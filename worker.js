var secrets = require('./config/secrets');
var mongoose = require('mongoose');

//var Job = require('./models/Job.js');


var User = require('./models/User.js');

var Assignment = require('./models/Assignment.js');

var Submission = require('./models/Submission.js');

var cpp_builder = require('./job_processing/cpp_build');

function reduce() {
  Submission.findOneAndUpdate({status:"new"}, {$set: {status:"processing"}}, {sort: {_id:1}}).populate('owner', 'email').populate('assignment').exec(
    function(err, doc){
      if(doc){
        cpp_builder.grade(doc).then(function(){
          reduce();
        }).catch(function(err){
          console.log(err);
          doc.status = "error";
          doc.save();
          reduce();
        });
        
      } else {
        console.log("queue is empty."); 
        setTimeout(reduce, 1000);
      }
    }
  );        
};


mongoose.connect(secrets.db);
mongoose.connection.on('error', function() {
  console.error('MongoDB Connection Error. Please make sure that MongoDB is running.');
});

reduce();


process.on('SIGTERM', function () {
  console.log("Worker is terminating....");
  mongoose.disconnect();
  process.exit(0);
});
