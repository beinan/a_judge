var AppDispatcher = require('../app_dispatcher');
var ActionType = require('../action_type');

class AssignmentsAction {    
  queryAssignments(page_num, page_size){
    AppDispatcher.dispatch({
      actionType: ActionType.QUERY_ASSIGNMENTS,
      page_num: page_num,
      page_size: page_size
    });
  }
  
  activeAssignment(id){
    AppDispatcher.dispatch({
      actionType: ActionType.ACTIVE_ASSIGNMENT,
      id: id
    });
  }
}

let instance = new AssignmentsAction();
export default instance;
