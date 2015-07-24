var AppDispatcher = require('../app_dispatcher');
var ActionType = require('../action_type');

class AppAction {
    
  setAppHeight(height){
    AppDispatcher.dispatch({
      actionType: ActionType.APP_HEIGHT_CHANGE,
      height:height
    });
  }

  setView(view_name){
    AppDispatcher.dispatch({
      actionType: ActionType.APP_VIEW_CHANGE,
      view_name: view_name
    });
  }
}

let instance = new AppAction();
export default instance;
