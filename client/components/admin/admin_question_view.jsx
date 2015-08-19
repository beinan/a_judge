import React from 'react'


import {ContentSection, ContentBox, UploadFileForm} from '../common_components.jsx';

import CommonSection from '../commons/common_section.jsx'
import CommonListBox from '../commons/common_list_box.jsx'

import CommonAction from '../../actions/common_action'

import {Button, Label, Input, Modal} from 'react-bootstrap'

import {postJson} from '../../utils/ajax'

import moment from 'moment';

class ImportTestCaseComponent extends React.Component{
  constructor(props){
    super(props);
  }

  render(){ 
    var import_box_content = (
      <UploadFileForm title="Upload Test Cases" 
                      desc="Your test cases have to be packed as a Zip file"
                      url = '/admin/import_cpp_grader'
      />        
    )
    return (
      <div className="row">
        <div className="col-sm-6">
          <ContentBox title="Import" content={import_box_content}/>
        </div>
      </div>      
    );
  }
}
class AdminQuestionView extends React.Component{
  constructor(props){
    super(props);
    this.state = {};
  }
  
  render(){
    var save_assignment = ()=>{
      postJson("/admin/update_assign", 
               {title: this.refs.title_input.getValue(),
               desc: this.refs.desc_input.getValue(),
               date: this.refs.due_date_input.getValue(),
               isPublic: this.refs.is_pub_input.getChecked(),
               _id: this.state.currentAssign._id})
           .then((data)=>{
             alert("Assignment saved.");
             this.setState({showModal:false});
             CommonAction.listDataEntryUpdate("admin_assignment_list", data);
           })
           .catch(console.log);
    }
    var modalInstance = (
      <div>
        <Modal show={this.state.showModal} onHide={()=>this.setState({showModal:false})}>
          <Modal.Header closeButton>
            <Modal.Title>Modify Assignment</Modal.Title>
          </Modal.Header>

          <Modal.Body>
            <Label>{this.state.currentAssign?this.state.currentAssign.assign_num:""}</Label>
            <Input type='text' style={{color:"black"}} defaultValue={this.state.currentAssign?this.state.currentAssign.title:""} ref='title_input' label='Title'/>
            <Input type='text' style={{color:"black"}} defaultValue={this.state.currentAssign?moment(this.state.currentAssign.date).format():""} ref='due_date_input' label='Due Date'/>
            <Input type='checkbox' label='Public' defaultChecked={this.state.currentAssign?this.state.currentAssign.isPublic:false} ref="is_pub_input"/> 
            <Input type='textarea' style={{color:"black"}} defaultValue={this.state.currentAssign?this.state.currentAssign.desc:""} ref='desc_input' label='Description'/>
          </Modal.Body>

          <Modal.Footer>
            <Button onClick={()=>this.setState({showModal:false})}>Close</Button>
            <Button bsStyle='primary' onClick={save_assignment}>Save changes</Button>
          </Modal.Footer>

        </Modal>
      </div>
    );
    var assign_click = (a) => {
      console.log("modify on ", a);
      this.setState({showModal: true, currentAssign: a});
    }
    var assign_mapper = (a) => {
      var button = <button className="btn btn-block btn-primary" style={{width: 70}} onClick={assign_click.bind(null,a)}>Modify</button>
      return [a.assign_num, a.title, a.isPublic?"true":"false", moment(a.date).format("dddd, MMMM Do YYYY, h:mm:ss a"), button]
    }
    return (
      <div>
        {/*header*/}
        <section className="content-header">
          <h1>
            Questions
            <small>Create or modify questions</small>
          </h1>
          <ol className="breadcrumb">
            <li><i className="fa fa-dashboard"></i> Home</li>
            <li>Admin</li>
            <li className="active">Admin Questions</li>
          </ol>
        </section>
        {/*content*/}
        <div className="content body">
          <div className="row">

            <CommonSection section_id="introduction" title="Introduction" desc="TODO: introduction text" />
            <CommonSection section_id="import" title="Import" 
                            desc="TODO: import test cases desc text" >
              <ImportTestCaseComponent />
            </CommonSection>
            <CommonSection section_id="assignments" title="Assignments" 
                            desc="" >
              <CommonListBox url="/admin/api/assignments" headers= {["#Num", "Title", "Public", "Due", "Admin"]}
                             data_mapper={assign_mapper}
                             store_id="admin_assignment_list" page_size={10} />
              
            </CommonSection>

            
          </div>
          {modalInstance}
        </div>
      </div>
    )
  }

}

export default AdminQuestionView
