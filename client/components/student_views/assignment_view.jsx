import React from 'react'

import AssignmentsStore from '../../stores/assignments_store';
import AssignmentsAction from '../../actions/assignments_action';
import {ContentSection, ContentBox, UploadFileForm} from '../common_components.jsx';

import CommonSection from '../commons/common_section.jsx'
import CommonListBox from '../commons/common_list_box.jsx'



import {Badge, Button, Label, Input, Modal} from 'react-bootstrap'

import moment from 'moment';

import marked from 'marked';



class AssignmentView extends React.Component{
  constructor(props){
    super(props);
    this.state = {};
    this.renderModal = this.renderModal.bind(this);
  }
  
  renderModal(){
    if(!this.state.currentAssign)
      return null;
    return (
      <div>
        <Modal show={this.state.showModal} onHide={()=>this.setState({showModal:false})}>
          <Modal.Header closeButton>
            <Modal.Title>{this.state.currentAssign.title}</Modal.Title>
          </Modal.Header>

          <Modal.Body>
            <dl>
              <dt>Description</dt>
              <dd dangerouslySetInnerHTML={{__html:marked(this.state.currentAssign.desc)}}></dd>
              
              <dt>Submit your solution</dt>
              <dd>
                <UploadFileForm title="Upload your solution." 
                                desc="Your solution have to be packed as a Zip file"
                                url = {'/upload_solution/' + this.state.currentAssign.assign_num}
                />        

              </dd>
            </dl>
            
          </Modal.Body>

          <Modal.Footer>
            <Button onClick={()=>this.setState({showModal:false})}>Close</Button>
          </Modal.Footer>

        </Modal>
      </div>
    );
  }
 
  render(){
    var assign_click = (a) => {
      console.log("modify on ", a);
      this.setState({showModal: true, currentAssign: a});
    }
    var assign_mapper = (a) => {
      var button = <button className="btn btn-block btn-primary" style={{width: 70}} onClick={assign_click.bind(null,a)} >Detail</button>
      return [a.assign_num, a.title,  moment(a.date).format("dddd, MMMM Do YYYY, h:mm:ss a"), button]
    }
    var modal = this.renderModal(this.state.showModal, this.state.currentAssign);
    return (
      <div>
        {/*header*/}
        <section className="content-header">
          <h1>
            Assignments
          </h1>
          <ol className="breadcrumb">
            <li><i className="fa fa-dashboard"></i> Home</li>
            <li className="active">Assignment</li>
          </ol>
        </section>
        {/*content*/}
        <div className="content body">
          <div className="row">
            <CommonSection section_id="assignments" title="Assignments" 
                           desc="" >
              <CommonListBox url="/api/assignments" headers= {["#Num", "Title", "Due", "Admin"]}
                             data_mapper={assign_mapper}
                             store_id="assignment_list" page_size={10} />
              
            </CommonSection>

            {modal}
          </div>
          
        </div>
      </div>
    )
  }

}

export default AssignmentView;
