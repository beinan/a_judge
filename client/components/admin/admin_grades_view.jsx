import React from 'react'


//import {ContentSection, ContentBox, UploadFileForm} from '../common_components.jsx';

//import {AdminJobsBox} from './admin_components.jsx'

import CommonListBox from '../commons/common_list_box.jsx'

import CommonAction from '../../actions/common_action.js'
import moment from 'moment';

import {Badge, Button, Label, Input, Modal} from 'react-bootstrap'

import {getJson} from '../../utils/ajax'

import getOrCreateListStore from '../../stores/common_list_store'


class AdminGradesView extends React.Component{
  constructor(props){
    super(props);
    this.state = {assign_num:'00'};
    // this.assign_store = getOrCreateListStore("admin_assignment_list", "/admin/api/assignments", 20);
    
   
  }
  
  render(){
    var this_view = this;
    var view_grades_btn = function(d){
      return <button className="btn btn-block btn-primary" style={{width: 70}} onClick={()=>{this_view.setState({assign_num:d.assign_num})}}>View</button>
    }

    return (
      <div>
        {/*header*/}
        <section className="content-header">
          <h1>
            Grades
            <small>Student Grades</small>
          </h1>
          <ol className="breadcrumb">
            <li><i className="fa fa-dashboard"></i> Home</li>
            <li>Admin</li>
            <li className="active">Grades</li>
          </ol>
        </section>
        {/*content*/}
        <div className="content body">
          <div className="row">
            <CommonListBox title="Assignment" url="/admin/api/assignments" headers= {["num", "View Grades"]}
                           data_mapper={(d)=>[d.assign_num, view_grades_btn(d)]}
                           store_id="admin_assignment_list" page_size={20} />
      
            <CommonListBox title={"Grades of Assignment:"+this.state.assign_num} url={"/admin/assign_grades/"+ this.state.assign_num} headers= {["name", "email", "score"]}
                           data_mapper={(d)=>[d.name, d.email, d.score, d.runtime]}
                           store_id={"admin_grades_list" + this.state.assign_num} page_size={200} />
              
        
            }
          </div>
          
        </div>
      </div>
    )
  }

}

export default AdminGradesView;
