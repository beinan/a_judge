var shell = require('shelljs');

var Job = require('../models/Job.js');
var Assignment = require('../models/Assignment.js');
var Promise = require('es6-promise').Promise;


//for(var i = 0; i < 2000; i++)
  //Job.create({cmd:'ls'});
var count = 0;
function process_job(job){
  count ++;
  console.log("processing", job._id);
  var outputs = [];
  return new Promise(function(resolve, reject) {
    var process = shell.exec(job.cmd, function(code, output){
      Job.update({_id: job._id}, {$set: {status: "finished"}}).exec(
        function(err, ret){
          if(err){
            console.log("update status error:", job._id, ret);
          }
        }
      );
      console.log("job finished:", job._id, "job count", count);
      
      var xml = "";
      for(var i = 0; i < outputs.length; i ++){
        if(outputs[i].indexOf("<root")===0 || xml.length > 0){
          xml = xml + outputs[i];
        }
      }
      var parseString = require('xml2js').parseString;
      parseString(xml, function (err, result) {
        for(var i = 0; i < result.root.assigns[0].assign.length; i++){
          var assign = result.root.assigns[0].assign[i];
          var questions = [];
          for(var q = 0; q < assign.questions[0].question.length; q++){
            var question = assign.questions[0].question[q];
            questions.push({num: parseInt(question.qnum[0]), points:parseInt(question.points[0]), desc: question.desc[0]});
          }
          Assignment.create({title: assign.assign_num[0], testcases: questions});
        }
      });
     
      resolve(code);
    });
    
    var logging = function(data){
      outputs.push(data);
      Job.update({_id: job._id}, {$push: {outputs: {line:data}}}).exec(
        function(err, ret){
          if(err){
            console.log("push outputs error:", job._id, ret);
          }
        }
      );
    };
    process.stdout.on('data', logging);
    process.stderr.on('data', logging);
  });    
}

module.exports = process_job;
