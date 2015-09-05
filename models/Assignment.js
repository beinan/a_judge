var mongoose = require('mongoose');

var assignmentSchema = new mongoose.Schema({
  assign_num: String,
  title: String,
  desc: String,
  isPublic: Boolean,
  isVectorAllowed: Boolean,
  testcases: [{ num: Number, points: Number, desc:String }],
  date: { type: Date, default: Date.now },
  skeleton_path: String
});

var Assignment = mongoose.model('Assignment', assignmentSchema);
module.exports = Assignment;
