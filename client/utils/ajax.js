var Promise = require('es6-promise').Promise;
var $ = require('jquery');

exports.getJson = function(url, data){
  return new Promise( (resolve, reject) =>  {
      $.getJSON(url,data).then((data) => resolve(data), (jqXHR, textStatus, err) => reject(err) );
  });
};

