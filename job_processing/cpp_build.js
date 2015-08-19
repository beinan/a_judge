var shell = require('shelljs');
var path = require('path');

var Promise = require('es6-promise').Promise;
var exec = require('./shell_promise').exec;

var parseString = require('xml2js').parseString;


//build user solution
exports.build = function(code_files, source_folder, build_folder, output_filename){
  var output = path.join(build_folder, output_filename);
  return exec("g++ -o " + output + " -fPIC -shared *.cpp -lpthread", {cwd: source_folder});                                           
};

//build cpp grader
exports.buildCppGrader = function(source_folder){
  return exec("g++ -ggdb -DGRADE_SERVER -o CppGrader *.cpp -ldl -lpthread", {cwd: source_folder});                                           
};

exports.grade = function(submission){
  return new Promise(
    function(resolve, reject){
      var reduce = function(testcase_index){
        if(testcase_index < submission.assignment.testcases.length){
          var test = submission.assignment.testcases[testcase_index];
          console.log("grade test:", test);
          var grader_promise = grade_test(path.join(submission.folder,"build"), submission.assignment.assign_num, test.num)
            .then(parseXmlString)
            .then(function(result){
              result.test_case = test.num;
              result.points = result.passed?test.points:0;
              result.desc = test.desc;
              submission.results.push(result);
              submission.total_score = submission.total_score + result.points;
              submission.total_runtime = submission.total_runtime + result.runtime;
              reduce(testcase_index + 1);
            })
            .catch(function(err){
              console.log(err);
            });
          
        }else{
          //finished
          submission.status = "finished";
          submission.final_score = submission.total_score - submission.late_fee + submission.bonus;     
          submission.save(function(err){
            if(err)
              reject(err);
            else
              resolve(submission);
          });
          
        }
      };

      submission.results = [];
      submission.total_score = 0;
      submission.total_runtime = 0;
      submission.late_fee = 0;
      submission.bonus = 0;
      var timediff = submission.date.getTime() - submission.assignment.date.getTime();
      if(timediff > 0){
        submission.late_fee = Math.ceil(timediff / (1000 * 60 * 60 * 24)) * 5; //TODO: this should be configurable
      }
      reduce(0); //start grading each testcases one by one
    }
  );    
};


function grade_test(build_folder, assign_num, testcase_num){
  return exec("docker run --cpuset-cpus=\"0,1\" -v " + build_folder 
              + ":/ads/ cppgrader /CppGrader " + assign_num + " " + testcase_num + " /ads/a.out", {timout: 120000});
}

function parseXmlString(xml){
  return new Promise(
    function(resolve, reject){
      parseString(xml, function (err, result) {
        var test_result = result.root.results[0].result[0];
        var passed = test_result.passed[0] == '1'? true:false;
        var error_msg = test_result.error_message[0];
        var time = parseInt(test_result.time[0]);
        var program_output = result.root.program_output[0];
        console.log(xml, result, passed, error_msg, time);
        resolve({runtime:time, passed:passed, err_msg:error_msg, output:program_output});
      });
    }
  );
}
