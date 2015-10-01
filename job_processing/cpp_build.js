var shell = require('shelljs');
var path = require('path');

var Promise = require('es6-promise').Promise;
var exec = require('./shell_promise').exec;

var parseString = require('xml2js').parseString;


//build user solution
exports.build = function(source_folder, build_folder, output_filename){
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
      var add_result = function(submission, test, testcase_index, result){
        result.test_case = test.num;
        result.points = result.passed?test.points:0;
        result.runtime = result.runtime?result.runtime: 0;
        result.desc = test.desc;
        submission.results.push(result);
        submission.total_score = submission.total_score + result.points;
        submission.total_runtime = submission.total_runtime + result.runtime;
        reduce(testcase_index + 1);
        
      };
      var reduce = function(testcase_index){
        if(testcase_index < submission.assignment.testcases.length){
          var test = submission.assignment.testcases[testcase_index];
          console.log("grade test:", test);
          var grader_promise = grade_test(path.join(submission.folder,"build"), submission.assignment.assign_num, test.num)
            .then(function(result){
              add_result(submission, test, testcase_index, result);
            })
            .catch(function(err){
              console.log("grading exec error", err);              
              add_result(submission, test, testcase_index, {passed: false, err_msg: "segment fault or unknown error." + err});
            });
          
        }else{
          //finished
          submission.status = "finished";
          submission.final_score = submission.total_score - submission.late_fee + submission.bonus;     
          if(submission.final_score < 0){
            submission.final_score = 0;
          }
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
        //using floor, because 24 hours policy(no late fee in the first 24 hours)
        submission.late_fee = Math.floor(timediff / (1000 * 60 * 60 * 24)) * 10; //TODO: this should be configurable
      }
      reduce(0); //start grading each testcases one by one
    }
  );    
};


function grade_test(build_folder, assign_num, testcase_num){
  return new Promise(
    function(resolve, reject){
      var killed = false;
      var timeout_id = setTimeout(function(){
        //kill and remove all existing docker containers
        exec("docker kill $(docker ps | awk '{ print $1,$2 }' | grep cppgrader | awk '{print $1 }') && docker rm $(docker ps -a | awk '{ print $1,$2 }' | grep cppgrader | awk '{print $1 }')");
        resolve({passed:false, err_msg:"Time out"}); //timeout 
      }, 30000);
      var run_grader =  function(){
        exec("docker run --cpuset-cpus=\"0,1\" -v " + build_folder 
             + ":/ads/ cppgrader /CppGrader " + assign_num + " " + testcase_num + " /ads/a.out", {timout: 120000,killSignal: 'SIGKILL'})
          .then(function(data){
            if(!killed){
              clearTimeout(timeout_id);
              parseXmlString(data).then(function(result){
                resolve(result);
              }).catch(function(e){
                reject(e);
              });
            }else{
              resolve({passed:false, err_msg:"Time out."});
            }
          }).catch(function(e){
            reject(e);
          });
      };
      exec("docker kill $(docker ps | awk '{ print $1,$2 }' | grep cppgrader | awk '{print $1 }')") //clear running docker containers.
        .then(run_grader).catch(run_grader);
      
    }
  );
  
}

function parseXmlString(xml){
  return new Promise(
    function(resolve, reject){
      parseString(xml, function (err, result) {
        if(err){
          reject(err);
        }
        
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
