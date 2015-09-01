/**
 * Question  data Controller
 */

var Assignment = require('../models/Assignment.js');
var path = require('path');
var Promise = require('es6-promise').Promise;
var fsp = require('../job_processing/fs_promise');

var  moment = require('moment');

exports.getAssignments = function(req, res) {
  Assignment.find({isPublic:true}).sort({"assign_num":1}).skip(req.query.start).limit(req.query.page_size).exec(
    function(err, docs){
      res.json(docs);
    }
  );        
};

exports.allAssignments = function(req, res) {
  Assignment.find().skip(req.query.start).limit(req.query.page_size).exec(
    function(err, docs){
      res.json(docs);
    }
  );        
};

exports.downloadSkeleton = function(req, res){
 var assign_num = req.params.assign_num;
  Assignment.findOne({assign_num: assign_num}, function(err, assignment){
    if(err || !assignment){
      res.status(400).json({status:'error', msg:"Assignment does not exist or DB error."});
    }if (!assignment.skeleton_path){
      res.status(404).json({msg:"Not found"});
    }else{
      res.download(assignment.skeleton_path);
    }
  }); 
}

exports.uploadSkeleton = function(req, res){
  var assign_num = req.params.assign_num;
  var file = req.files.file;
  if(!file)
     res.status(400).json({status:'error', msg:"no file uploaded"}); 
  else
    Assignment.findOne({assign_num: assign_num}, function(err, assignment){
      if(err || !assignment){
        res.status(400).json({status:'error', msg:"Assignment does not exist or DB error."});
      }else{
        create_skeleton(file, assignment, req.user)
          .then(function(){
           
            res.json({status:"success"});
          })
          .catch(function(err){        
            console.log(err);
            res.status(500).json({status:'error', msg:err});
            throw err;
          });
      }
    });
};

function create_skeleton(file, assignment, owner){
  
  var appDir = path.dirname(require.main.filename);    
  
  var user_folder = owner.email.replace('@', '_at_');
  //var datetime =
  var date_folder = moment().format('YYYYMMDD_HHmmss');
  var dest_folder = path.join(appDir, "uploads", user_folder, date_folder);
  var final_zip_filename = path.join(dest_folder, file.name);
  return fsp.mkdirp(dest_folder)
    .then(fsp.move.bind(null, file.path, final_zip_filename))  //move uploaded solution to the user's folder
    .then(function(){  //build
      assignment.skeleton_path = final_zip_filename;
      assignment.save();
    }) ;        
};

exports.update = function(req, res) {
  var data = req.body;
  //console.log(data);
  var cb = function (err, assign) {
    if (err) 
      res.status(500).json(err);
    else
      res.json(assign);
  };
  Assignment.findByIdAndUpdate(data._id, { $set: { title: data.title, desc: data.desc, 
                                                   isPublic: data.isPublic, date:moment(data.date).toDate()}}, 
                               {'new':true}
                               , cb);
};
