var shell = require('shelljs');
var util = require('util');
var moment = require('moment');
var path = require('path');
//var fs = require('fs');
var Promise = require('es6-promise').Promise;
var fsp = require('../job_processing/fs_promise');
var cpp_builder = require('../job_processing/cpp_build.js');

var Submission = require('../models/Submission');
var Assignment = require('../models/Assignment');

var secrets = require('../config/secrets');

exports.allSubmissions = function(req, res) {
  Submission.find().sort({_id : -1}).skip(req.query.start).limit(req.query.page_size).populate('owner', 'email').populate('assignment').exec(
    function(err, docs){
      res.json(docs);
    }
  );        
};

exports.mySubmissions = function(req, res) {
  Submission.find({owner: req.user._id}).sort({_id : -1}).skip(req.query.start).limit(req.query.page_size).populate('owner', 'email').populate('assignment').exec(
    function(err, docs){
      res.json(docs);
    }
  );        
};

exports.myGrades = function(req, res) {
  Assignment.find(
    function(err, assigns){
      var promises = [];
      for(var i in assigns){
        var p = new Promise(function(resolve, reject){
          Submission.find({owner:req.user.id, assignment:assigns[i]._id}).sort({final_score:-1}).limit(1).populate('owner', 'email').populate('assignment').exec(function(err,doc){
            if(err)
              reject(err);
            else
              resolve(doc);
          });
        });
        promises.push(p);
      }
      Promise.all(promises).then(function(data){
        var merged = [];
        merged = merged.concat.apply(merged, data);
        res.json(merged);
      }).catch(function(err){
        res.status(500).json(err);
      });
    }
  );
          
};


exports.upload = function(req, res){

  var assign_num = req.params.assign_num;
  var file = req.files.file;
  if(!file)
     res.status(400).json({status:'error', msg:"no file uploaded"}); 
  else
    Assignment.findOne({assign_num: assign_num}, function(err, assignment){
      if(err || !assignment){
        res.status(400).json({status:'error', msg:"Assignment does not exist or DB error."});
      }else{
        build_user_solution(file, assignment, req.user)
          .then(function(output){
            console.log("output-------", output);
            res.json({status:"success", job_id:""});
          })
          .catch(function(err){        
            console.log(err);
            res.status(500).json({status:'error', msg:err});
            throw err;
          });
      }
    });
};


exports.regrade = function(req, res){
  Submission.findOne({_id:req.params.id }).populate('owner', 'email').populate('assignment').exec(function(err, doc){
    if(err)
      res.json(err);
    else{
      
      cpp_builder.grade(doc).then(function(doc){
        res.json(doc);
      })
      .catch(function(err){
        console.log(err);

        res.status(500).json(err);
      });
    }  
  });
}

function build_user_solution(file, assignment, owner){
  
  var appDir = path.dirname(require.main.filename);    
  
  var user_folder = owner.email.replace('@', '_at_');
  //var datetime =
  var date_folder = moment().format('YYYYMMDD_HHmmss');
  var dest_folder = path.join(appDir, "uploads", user_folder, date_folder);
  var final_zip_filename = path.join(dest_folder, file.name);
  var source_folder = path.join(dest_folder, 'src');
  var build_folder = path.join(source_folder, 'build');
  var output_filename = 'a.out';  //hardcode here and also in docker file
  return fsp.mkdirp(build_folder)
    .then(fsp.move.bind(null, file.path, final_zip_filename))  //move uploaded solution to the user's folder
    .then(fsp.unzip.bind(null,final_zip_filename, source_folder))  //unzip file
    .then(function(filename_list){  //build
      //console.log(filename_list);  
      return cpp_builder.build(filename_list, source_folder, build_folder, output_filename);
    })
    .then(fsp.checksum.bind(null, path.join(build_folder, output_filename)))  //get md5 checksum for duplication checking   
    .then(create_submission.bind(null,owner._id, assignment._id, source_folder))
    ;        
};

function create_submission(owner_id, assign_id, folder, md5){
  //console.log("md5", md5);
  return new Promise(
    function(resolve, reject){
      Submission.findOne({build_md5: md5, owner: owner_id}, {_id:1}, function(err, doc){
        if(err)
          reject(err);
        else if(doc && secrets.checking_dup) //duplicated
          reject("Duplicated submission.");
        else {
          var new_submission = {
            build_md5:md5,
            folder: folder,
            owner: owner_id,
            assignment: assign_id
          };
          Submission.create(new_submission, function(err, new_doc){
            if(err)
              reject(err);
            else
              resolve(new_doc);
          });
        }
      });
    }
  );
}
