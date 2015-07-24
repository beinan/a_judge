var mongoose = require('mongoose');

var assignmentSchema = new mongoose.Schema({
  title: String,
  desc: String,
  testcases: [{ num: Number, points: Number, desc:String }],
  date: { type: Date, default: Date.now }
});

var Assignment = mongoose.model('Assignment', assignmentSchema);
module.exports = Assignment;
