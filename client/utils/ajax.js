var Promise = require('es6-promise').Promise;
var $ = require('jquery');

exports.getJson = function(url, data){
  return new Promise( (resolve, reject) =>  {
      $.getJSON(url,data).then((data) => resolve(data), (jqXHR, textStatus, err) => reject(err) );
  });
};

exports.postJson = function(url, data){
  return new Promise( (resolve, reject) =>  {
    console.log("port json", url, data);
    $.ajax({
      type: "POST",
      url: url,
      data: JSON.stringify(data),
      contentType: "application/json; charset=utf-8",
      dataType: "json"
    }).then(
      (data) => resolve(data), 
      (jqXHR, textStatus, err) => reject(err) 
    );
  });
};

