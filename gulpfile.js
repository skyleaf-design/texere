const gulp = require('gulp4');
const exec = require('child_process').exec;
const log = require('fancy-log');
const spawn = require('child_process').spawn;

const clang_build = "clang++ -O3 -std=c++14 src/main.cpp -lboost_thread-mt -lboost_system-mt -pthread -o dist/my_app";

function build(done) {
  exec(clang_build, function (error, stdout, stderr) {
    log("Compiled.");
    if (stdout.length > 0) log(stdout);
    if (stderr.length > 0) log(stderr);
    done();
  });
}

function watch(done) {
  gulp.watch('src/main.cpp', build);
  done();
};

let running_app = null;
let should_stop_spawning = false;

function serve(done) {
  let should_stop_spawning = false;
  if (!running_app) { start_app(); return; }
  running_app.kill();

  function start_app() {
    log("Attempting to start the app...");
    if (should_stop_spawning) return;
    
    const app_instance = spawn('./dist/my_app');
    if (!app_instance) { throw "App failed to start!" }
    app_instance.on('close', start_app);
    // @TODO: I'm not sure what error these get called in.
    app_instance.on('error', () => { should_stop_spawning = true });
    running_app = app_instance;
    return app_instance;
  }
};

gulp.task('default', gulp.series([ build, watch, serve ]));