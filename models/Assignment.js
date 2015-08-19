var mongoose = require('mongoose');

var assignmentSchema = new mongoose.Schema({
  assign_num: String,
  title: String,
  desc: String,
  isPublic: Boolean,
  testcases: [{ num: Number, points: Number, desc:String }],
  date: { type: Date, default: Date.now }
});

var Assignment = mongoose.model('Assignment', assignmentSchema);
module.exports = Assignment;
