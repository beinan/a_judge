var mongoose = require('mongoose');
var Schema = mongoose.Schema,
    ObjectId = Schema.ObjectId;
var JobSchema = new Schema({
  cmd: String,
  status: { type: String, default: "new" },
  type: String,
  owner  : { type: ObjectId, ref: 'User' },
  outputs: [{ line: String, date: { type: Date, default: Date.now } }],
  date: { type: Date, default: Date.now }
});

var Job = mongoose.model('Job', JobSchema);
module.exports = Job;
