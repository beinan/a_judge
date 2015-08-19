var AppDispatcher = require('../app_dispatcher');
var ActionType = require('../action_type');

class CommonAction {
    
  listGotoPage(store_id, page_num){
    if(page_num < 0)
      return;
    AppDispatcher.dispatch({
      actionType: ActionType.LIST_GOTO_PAGE,
      store_id:store_id,
      page_num:page_num
    });
  }

  listDataEntryUpdate(store_id, data_entry){
    
    AppDispatcher.dispatch({
      actionType: ActionType.LIST_DATA_ENTRY_UPDATE,
      store_id:store_id,
      data_entry: data_entry
    });
  }
  
}

let instance = new CommonAction();
export default instance;
