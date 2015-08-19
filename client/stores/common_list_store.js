var AppDispatcher = require('../app_dispatcher');
var EventEmitter = require('events').EventEmitter;
var ActionType = require('../action_type');
var assign = require('object-assign');

var getJson = require('../utils/ajax.js').getJson;

const UPDATE_EVENT = "update_event";

class CommonListStore extends EventEmitter{

  constructor(url, page_size){
    super();
    this._data = {status:'init', items:[], page_num:0, page_size: page_size};
    this.url = url;
    this.gotoPage(this._data.page_num);
  }
  
  gotoPage(page_num){
    this._data.status = "loading";
    this._data.page_num = page_num;
    this.emitChange();
    var params = {start: this._data.page_num*this._data.page_size, page_size:this._data.page_size};
    getJson(this.url, params).then((data) => {
      this._data.items = data; 
      this._data.status = "ready";
      this.emitChange();
    }).catch((err) => {console.log(err); this._data.status = 'error';});
  }

  updateDataEntry(data_entry){
    console.log("update list entry", data_entry);
    for(var i in this._data.items){
      if(this._data.items[i]._id == data_entry._id){
        console.log("update matched", i, this._data.items[i], data_entry);
        console.log("original",this._data.items[i]);
        assign(this._data.items[i], data_entry); //overwrite data.items[i]
        console.log(this._data.items[i], data_entry);
        this.emitChange();
        
        return;
      }
    }
  }
  
  getData(){
    return this._data;
  }

  
  emitChange() {
    this.emit(UPDATE_EVENT);
  }

  
  addUpdateEventListener(callback) {
    this.on(UPDATE_EVENT, callback);
  }

  /**
   * @param {function} callback
   */
  removeUpdateEventListener(callback) {
    this.removeListener(UPDATE_EVENT, callback);
  }
}



// Register callback to handle all updates
AppDispatcher.register(function(action) {
  var store_id = action.store_id;
   
  switch(action.actionType) {
    case ActionType.LIST_GOTO_PAGE:
    //_app_data.height = action.height;
    var page_num = action.page_num;
    getOrCreateListStore(store_id).gotoPage(page_num);    
    break;

    case ActionType.LIST_DATA_ENTRY_UPDATE:
    //_app_data.height = action.height;
    var data_entry = action.data_entry;
     getOrCreateListStore(store_id).updateDataEntry(data_entry);    
    break;

    default:
      // no op
  }
});


var _stores = {};

function getOrCreateListStore(store_id, url, page_size){
  if(!_stores[store_id])
    _stores[store_id] = new CommonListStore(url, page_size);
  return _stores[store_id];
}

export default getOrCreateListStore;
