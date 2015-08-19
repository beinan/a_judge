var mongoose = require('mongoose');
var Schema = mongoose.Schema,
    ObjectId = Schema.ObjectId;
var SubmissionSchema = new Schema({
  folder: String,
  build_md5: String,  //for dup checking
  status: { type: String, default: "new" },
  owner  : { type: ObjectId, ref: 'User' },
  results: [{ test_case: Number, desc: String, points: Number, output: String, err_msg: String, passed: Boolean, runtime: Number, date: { type: Date, default: Date.now } }],  
  assignment  : { type: ObjectId, ref: 'Assignment' }, 
  total_runtime: Number,
  total_score: Number,
  bonus: Number,
  final_score: Number,
  late_fee: Number,
  date: { type: Date, default: Date.now }
});

var Submission = mongoose.model('Submission', SubmissionSchema);
module.exports = Submission;
