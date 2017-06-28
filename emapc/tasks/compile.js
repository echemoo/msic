/**
 * Created by echemoo on 2016/11/26.
 */
module.exports = (gulp, src, cb, params) => {
    cb = cb || function () {};

    return (done) => runTypeScriptCompiler(done);

    function runTypeScriptCompiler(done) {
        const cp = require('child_process');
        const childProcess = cp.spawn('node', getCompilerCommand(), {cwd: process.cwd()});
        done = done || function () {};
        childProcess.stdout.on('data', (data) => console.log(data.toString()));
        childProcess.stderr.on('data', (data) => console.log(data.toString()));
        childProcess.on('close', () => {
            cb();
            done();
        });
    }

    function getCompilerCommand() {
        params = params
            ? [params].concat(['--experimentalDecorators', '--module', 'amd', '--target', 'es5', '--sourceMap'])
            : ['-p', src];
        const path = require('path');
        const tscpath = path.join(process.cwd(), 'node_modules', 'typescript', 'bin', 'tsc');
        return [tscpath].concat(params);
    }

};
