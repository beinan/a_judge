import React from 'react'
import ViewType from '../view_type'
import SessionStore from '../stores/session_store'
import AppStore from '../stores/app_store'

import AppAction from '../actions/app_action'

class MenuItem extends React.Component{

  constructor(props) {
    super(props);
    this.state = {is_active : AppStore.getData().view_name == props.view_name};
    this._onChange = this._onChange.bind(this);
    this._handleClick = this._handleClick.bind(this);
  }
    
  

  componentDidMount() {
    AppStore.addEventListener(AppStore.VIEW_CHANGE_EVENT, this._onChange);
  }

  componentWillUnmount() {
    AppStore.removeEventListener(AppStore.VIEW_CHANGE_EVENT , this._onChange);
  }

  render() {
    console.log("menu item is rendering", this.props);
    var li_class = "";
    if(this.state.is_active){
      li_class = "active";
    }
    return (
      <li className={li_class}>
        <a href="#" onClick={this._handleClick}>
          <i className='fa fa-link'></i> 
          <span>{this.props.title}</span>
        </a>
      </li>           
    );
  }

  _onChange() {
    var is_active = (AppStore.getData().view_name === this.props.view_name);
    if(is_active !== this.state.is_active)
      this.setState({is_active : is_active});
  }
 
  _handleClick(e){
    console.log("menu item onclick", this.props);
    e.preventDefault();
    AppAction.setView(this.props.view_name);
  }
}

class MainSideBar extends React.Component{
  constructor(props) {
    super(props);
    this.state = SessionStore.getData();
    this._onChange = this._onChange.bind(this);
  }
    
  

  componentDidMount() {
    SessionStore.addEventListener(SessionStore.SESSION_READY_EVENT, this._onChange);
  }

  componentWillUnmount() {
    SessionStore.removeEventListener(SessionStore.SESSION_READY_EVENT , this._onChange);
  }

  _onChange() {
     this.setState(SessionStore.getData());
  }
  

  render(){
    console.log("onchange", this.state);   
    var userPanel = <div className="user-panel"> Loading... </div>;
    var sideBarMenu = null;
    var admin_menus = [];
    if(this.state.status !== "init"){
      userPanel = (<div className="user-panel">
            <div className="pull-left image">
              <img src="/images/user2.jpg" className="img-circle" alt="User Image" />
            </div>
            <div className="pull-left info">
              <p>{this.state.email}</p>
              <a href="/account"><i className="fa fa-circle text-success"></i> Online</a>
            </div>
          </div>);
      admin_menus = this.state.isAdmin?[
        <li className="header" key="admin_menu_section">Admin Menu</li>, 
        <MenuItem key="admin_questions" view_name={ViewType.ADMIN_QUESTION_VIEW} title="Admin Questions" />,
        <MenuItem key="admin_monitor" view_name={ViewType.ADMIN_MONITOR_VIEW} title="Monitor" />,
        <MenuItem key="admin_grades" view_name={ViewType.ADMIN_GRADE_VIEW} title="Grades" />
      ]:null
      sideBarMenu = (
          <ul className="sidebar-menu">
            <li className="header" key="main_menu_section">Main Menu</li>
            <MenuItem view_name={ViewType.ASSIGNMENT_VIEW} title="Assignments" />
            <MenuItem view_name={ViewType.STUDENT_SUBMISSION_VIEW} title="My Submissions" />
            <MenuItem view_name={ViewType.STUDENT_GRADE_VIEW} title="My Grades" />
            <li>
              <a href="/forum">
                <i className='fa fa-link'></i> 
                <span>Forum</span>
              </a>
            </li>           
            <li>
              <a href="/account">
                <i className='fa fa-link'></i> 
                <span>My Account</span>
              </a>
            </li>           
            {admin_menus}    
          </ul>
      );
    }
    console.log(userPanel);
    return (
      <aside className="main-sidebar">
        <section className="sidebar" style={{height: "300px"}}>
          {userPanel}
          {sideBarMenu}
        </section>
      </aside>
    )
  }
}

export default MainSideBar
