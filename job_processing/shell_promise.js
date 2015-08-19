var Promise = require('es6-promise').Promise;
var exec = require('child_process').exec;

exports.exec = function(cmd, options){
  return new Promise(
    function(resolve, reject){
      var output = '';
      var child_process = exec(cmd, options, function (err) {
         console.log("exec command", cmd, options);
         if (err) {
           return reject(output);
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
