var mongoose = require('mongoose');

var questionSchema = new mongoose.Schema({
  title: String,
  desc: String
});

var Question = mongoose.model('Question', questionSchema);
module.exports = Question;
