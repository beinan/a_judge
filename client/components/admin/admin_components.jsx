import React from 'react'


import {ContentSection, ContentBox, UploadFileForm} from '../common_components.jsx';

import AdminAction from '../../actions/admin_action.js'

import AdminJobStore from '../../stores/admin_jobs_store.js'

/*List jobs and pagination in a box*/ 
export class AdminJobsBox extends React.Component{
  constructor(props){
    super(props);
    this.state = AdminJobStore.getData();
    this._onChange = this._onChange.bind(this);
  }
  
  componentDidMount() {
    AdminAction.queryJobs(0, 10);
    AdminJobStore.addEventListener(AdminJobStore.JOBS_UPDATE_EVENT, this._onChange);
  }

  componentWillUnmount() {
    AdminJobStore.removeEventListener(AdminJobStore.JOBS_UPDATE_EVENT, this._onChange);
  }

  _onChange() {
    this.setState(AdminJobStore.getData());
  }
  
  render(){
    console.log("job list",this.state);
    var jobs;
    if(this.state.status !== "ready")
      jobs = <p>Loading</p>
    else{
      var job_items = this.state.jobs.map((job_data)=>
        <li>
         <span className="text">Owner:{job_data.owner.email} <small>{job_data.date}</small></span>
         <small className="label label-danger"><i className="fa fa-clock-o"></i> {job_data.status}</small>
        </li>   
      );
      jobs = ( 
        <ul className="todo-list ui-sortable">
          {job_items}
        </ul>
      );
    }
    return (
      <ContentBox title="On-processing Jobs" content={jobs}/>
    )
  }
}

