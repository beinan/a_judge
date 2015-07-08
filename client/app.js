var $ = global.$ = global.jQuery = require('jquery');
var bootstrap = require('bootstrap');

//load the js of admin_lte template().
require('./admin_lte.js');
var React = require('react');

class App extends React.Component {

  render() {
    return <div>Hello, {this.props.name}!</div>;
  }
}

import Frame from './components/frame.jsx';
React.render( <Frame/>, document.getElementById('app_wrapper'));
