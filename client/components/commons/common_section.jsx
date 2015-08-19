import React from 'react'

class CommonSection extends React.Component{
  
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
        {this.props.children}
      </section>
    );
  }
}

export default CommonSection;
