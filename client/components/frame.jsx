import React from 'react';
import AppStore from '../stores/app_store'

class TopNavBar extends React.Component{
  render(){
    return (
      <nav className="navbar navbar-static-top" role="navigation">
      </nav>  
    )
  }
}

class Header extends React.Component{
  render() {
    return (
      <header className="main-header">
        <a href="#" className="logo">
          <span className="logo-mini"><b>J</b></span>
          <span className="logo-lg"><b>A</b>Judge</span>
        </a>
        <TopNavBar/>
      </header>
    )
  }  
}

import MainSideBar from './main_side_bar.jsx'
import ContentWrapper from './content_wrapper.jsx'
 
class Frame extends React.Component {
  constructor(props) {
    super(props);
    this.state = AppStore.getData();
    this._onChange = this._onChange.bind(this);
  }
    
  

  componentDidMount() {
    AppStore.addEventListener(AppStore.HEIGHT_CHANGE_EVENT, this._onChange);
  }

  componentWillUnmount() {
    AppStore.removeEventListener(AppStore.HEIGHT_CHANGE_EVENT , this._onChange);
  }

  render() {
    return (
      <div className="wrapper" style={{height:this.state.height, overflowY:'auto'}}>
        <Header/>
        <MainSideBar/>
        <ContentWrapper/>
      </div>
    );
  }
  _onChange() {
    this.setState(AppStore.getData());
  }
}
 
export default Frame;
