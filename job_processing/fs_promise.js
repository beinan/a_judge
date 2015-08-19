var shell = require('shelljs');
var path = require('path');
var mkdirp = require('mkdirp');
var fs = require('fs');
var unzip = require('unzip');
var Promise = require('es6-promise').Promise;


exports.mkdirp = function(path){
  return new Promise(
    function(resolve, reject){ 
      mkdirp(path, function (err) {
         console.log("create folder", path);
         if (err) return reject(err);
         return resolve();
      });
    }                  
  );
};

exports.move = function(src_name, dest_name){
  return new Promise(
    function(resolve, reject){
      fs.rename(src_name, dest_name, function (err) {
        console.log("rename", src_name, dest_name);
        
        if (err) return reject(err);
        return resolve();
      });
    }                  
  );
};

exports.unzip = function(zip_filename, dest_folder){
  return new Promise(
    function(resolve, reject){
      var filename_list = [];
      fs.createReadStream(zip_filename)
        .pipe(unzip.Parse())
        .on('entry', function (entry) {
          var fileName = entry.path;
          var type = entry.type; // 'Directory' or 'File'
          var size = entry.size;
          if (fileName) {
            console.log(fileName);
            filename_list.push(fileName);
            entry.pipe(fs.createWriteStream(path.join(dest_folder, fileName)));
          } else {
            entry.autodrain();
          }
        })
        .on('error', function(err){
          console.log(err);
          reject(err);
        })
        .on('close', function(){
          resolve(filename_list);
        });
    }    
  );
}

var crypto = require('crypto');
exports.checksum = function(filename){
  return new Promise(
    function(resolve, reject){
      var hash = crypto.createHash('md5'), 
      stream = fs.createReadStream(filename);
      stream.on('data', function (data) {
        hash.update(data, 'utf8');
      });
      stream.on('error', function(err){
        reject(err);
      });
      stream.on('end', function () {
        resolve(hash.digest('hex')); // get checksum
      });
    }                  
  );  
};
