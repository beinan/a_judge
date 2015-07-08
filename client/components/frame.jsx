import React from 'react';

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
        <a href="index2.html" className="logo">
          <span className="logo-mini"><b>J</b>BD</span>
          <span className="logo-lg"><b>Bug</b>Digger</span>
        </a>
        <TopNavBar/>
      </header>
    )
  }  
}

import MainSideBar from './main_side_bar.jsx'
 
class Frame extends React.Component {
  render() {
    return (
      <div className="wrapper">
        <Header/>
        <MainSideBar/>
      </div>
    );
  }
}
 
export default Frame;
