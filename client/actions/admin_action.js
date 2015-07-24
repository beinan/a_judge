var AppDispatcher = require('../app_dispatcher');
var ActionType = require('../action_type');

class AdminAction {    
  queryJobs(page_num, page_size){
    AppDispatcher.dispatch({
      actionType: ActionType.ADMIN_QUERY_JOBS,
      page_num: page_num,
      page_size: page_size
    });
  }
}

let instance = new AdminAction();
export default instance;
