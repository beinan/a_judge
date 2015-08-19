/**
 * Question  data Controller
 */

var Question = require('../models/Question.js');
var Job = require('../models/Job.js');
var Assignment = require('../models/Assignment.js');

var shell = require('shelljs');

var fsp = require('../job_processing/fs_promise');
var path = require('path');
var cpp_builder = require('../job_processing/cpp_build.js');
var exec = require('../job_processing/shell_promise').exec;


exports.getQuestions = function(req, res) {
  Question.find(
    function(err, docs){
      res.render('question/questions', {questions: docs});
    }
  );        
};


//admin functions start
exports.createQuestion = function(req, res) {
  res.render('question/question_form');  
};

exports.postCreateQuestion = function(req, res) {
  
  var q = new Question({
    title: req.body.title,
    desc: req.body.desc
  });
  q.save(function(err, saved_q){
    if(err) return next(err);
    return res.redirect('/admin/questions/' + saved_q._id);
  });
};

exports.adminQuestion = function(req, res){
  Question.findById(req.params.id, function(err, q){
    if(err)
      return next(err);
    return res.render('question/admin_question', {question : q});
  });
};

exports.adminAllQuestions = function(req, res){
  Question.find(
    function(err, docs){
      res.render('question/admin_all_questions', {questions: docs});
    }
  );
};

exports.uploadTestFile = function(req, res){
  console.log(req.body);
  console.log(req.files);
  var question_id = req.body.question_id;

  return res.redirect('/admin/questions/' + question_id);
};

var util = require('util');
var moment = require('moment');
   
exports.importCppGrader = function(req, res){
   var file = req.files.file;
  if(file){
    build_cpp_grader(file, req.user)
      .then(function(count){
        res.json({status:"success", msg: "Import succeeded, " + count + " assignments created or updated."});
      })
      .catch(function(err){
        console.error(err);
        res.status(500).json({status:"error", msg:err});
      });    
  }else{
    res.json({status:"error", msg:'no file uploaded'});
  }   
 
};

function build_cpp_grader(file, owner){
  var appDir = path.dirname(require.main.filename);    
  
  var user_folder = owner.email.replace('@', '_at_');
  //var datetime =
  var date_folder = moment().format('YYYYMMDD_HHmmss');
  var dest_folder = path.join(appDir, "uploads", user_folder, date_folder);
  var final_zip_filename = path.join(dest_folder, file.name);
  var source_folder = path.join(dest_folder, 'src');
  var output_filename = 'a.out';  //hardcode here and also in docker file
  var grader_dir = path.join(appDir,"docker/phil");
   
  return fsp.mkdirp(source_folder)
    .then(fsp.move.bind(null, file.path, final_zip_filename))  //move uploaded solution to the user's folder
    .then(fsp.unzip.bind(null,final_zip_filename, source_folder))  //unzip file
    .then(cpp_builder.buildCppGrader.bind(null, source_folder))
    .then(fsp.move.bind(null, path.join(source_folder, "CppGrader"), path.join(grader_dir, "CppGrader"))) //mv cppgrader to grader folder
    .then(exec.bind(null, "docker build -t cppgrader .", {cwd:grader_dir}))  //rebuild docker image
    .then(exec.bind(null, "./CppGrader reload_assignments", {cwd: grader_dir})) //generate assignment xml information
    .then(parseXmlString) //create assignment to db
  ;
}

var parseString = require('xml2js').parseString;
function parseXmlString(xml){
  return new Promise(
    function(resolve, reject){
      parseString(xml, function (err, result) {
        var i;
        for(i = 0; i < result.root.assigns[0].assign.length; i++){
          var assign = result.root.assigns[0].assign[i];
          var questions = [];
          for(var q = 0; q < assign.questions[0].question.length; q++){
            var question = assign.questions[0].question[q];
            questions.push({num: parseInt(question.qnum[0]), points:parseInt(question.points[0]), desc: question.desc[0]});
          }
          Assignment.findOneAndUpdate({assign_num: assign.assign_num[0]}, {$set: {testcases:questions}}, {upsert: true, new:true})
            .exec(function(err, doc){
              if(err)
                reject(error);
              else
                console.log("assignmnt created or updated:", doc);
            });
          //Assignment.create({title: assign.assign_num[0], testcases: questions});
        }
        return resolve(i);
      });
    }
  );
}
exports.addGrader = function(req, res){
  console.log(req.body.code);
  var question_id = req.body.question_id;
  
  var path = require('path');
  var appDir = path.dirname(require.main.filename);
  var fs = require('fs');
  var srcFilename = appDir + "/uploads/a.cpp"; 
  fs.writeFile(srcFilename, req.body.code, function(err) {
    if(err) {
        return console.log(err);
    }
    //var shell = require('shelljs');
    var process = shell.exec("docker run -i -v " + srcFilename + ":/src.cpp:ro cppgrader sh -c \"g++ -std=c++11 -o app /src.cpp; timeout -s KILL 20 ./app\"",
                             {async:true});
    //console.log(process);
    process.stdout.on('data',  function(output){
        //console.log(code);
        //console.log(output);
        var lines = output.split('\n');
        for(i in lines){
          console.log("line:", lines[i]);
          //if(lines[i] === "AAA")
            //process.stdin.write("MA 3 3\n");
        }
        
    });
    process.stdin.write("ma 3 3\n 5\n 10 1 1 25 1 3 50 2 2 80 3 2 100 3 3 \n");
    return console.log("The file was saved!");
  }); 
  return res.redirect('/admin/questions/' + question_id);
};



//admin functions end
