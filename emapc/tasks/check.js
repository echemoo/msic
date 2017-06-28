/**
 * Created by echemoo on 2016/11/26.
 */
module.exports = () => () => require('run-sequence')('check:eslint', 'check:tslint');
