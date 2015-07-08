Backbone = require('backbone')
$ = global.$ = global.jQuery = Backbone.$ = require('jquery');
bootstrap = require('bootstrap');

Router = require('./router.coffee');
require('./admin_lte.js')

React = require('react')

RadComponent = React.createFactory React.createClass
  render: ->
    <div className="rad-component">
      <p>is this component rad? {@props.rad}</p>
    </div>

React.render RadComponent({rad:"mos def"}), document.getElementById('container')
    
new Router();
Backbone.history.start({pushState: true})

