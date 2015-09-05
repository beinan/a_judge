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
            if(type == "File"){
              filename_list.push(fileName);
              entry.pipe(fs.createWriteStream(path.join(dest_folder, fileName)));
            }
            
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

var ignorePrefixes = ["Grader","AbstractGrader","main","Date","Random","Stopwatch","UnixStopwatch","WindowsStopwatch",
                     "GoldPriorityQueue", "Commands"];
function isFileIgnored(filename){
  for(var i in ignorePrefixes){
    if(filename.indexOf(ignorePrefixes[i]) == 0){
      return true;
    }
  }
  return false;
}

exports.unzipSource = function(zip_filename, dest_folder){
  
  return new Promise(
    function(resolve, reject){
      var filename_list = [];
      fs.createReadStream(zip_filename)
        .pipe(unzip.Parse())
        .on('entry', function (entry) {
          var fileName = entry.path;
          var type = entry.type; // 'Directory' or 'File'
          var size = entry.size;
          //console.log(fileName);
          if(type != "File"){
            reject("You cannot contain sub-folder in your zip file.");
            return;
          }else if(path.extname(fileName) != ".cpp" && path.extname(fileName) != ".h"){
            reject("You cannot contain files other than '*.cpp' and '*.h'");
            return;
          }
          if( !isFileIgnored(fileName)){
            filename_list.push(fileName);
            entry.pipe(fs.createWriteStream(path.join(dest_folder, fileName)));
          }
          else {
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

exports.readFile = function(filename){
  return new Promise(
    function(resolve, reject){
      fs.readFile(filename, "utf-8", function(err, data){
        if(err)
          reject(err);
        else
          resolve(data);
      });
    }
  );
  
};
exports.cppStlChecking = function(source_folder, is_vector_allowed, filename_list){
  var checking_promises = [];
  for(var i in filename_list){
    var filename = path.join(source_folder, filename_list[i]);
    var p = exports.readFile(filename).then(check.bind(null, filename_list[i], is_vector_allowed));
    checking_promises.push(p);
  }
  return Promise.all(checking_promises).then(console.log);
  
};

function check(filename, is_vector_allowed, content){
  try{
    //console.log("checking:", content);
    var invalid_list = ["array","bitset","deque","forward_list","list","map","queue",
                        "set","stack","unordered_map","algorithm"];
    if(!is_vector_allowed)
      invalid_list.push("vector");
    var include_files = parse_cpp(content);
    for(var i in include_files){
      if(invalid_list.indexOf(include_files[i]) != -1){
        throw "Including STL library:" + include_files[i] + " (in " + filename + ") is not allowed in this homework.";
      }
    }
  }catch(e){
    console.log(e, e.stack);
    throw e;
  }
  return true;

}

var TYPE_FREE = 0;
var TYPE_COMMENT = 1;
var TYPE_STRING = 2;
var TYPE_CHAR = 3;
var TYPE_DEFINE = 4;

function onlyWhitespace(str){
  for(var i = 0; i < str.length; ++i){
    var c = str[i];
    if(c != ' ' && c != '\n'){
      return false;
    }
  }
  return true;
}

function insideEscape(contents, index){
    var count = 0;
    for(var i = index; i >= 0; --i){
      var c = contents[i];
      if(c == '\\'){
        ++count;
      } else {
        break;
      }
    }
    if(count % 2 == 0){
      return false;
    } else {
      return true;
    }
  }

function parse_cpp(contents){
  var accum = "";
  var state = TYPE_FREE;
  var includes = [];
  for(var i = 0, len = contents.length; i < len; i++){
    var c = contents[i];
    var cc = '\0';
    if(i < len - 1){
      cc = contents[i+1];
    }
      
    switch(state){
    case TYPE_FREE:
      if(c == '/' && cc == '/'){
        //if(accum.length != 0){
          //ret.add(new Segment(accum.toString(), TYPE_FREE));
        //}
        accum = "//";
        state = TYPE_COMMENT;
        ++i;
      } else if(c == '\"'){
        //if(accum.length != 0){
          //ret.add(new Segment(accum.toString(), TYPE_FREE));
        //}
        accum = "\"";
        state = TYPE_STRING;
      } else if(c == '\''){
        //if(accum.length != 0){
          //ret.add(new Segment(accum.toString(), TYPE_FREE));
        //}
        accum = "\'";
        state = TYPE_CHAR;
      } else if(c == '#' && onlyWhitespace(accum)){
        //if(accum.length != 0){
              //ret.add(new Segment(accum.toString(), TYPE_FREE));
        //}
        accum = ("#");
        state = TYPE_DEFINE;
      } else if(c == '}' || c == '{'){
        accum +=c ;
        //ret.add(new Segment(accum.toString(), TYPE_FREE));
        accum = "";
      } else if(c == '\n'){
        //if(accum.length != 0){
          //ret.add(new Segment(accum.toString(), TYPE_FREE));
        //}
        accum = "";
      } else {
        accum +=c;
      }
      break;
    case TYPE_COMMENT:
      if(c == '\n'){
        if(insideEscape(contents, i - 1)){
          accum += c;
        } else {
          //if(accum.length != 0){
            //ret.add(new Segment(accum.toString(), TYPE_COMMENT));
          //}
          accum = "";
          state = TYPE_FREE;
        }
      } else {
        accum += c;
      }
      break;
    case TYPE_STRING:
      if(c == '\"'){
        if(insideEscape(contents, i - 1)){
          accum += c;
        } else {
          accum += c;
          //ret.add(new Segment(accum.toString(), TYPE_STRING));
          accum = "";
          state = TYPE_FREE;
        }
      } else {
        accum += c;
      }
      break;
    case TYPE_CHAR:
      if(c == '\''){
        if(insideEscape(contents, i - 1)){
          accum += c;
        } else {
          accum += c;
          //ret.add(new Segment(accum.toString(), TYPE_CHAR));
          accum = "";
          state = TYPE_FREE;
        }
      } else {
        accum +=c ;
      }
      break;
    case TYPE_DEFINE:
      if(c == '\n'){
        if(insideEscape(contents, i - 1)){
          accum += c;
        } else {
          if(accum.length != 0 && accum.indexOf("#include") == 0){
            includes.push(getFile(accum));
          }
          accum = "";
          state = TYPE_FREE;
        }
      } else {
        accum +=c ;
      }
      break;
    }
    
  }

  if(accum.length != 0 && state== TYPE_DEFINE && accum.indexOf("#include") == 0){
    includes.push(getFile(accum));
  }
  console.log("including:", includes);
  return includes;
}

function getFile(include_stm){
  var index1, index2;
  if((include_stm.indexOf("\"") != -1) && (include_stm.indexOf("<") == -1)){
    index1 = include_stm.indexOf("\"");
    var str = include_stm.substring(index1+1);
    index2 = str.indexOf("\"");
    str = str.substring(0, index2);
    return str;
  }else if((include_stm.indexOf("\"") == -1) && (include_stm.indexOf("<") != -1)){
    index1 = include_stm.indexOf("<");
    index2 = include_stm.indexOf(">");
    return include_stm.substring(index1+1, index2);
      
  }else
    return "";
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
