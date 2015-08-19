import React from 'react'


//import {ContentSection, ContentBox, UploadFileForm} from '../common_components.jsx';

//import {AdminJobsBox} from './admin_components.jsx'

import CommonListBox from '../commons/common_list_box.jsx'

import CommonAction from '../../actions/common_action.js'
import moment from 'moment';

import {Badge, Button, Label, Input, Modal} from 'react-bootstrap'

import {getJson} from '../../utils/ajax'

class AdminMonitorView extends React.Component{
  constructor(props){
    super(props);
    this.state = {};
  }
  
  render(){
    var regrade_click = (s) =>{
      getJson("/admin/regrade/" + s._id)
           .then((data)=>{
             alert("Regrade finished.");
             console.log("submission returned",data);
             CommonAction.listDataEntryUpdate("admin_submission_list", data);
           })
    };
    var detail_click = (s) => {
      console.log("show details", s);
      this.setState({showModal: true, currentSubmission: s});
    }
    var submission_mapper = (s)=>{
      var op_button = (
        <button className="btn btn-block btn-primary" style={{width: 70}} onClick={regrade_click.bind(null,s)}>Regrade</button>
        );
      var detail_button = (
        <button className="btn btn-block btn-primary" style={{width: 70}} onClick={detail_click.bind(null,s)}>Show</button>     
      );
      return [s.owner.email, s.status, moment(s.date).fromNow(), detail_button, op_button]
    }
    
    var render_submission_result = (s) =>{
      if(!s)
        return null;
      return s.results.map(r => {
        return (
          <tr>
            <td>{r.desc}</td>
            <td>{r.output}</td>
            <td>{r.err_msg}</td>
            <td>{r.runtime}</td>
            <td>{r.points}</td>
          </tr>
        );
      });
    }
    var modalInstance = (
      <div>
        <Modal show={this.state.showModal} onHide={()=>this.setState({showModal:false})}>
          <Modal.Header closeButton>
            <Modal.Title>Submission Details</Modal.Title>
          </Modal.Header>

          <Modal.Body>
             <table className="table table-bordered"> 
              <tr>
                <td>Test Case</td>
                <td>Output</td>
                <td>Error Message</td>
                <td>Runtime</td>
                <td>Points</td>
              </tr>
              {render_submission_result(this.state.currentSubmission)}
            </table>
            <p>Total: <Badge>{this.state.currentSubmission?this.state.currentSubmission.total_score:0}</Badge></p>
            <p>Late: <Badge>{this.state.currentSubmission?this.state.currentSubmission.late_fee:0}</Badge></p>
            <p>Final: <Badge>{this.state.currentSubmission?this.state.currentSubmission.final_score:0}</Badge></p>
           
           
          </Modal.Body>

          <Modal.Footer>
            <Button onClick={()=>this.setState({showModal:false})}>Close</Button>
            
          </Modal.Footer>

        </Modal>
      </div>
    );
    var promote = function(u){
      var on_click = () => getJson("/admin/promote/" + u._id)
           .then((data)=>{
             alert("Promote finished.");
             console.log("promote returned",data);
             u.isAdmin = true;  //for update view only
             CommonAction.listDataEntryUpdate("admin_user_list", u);
           })
      return <button className="btn btn-block btn-danger" style={{width: 80}} onClick={on_click}>Promote</button>

  
    }
    var demote = function(u){
      var on_click = ()=>getJson("/admin/demote/" + u._id)
           .then((data)=>{
             alert("Demote finished.");
             console.log("promote returned",data);
             u.isAdmin = false;  //for update view only
             CommonAction.listDataEntryUpdate("admin_user_list", u);
           })  
      return <button className="btn btn-block btn-info" style={{width: 80}} onClick={on_click}>Demote</button>
                             
    }
    return (
      <div>
        {/*header*/}
        <section className="content-header">
          <h1>
            Monitor
            <small>Grading server monitor</small>
          </h1>
          <ol className="breadcrumb">
            <li><i className="fa fa-dashboard"></i> Home</li>
            <li>Admin</li>
            <li className="active">Admin Monitor</li>
          </ol>
        </section>
        {/*content*/}
        <div className="content body">
          <div className="row">
            {/*two column view*/}
              <CommonListBox title="Submissions" url="/admin/api/submissions" headers= {["Owner", "Status", "Date", "Detail", "Op"]}
                             data_mapper={submission_mapper}
                             store_id="admin_submission_list" page_size={10} />
              
        
              <CommonListBox title="Users" url="/admin/api/users" headers= {["Email", "Name", "Admin", "Promote", "Demote"]}
                             data_mapper={(u)=>[u.email, u.profile.name, u.isAdmin?"Yes":"No", promote(u), demote(u)]}
                             store_id="admin_user_list" page_size={10} />
              {modalInstance}
          </div>
          
        </div>
      </div>
    )
  }

}

export default AdminMonitorView;
