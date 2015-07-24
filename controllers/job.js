var Job = require('../models/Job.js');

exports.allJobs = function(req, res) {
  Job.find().sort({_id : -1}).skip(req.query.start).limit(req.query.page_size).populate('owner', 'email isAdmin').exec(
    function(err, docs){
      res.json(docs);
    }
  );        
};

exports.getJob = function(req, res) {
  Job.findById(req.params.id, function(err, doc){
    if(err)
      return next(err);
    return res.json(doc);
  });        
};
