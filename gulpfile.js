const gulp = require('gulp4');
const exec = require('child_process').exec;
const log = require('fancy-log');
const spawn = require('child_process').spawn;

function run_clang(src_path, dest_path, callback) {
  const clang_build = `clang++ -std=c++14 ${src_path} -lboost_thread-mt -lboost_system-mt -pthread -o ${dest_path}`;

  exec(clang_build, function (error, stdout, stderr) {
    log("Compiled.");
    if (stdout.length > 0) log(stdout);
    if (stderr.length > 0) log(stderr);
    callback();
  });
}

function build(done) {
  run_clang("src/main.cpp", "dist/my_app", done);
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
    log("Started the app!");
    app_instance.on('close', start_app);
    // @TODO: I'm not sure what error these get called in.
    app_instance.on('error', () => { should_stop_spawning = true });
    running_app = app_instance;
    return app_instance;
  }
};

gulp.task('default', gulp.series([ build, watch, serve ]));