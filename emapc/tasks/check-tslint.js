/**
 * Created by echemoo on 2016/11/26.
 */
module.exports = (gulp, directory, configuration) => () => {
  const path = require('path');
  const tslint = require('gulp-tslint');

  return gulp.src([
    path.join(directory, '**', '*.ts'),
    path.join('!', directory, 'references.ts')
  ]).pipe(tslint({
    configuration: require(configuration),
    formatter: 'verbose'
  })).pipe(tslint.report());
};
