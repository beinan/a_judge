'use strict';

var watchify = require('watchify');
var browserify = require('browserify');
var gulp = require('gulp');
var source = require('vinyl-source-stream');
var buffer = require('vinyl-buffer');
var gutil = require('gulp-util');
var sourcemaps = require('gulp-sourcemaps');
var assign = require('lodash.assign');

var babelify = require('babelify');
// add custom browserify options here
var customOpts = {
  entries: ['./client/app.js'],
  debug: true
};
var opts = assign({}, watchify.args, customOpts);
var b = watchify(browserify(opts)); 
b.transform(babelify);

gulp.task('js', bundle); // so you can run `gulp js` to build the file
b.on('update', bundle); // on any dep update, runs the bundler
b.on('log', gutil.log); // output build logs to terminal

function bundle() {
  return b.bundle()
    // log errors if they happen
    .on('error', function(err) {console.log(err.toString(),"\n",err.codeFrame);})
    .pipe(source('application.js'))
    // optional, remove if you don't need to buffer file contents
    .pipe(buffer())
    // optional, remove if you dont want sourcemaps
    //.pipe(sourcemaps.init({loadMaps: true})) // loads map from browserify file
       // Add transformation tasks to the pipeline here.
    //.pipe(sourcemaps.write('./')) // writes .map file   
    .pipe(gulp.dest('./public/js'));
}

gulp.task("watch", function(){
  var nodemon = require('gulp-nodemon');
  nodemon({script:'./app', ext:"js"});
});
gulp.task("default", ["js","watch"]);
