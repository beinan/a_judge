import React from 'react'

class MainSideBar extends React.Component{
  render(){
    return (
      <aside className="main-sidebar">
        <section className="sidebar">
          <div className="user-panel">
            <div className="pull-left image">
              <img src="dist/img/user2-160x160.jpg" className="img-circle" alt="User Image" />
            </div>
            <div className="pull-left info">
              <p>Alexander Pierce</p>
            </div>
          </div>
        </section>
      </aside>
    )
  }
}

export default MainSideBar
