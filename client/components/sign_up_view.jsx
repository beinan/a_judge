import React from 'react'

class SignUpView extends React.Component{
  constructor(props){
    super(props);
    this.handleSubmit = this.handleSubmit.bind(this);
  }
  handleSubmit(e){
    e.preventDefault();
    var email = React.findDOMNode(this.refs.email).value.trim();
    var password = React.findDOMNode(this.refs.password).value;
    var confirmPassword = React.findDOMNode(this.refs.confirmPassword).value;
    //todo: validation
    $.post('/signup', $('#signup_form').serialize())
  }
  render(){
    return (
      <section className="content">
        <div className="row">
          <div className="box box-primary">
            <div className="box-header">
              <h3 className="box-title">Sign Up</h3>
            </div>
            <form onSubmit={this.handleSubmit} id="signup_form">
            <div className="box-body">
               <div className="form-group">
                  <label htmlFor="signupInputEmail1">Email address</label>
                  <input type="email" className="form-control" id="signupInputEmail1" name="email" ref="email" placeholder="Enter email" />
               </div>
               <div className="form-group">
                  <label htmlFor="signupInputPassword1">Password</label>
                  <input type="password" className="form-control" id="signupInputPassword1" name="password" ref="password" placeholder="Password" />
               </div>
               <div className="form-group">
                  <label htmlFor="signupInputPassword2">Confirm Password</label>
                  <input type="password" className="form-control" id="signupInputPassword2" name="confirmPassword" ref="confirmPassword" placeholder="Confirm Password" />
               </div>
            </div>
            <div className="box-footer">
               <button type="submit" className="btn btn-primary">Submit</button>
            </div>   
            </form>
          </div>
        </div>
      </section>
    )
  }
}

export default SignUpView
