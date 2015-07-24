/**
 * Question  data Controller
 */

var Question = require('../models/Question.js');
var Job = require('../models/Job.js');
var shell = require('shelljs');

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
  console.log(req.body);
  console.log(req.files);
  var file = req.files.file;
  if(file){
    var path = require('path');
    var appDir = path.dirname(require.main.filename);    
    
    var user_folder = req.user.email.replace('@', '_at_') + '/';
    //var datetime =
    var date_folder = moment().format('YYYYMMDD_HHmmss') + '/';
    var dest_folder = appDir + "/uploads/" + user_folder + date_folder;
    var grader_dir = appDir + "/graders";
    var compile_cmd = util.format("g++ -ggdb -DGRADE_SERVER -o CppGrader *.cpp -ldl -lpthread && cp CppGrader %s && echo \"CppGrader is ready!\"", grader_dir);
    var reload_cmd = util.format("cd %s && ./CppGrader reload_assignments ", grader_dir);
    var cmd = util.format("mkdir %s -p && cd %s && cp %s . && unzip %s && %s && %s", 
                          dest_folder, dest_folder, file.path, file.name, compile_cmd, reload_cmd);
    
    //create a async job, #see worker.js
    var promise = Job.create({cmd:cmd, owner: req.user._id, type: 'import_assignments'});
    return promise.then(function(doc){ res.json({status:"ok", job_id:doc._id});});    
  }else{
    return req.json({err:'no file uploaded'});
  }   
 
};


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
