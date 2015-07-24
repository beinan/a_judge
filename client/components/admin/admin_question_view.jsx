import React from 'react'


import {ContentSection, ContentBox, UploadFileForm} from '../common_components.jsx';

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
  }
  
  render(){
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
          <ContentSection section_id="introduction" title="Introduction" desc="TODO: introduction text" />
          <ContentSection section_id="import" title="Import" desc="TODO: import test cases desc text" content={<ImportTestCaseComponent />}/>
          
          
        </div>
      </div>
    )
  }

}

export default AdminQuestionView
