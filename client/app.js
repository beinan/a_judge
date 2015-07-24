var $ = global.$ = global.jQuery = require('jquery');
var bootstrap = require('bootstrap');


var CSRF_HEADER = 'X-CSRF-Token';

var setCSRFToken = function(securityToken) {
  jQuery.ajaxPrefilter(function(options, _, xhr) {
    if ( !xhr.crossDomain ) 
        xhr.setRequestHeader(CSRF_HEADER, securityToken);
  });
};

setCSRFToken($('meta[name="csrf-token"]').attr('content'));



//load the js of admin_lte template().
//require('./admin_lte.js');
var React = require('react');
import Frame from './components/frame.jsx';
import AppAction from './actions/app_action.js';

AppAction.setAppHeight($(window).height());
$(window).resize(()=> AppAction.setAppHeight($(window).height()));

import ViewType from './view_type';
AppAction.setView(ViewType.QUESTION_VIEW);

React.render( <Frame/>, document.getElementById('app_wrapper'));
