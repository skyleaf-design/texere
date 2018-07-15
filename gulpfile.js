const gulp = require('gulp4');
const exec = require('child_process').exec;
const log = require('fancy-log');
const spawn = require('child_process').spawn;
const path = require('path');

function run_clang(src_path, dest_path, callback) {
  const clang_build = `clang++ -std=c++14 ${src_path} -lboost_filesystem -lboost_thread-mt -lboost_system-mt -pthread  -o ${dest_path}`;

  exec(clang_build, function (error, stdout, stderr) {
    // @TODO: make the binary executable, so we can call it without the ./
    log("Compiled.");
    if (stdout.length > 0) log(stdout);
    if (stderr.length > 0) log(stderr);
    callback();
  });
}

function build(done) {
  run_clang("src/http_wrapper.cpp", "dist/texere", done);
}

// Disabled, since clang does not use incremental builds and linking.
// Maybe in the future, we can compile everything as a DLL, and then
// just compile only the module that changes, and link everything else.
function watch(done) {
  gulp.watch(['src/http_wrapper.cpp', 'src/texere.hpp'], build);
  done();
};

let running_app = null;
let should_stop_spawning = false;

// @TODO: log PID to disk.  If an existing PID is present, kill it.
function serve(done) {
  let should_stop_spawning = false;
  // @TODO: check pid file: if exists, issue a command to kill that app, and then
  if (!running_app) { start_app(); return; }
  running_app.kill();

  function start_app() {

    if (should_stop_spawning) return;
    log("Attempting to start the app...");
    
    const app_instance = spawn('./texere', [], { stdio: 'inherit', cwd: 'dist' } );
    if (!app_instance) { throw "App failed to start!" }
    log("Started the app!");
    // @TODO: write app_instance.pid to a file.
    app_instance.on('close', start_app);
    app_instance.on('error', (error) => {
      console.log(error);
      should_stop_spawning = true;
    });
    running_app = app_instance;
    return app_instance;
  }
};

gulp.task('default', gulp.series([ build, serve ]));