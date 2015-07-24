import React from 'react'

import AssignmentsStore from '../stores/assignments_store';
import AssignmentsAction from '../actions/assignments_action';
import {ContentSection, ContentBox, UploadFileForm} from './common_components.jsx';


class AssignmentListBox extends React.Component{
  constructor(props){
    super(props);
    this.state = AssignmentsStore.getData();
    this._onChange = this._onChange.bind(this);
  }
  
  componentDidMount() {
    AssignmentsAction.queryAssignments(0, 20);
    AssignmentsStore.addEventListener(AssignmentsStore.ASS_UPDATE_EVENT, this._onChange);
  }

  componentWillUnmount() {
    AssignmentsStore.removeEventListener(AssignmentsStore.ASS_UPDATE_EVENT, this._onChange);
  }

  _onChange() {
    this.setState(AssignmentsStore.getData());
  }
  
  _ass_onClick(id, e){
    e.preventDefault();
    AssignmentsAction.activeAssignment(id);
  }
  render(){
    console.log("Assignment list",this.state);
    var assignments;
    if(this.state.status !== "ready")
      assignments = <p>Loading</p>
    else{
      var ass_items = this.state.assignments.map((data)=>
         <li key={data._id}>
           <a href="#" onClick = {this._ass_onClick.bind(this, data._id)}>
             <span className="text">{data.title} <small>{data.date}</small></span>
             <small className="label label-danger"><i className="fa fa-clock-o"></i> {data.status}</small>
           </a>
         </li>   
         );
      assignments = ( 
        <ul className="todo-list ui-sortable">
          {ass_items}
        </ul>
      );
    }
    return (
      <ContentBox title="Assignments List" content={assignments}/>
    )
  }
}


class AssignmentDetail extends React.Component{
  constructor(props){
    super(props);
    //this._onChange = this._onChange.bind(this);
  }
  
  componentDidMount() {
    //AssignmentsStore.addEventListener(AssignmentsStore.ACTIVE_ASSIGNMENT_EVENT, this._onChange);
  }

  componentWillUnmount() {
    //AssignmentsStore.removeEventListener(AssignmentsStore.ACTIVE_ASSIGNMENT_EVENT, this._onChange);
  }

  //_onChange() {
    //this.setState(AssignmentsStore.getActiveAssignment());
  //}

  render(){
    return (
      <div>{this.props.assignment.title}</div>
    );
  }

}

class AssignmentView extends React.Component{
  constructor(props){
    super(props);
    this.state = AssignmentsStore.getActiveAssignment();
    this._onChange = this._onChange.bind(this);
  }
  
  componentDidMount() {
    AssignmentsStore.addEventListener(AssignmentsStore.ACTIVE_ASSIGNMENT_EVENT, this._onChange);
  }

  componentWillUnmount() {
    AssignmentsStore.removeEventListener(AssignmentsStore.ACTIVE_ASSIGNMENT_EVENT, this._onChange);
  }

  _onChange() {
    //console.log("active assignment", AssignmentsStore.getActiveAssignment());
    this.setState(AssignmentsStore.getActiveAssignment());
  }

 
  render(){
    var active_ass = null;
    if(this.state){
      active_ass = <AssignmentDetail assignment={this.state} />
    }
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
            <AssignmentListBox />
            {active_ass}
          </div>
          
        </div>
      </div>
    )
  }

}

export default AssignmentView;
