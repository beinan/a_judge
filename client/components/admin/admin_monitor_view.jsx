import React from 'react'


//import {ContentSection, ContentBox, UploadFileForm} from '../common_components.jsx';

import {AdminJobsBox} from './admin_components.jsx'

class AdminMonitorView extends React.Component{
  constructor(props){
    super(props);
  }
  
  render(){
    
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
            <section className="col-lg-7 connectedSortable ui-sortable">
              <AdminJobsBox />
            </section>
            <section className="col-lg-5 connectedSortable ui-sortable">
              
            </section>
          </div>
          
        </div>
      </div>
    )
  }

}

export default AdminMonitorView;
