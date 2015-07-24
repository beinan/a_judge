var AppDispatcher = require('../app_dispatcher');
var EventEmitter = require('events').EventEmitter;
var ActionType = require('../action_type');
var assign = require('object-assign');

var getJson = require('../utils/ajax.js').getJson;

var _ass_data = {status:'init', assignments:[], page_num:0, page_size: 20};


var AssignmentsStore = assign({}, EventEmitter.prototype, {
  
  ASS_UPDATE_EVENT : 'ass_update_event',
  ACTIVE_ASSIGNMENT_EVENT : 'active_assignment',

  getData: function(){
    return _ass_data;
  },
  
  getActiveAssignment: function(){
    if(_ass_data.active_id)
      for(let ass of _ass_data.assignments)
        if(ass._id === _ass_data.active_id)
          return ass;
    return null;
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
    case ActionType.QUERY_ASSIGNMENTS:
    //_app_data.height = action.height;
    _ass_data.page_num = action.page_num;
    _ass_data.page_size = action.page_size;
    _ass_data.status = "loading";
    AssignmentsStore.emitChange(AssignmentsStore.ASS_UPDATE_EVENT);
    var params = {start: action.page_num*action.page_size, page_size:action.page_size};
    getJson('/api/assignments', params).then((data) => {
      _ass_data.assignments = data; 
      _ass_data.status = "ready";
      AssignmentsStore.emitChange(AssignmentsStore.ASS_UPDATE_EVENT);
    });
    break;

    case ActionType.ACTIVE_ASSIGNMENT:
    //_app_data.height = action.height;
    _ass_data.active_id = action.id;
    
    AssignmentsStore.emitChange(AssignmentsStore.ACTIVE_ASSIGNMENT_EVENT);

    default:
      // no op
  }
});


export default AssignmentsStore;
