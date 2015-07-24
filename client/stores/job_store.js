
var EventEmitter = require('events').EventEmitter;
var getJson = require('../utils/ajax.js').getJson;

const UPDATE_EVENT = 'UPDATE_EVENT';


class JobStore extends EventEmitter{

  constructor(job_id){
    super();
    this.job_id = job_id;
    this.data = {status: 'init'};
  }

  update(){
    console.log("update job store", this);
    //this.data.status = "loading";
    //this.emit(UPDATE_EVENT);
    getJson('/api/jobs/' + this.job_id).then((data) => {
      this.data = data; 
      this.data.status = "ready";
      this.emit(UPDATE_EVENT);
    });
  }
  
  
  addUpdateEventListener(callback){
    this.on(UPDATE_EVENT, callback);
  }

  
  removeUpdateEventListener(callback){
    this.removeListener(UPDATE_EVENT, callback);
  }
}

export default JobStore;
