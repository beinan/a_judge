/**
 * Question  data Controller
 */

var Assignment = require('../models/Assignment.js');

exports.getAssignments = function(req, res) {
  Assignment.find(
    function(err, docs){
      res.json(docs);
    }
  );        
};

