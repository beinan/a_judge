var AppDispatcher = require('../app_dispatcher');
var EventEmitter = require('events').EventEmitter;
var ActionType = require('../action_type');
var assign = require('object-assign');

var getJson = require('../utils/ajax.js').getJson;

var _jobs_data = {status:'init', jobs:[], page_num:0, page_size: 20};


var AdminJobsStore = assign({}, EventEmitter.prototype, {
  
  JOBS_UPDATE_EVENT : 'jobs_update_event',
  
  getData: function(){
    return _jobs_data;
  },

  emitChange: function(event) {
    this.emit(event);
  },

  
  addEventListener: function(event, callback) {
    this.on(event, callback);
  },

  /**
   * @param {function} callback
   */
  removeEventListener: function(event, callback) {
    this.removeListener(event, callback);
  }
});

// Register callback to handle all updates
AppDispatcher.register(function(action) {

  switch(action.actionType) {
    case ActionType.ADMIN_QUERY_JOBS:
    //_app_data.height = action.height;
    _jobs_data.page_num = action.page_num;
    _jobs_data.page_size = action.page_size;
    _jobs_data.status = "loading";
    AdminJobsStore.emitChange(AdminJobsStore.JOBS_UPDATE_EVENT);
    var params = {start: action.page_num*action.page_size, page_size:action.page_size};
    getJson('/admin/api/jobs', params).then((data) => {
      _jobs_data.jobs = data; 
      _jobs_data.status = "ready";
      AdminJobsStore.emitChange(AdminJobsStore.JOBS_UPDATE_EVENT);
    });
    break;

    default:
      // no op
  }
});


export default AdminJobsStore;
