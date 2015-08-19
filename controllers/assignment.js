/**
 * Question  data Controller
 */

var Assignment = require('../models/Assignment.js');

var  moment = require('moment');

exports.getAssignments = function(req, res) {
  Assignment.find({isPublic:true}).sort({"assign_num":1}).skip(req.query.start).limit(req.query.page_size).exec(
    function(err, docs){
      res.json(docs);
    }
  );        
};

exports.allAssignments = function(req, res) {
  Assignment.find().skip(req.query.start).limit(req.query.page_size).exec(
    function(err, docs){
      res.json(docs);
    }
  );        
};


exports.update = function(req, res) {
  var data = req.body;
  //console.log(data);
  var cb = function (err, assign) {
    if (err) 
      res.status(500).json(err);
    else
      res.json(assign);
  };
  Assignment.findByIdAndUpdate(data._id, { $set: { title: data.title, desc: data.desc, 
                                                   isPublic: data.isPublic, date:moment(data.date).toDate()}}, 
                               {'new':true}
                               , cb);
};
