var AppDispatcher = require('../app_dispatcher');
var EventEmitter = require('events').EventEmitter;
var ActionType = require('../action_type');
var ViewType = require('../view_type');
var assign = require('object-assign');


var _app_data = {height:0, view_name:ViewType.QUESTION_VIEW};

var AppStore = assign({}, EventEmitter.prototype, {
  
  HEIGHT_CHANGE_EVENT : 'app_height_change_event',
  VIEW_CHANGE_EVENT : 'app_view_change_event',
  
  getData: function(){
    return _app_data;
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
    case ActionType.APP_HEIGHT_CHANGE:
      _app_data.height = action.height;      
      AppStore.emitChange(AppStore.HEIGHT_CHANGE_EVENT);
      break;

    case ActionType.APP_VIEW_CHANGE:
      _app_data.view_name = action.view_name;      
      AppStore.emitChange(AppStore.VIEW_CHANGE_EVENT);
      break;

    default:
      // no op
  }
});

export default AppStore;
