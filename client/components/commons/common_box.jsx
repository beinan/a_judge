import React from 'react'

class CommonBox extends React.Component{
  
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
          {this.props.children} 
        </div>
        <div className="box-footer clearfix no-border">
          {this.props.footer}
        </div>
      </div>
    );
  }
}

export default CommonBox;
