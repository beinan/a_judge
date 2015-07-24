
import React from 'react'
import AppStore from '../stores/app_store'

import ViewType from '../view_type.js'

import SignUpView from './sign_up_view.jsx'
import UserGradeView from './user_grade_view.jsx'
import AdminQuestionView from './admin/admin_question_view.jsx'
import AdminMonitorView from './admin/admin_monitor_view.jsx'

import AssignmentView from './assignment_view.jsx'

var view_map = {
  [ViewType.ASSIGNMENT_VIEW]: <AssignmentView/>,
  [ViewType.QUESTION_VIEW]: <SignUpView/>,
  [ViewType.USER_GRADE_VIEW]: <UserGradeView/>,
  [ViewType.ADMIN_QUESTION_VIEW]: <AdminQuestionView/>,
  [ViewType.ADMIN_MONITOR_VIEW]: <AdminMonitorView/>

};

class ContentWrapper extends React.Component{
  constructor(props) {
    super(props);
    
    this.state = {view_name: AppStore.getData().view_name};
    this._onChange = this._onChange.bind(this);
  }
    
  

  componentDidMount() {
    AppStore.addEventListener(AppStore.VIEW_CHANGE_EVENT, this._onChange);
  }

  componentWillUnmount() {
    AppStore.removeEventListener(AppStore.VIEW_CHANGE_EVENT , this._onChange);
  }

 
  _onChange() {
    this.setState( {view_name: AppStore.getData().view_name});
  }
  
  render(){
    return (
      <div className="content-wrapper">
        {view_map[this.state.view_name]}
      </div>
    )
  }
}

export default ContentWrapper
