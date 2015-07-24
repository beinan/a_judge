var secrets = require('./config/secrets');
var mongoose = require('mongoose');

var Job = require('./models/Job.js');

var process_job = require('./job_processing/job_processor');

function reduce() {
  Job.findOneAndUpdate({status:"new"}, {$set: {status:"processing"}}, {sort: {_id:1}}).exec(
    function(err, doc){
      if(doc){
        process_job(doc).then(function(){
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
