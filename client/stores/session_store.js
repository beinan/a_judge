var AppDispatcher = require('../app_dispatcher');
var EventEmitter = require('events').EventEmitter;
var ActionType = require('../action_type');
var assign = require('object-assign');

var getJson = require('../utils/ajax.js').getJson;

var _session_data = {status:'init'};


var SessionStore = assign({}, EventEmitter.prototype, {
  
  SESSION_READY_EVENT : 'session_ready_event',
  
  getData: function(){
    return _session_data;
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

getJson('/api/account').then((data) => {
  _session_data = data; 
  _session_data.status = "ready";
  SessionStore.emitChange(SessionStore.SESSION_READY_EVENT);
});

export default SessionStore;
