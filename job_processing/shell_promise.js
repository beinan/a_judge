var Promise = require('es6-promise').Promise;
var exec = require('child_process').exec;

exports.exec = function(cmd, options){
  return new Promise(
    function(resolve, reject){
      var output = '';
      console.log("start exec command", cmd, options);
     
      var child_process = exec(cmd, options, function (err) {
        console.log("finish command", cmd, options, err);
      
        if (err) {
           return reject(err);
         }
         return resolve(output);
      });

      child_process.stdout.on('data', function(data) {
        output += data;
        
      });

      child_process.stderr.on('data', function(data) {
        output += data;
      });
    }                  
  );
};
