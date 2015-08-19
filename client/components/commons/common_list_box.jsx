import React from 'react'

import CommonBox from './common_box.jsx'

import getOrCreateListStore from '../../stores/common_list_store'

import CommonAction from '../../actions/common_action'

/*List items and pagination in a box*/ 
class CommonListBox extends React.Component{
  constructor(props){
    super(props);
    this.store = getOrCreateListStore(this.props.store_id, this.props.url, this.props.page_size);
    this.state = this.store.getData();
    this._onChange = this._onChange.bind(this);
  }
  
  componentDidMount() {
    
    this.store.addUpdateEventListener(this._onChange);
  }

  componentWillUnmount() {
    this.store.removeUpdateEventListener(this._onChange);
  }

  _onChange() {
    this.setState(this.store.getData());
  }
  
  render(){
    console.log("common list box", this.props.store_id, this.state);
    var items;
    if(this.state.status !== "ready")
      items = <p>Loading</p>
    else{
      var table_headers = this.props.headers.map((t_head) => (<th>{t_head}</th>));
      var item_entries = this.state.items.map((item_data)=>
        <tr>
         {this.props.data_mapper(item_data).map((t_data)=>(<td>{t_data}</td>))}
        </tr>   
      );
      items = ( 
        <table className="table table-bordered">
         <tr>{table_headers}</tr> 
         {item_entries}
        </table>
      );
    }
    //pagination
    var footer = (
      <div className="box-tools pull-right">
        <ul className="pagination pagination-sm inline">
          <li><a href="#" onClick={() => CommonAction.listGotoPage(this.props.store_id, this.state.page_num)}>Refresh</a></li>
          <li><a href="#" onClick={() => CommonAction.listGotoPage(this.props.store_id, this.state.page_num - 1)}>«</a></li>
          <li><a disabled>{this.state.page_num + 1}</a></li>
          <li><a href="#" onClick={() => CommonAction.listGotoPage(this.props.store_id, this.state.page_num + 1)}>»</a></li>
        </ul>
      </div>
    )
    return (
      <CommonBox title={this.props.title} footer={footer}>
        {items}
      </CommonBox>
    )
  }
}

export default CommonListBox;
