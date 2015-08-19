import React from 'react'

import JobStore from '../stores/job_store'

export class ContentSection extends React.Component{
  
  constructor(props){
    super(props);
  }
  
  render() {
    return (
      <section id={this.props.section_id}>
        <h2 className="page-header"><a href={"#" + this.props.section_id}>{this.props.title}</a></h2>
        <p className="lead">
          {this.props.desc} 
        </p>
        {this.props.content}
      </section>
    );
  }
}

export class ContentBox extends React.Component{
  
  constructor(props){
    super(props);
  }
  
  render() {
    return (
      <div className="box box-primary">
        <div className="box-header with-border">
          <h3 className="box-title">{this.props.title}</h3>
          <span className="label label-primary pull-right"><i className="fa fa-html5"></i></span>
        </div>
        <div className="box-body">
          {this.props.children} {this.props.content}
        </div>
      </div>
    );
  }
}

export class JobOutput extends React.Component{
  constructor(props){
    super(props);
    this.state = {status:"init"}; 
    this.job_store = new JobStore(props.job_id);
    this.job_store.update();
    this._onChange = this._onChange.bind(this);
  }
  
  _onChange(){
    this.setState(this.job_store.data);
    console.log(this.job_store.update);
    if(this.timeout)
      clearTimeout(this.timeout);
    this.timeout = setTimeout(this.job_store.update.bind(this.job_store), 20000);
  }

  componentDidMount() {
    this.job_store.addUpdateEventListener(this._onChange);
  }

  componentWillUnmount() {
    clearTimeout(this.timeout);
    this.job_store.removeUpdateEventListener(this._onChange);
  }

  render(){
    var outputs = "";
    if(this.state.outputs)
      outputs = this.state.outputs.map((o)=> "[" + o.date + "]" + o.line).join('\n');
    console.log("job outputs is rendering",this.state, outputs);
    return (
    
      <pre className="hierarchy bring-up">
        <code className="language-bash" data-lang="bash">
          {outputs}
        </code>
      </pre>


    );
  }
}

export class UploadFileForm extends React.Component{
  
  constructor(props){
    super(props);
    this.handleSubmit = this.handleSubmit.bind(this);
    this.state = {status:"success", msg:'Upload your test cases.'}; //init with 'success' status.
  }
  

  handleSubmit(e){
    e.preventDefault();
    this.setState({status: 'warning', msg: "Uploading, don't close your browser."});
    var formData = new FormData(React.findDOMNode(this.refs.uploadForm));
    $.ajax({
      url: this.props.url,  //Server script to process data
      type: 'POST',
      data: formData,
      cache: false,
      contentType: false,
      processData: false
    }).then(
      (data) => { //ajax request successed
        this.setState({status: 'success', msg: "Upload succeeded."}); 
        console.log("upload successful",data);
        this.setState({job_id: data.job_id});
      },
      (jqXHR, textStatus, errorThrown) => { 
        //ajax request failed
        console.log(jqXHR, textStatus, errorThrown);          
        this.setState({status:'error', msg:jqXHR.responseJSON.msg});
      }
    );
  }
  render() {
    var job_output;
    if(this.state.job_id){
      job_output = <JobOutput job_id ={this.state.job_id} />
    }
    return (
      <form encType="multipart/form-data" onSubmit={this.handleSubmit} id="file_upload_form" ref="uploadForm">
        <div className={"form-group has-" + this.state.status}>          
          <label className="control-label" htmlFor="uploadFile">{this.state.msg}</label>
          <input type="file" name="file" id="uploadFile" />
          <p className="help-block">{this.props.desc}</p>
        </div>
        <button type="submit" className="btn btn-primary">
          <i className="fa fa-upload"></i> Upload
        </button>
        {job_output}        
      </form>
      
    );
  }
}

