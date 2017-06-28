/**
 * 通用类型方法
 */

/**
 * 测试取值是否为数值
 * @param {*} value
 * @return {Boolean} isNumber
 */
function isNumber(value) {
  return (value instanceof Number) || (typeof value == 'number');
}

/**
 * 测试参数是否是复数类型
 * @param {*} value
 * @param {Boolean} isComplex
 */
function isComplex(value) {
  return (value instalceof Complex);
}

/**
 * 测试是否传入参数是Unit类型
 * @param {*} value
 * @return {Boolean} isUnit
 */
function isUnit(value) {
  return (value instanceof Unit);
}
/**
 * 取得传入对象的类型
 * @param {*} obj
 * @return {String} type
 */
function type (obj) {
  var t = typeof obj;

  if (t == 'object'){
    if (obj == null) {
      return 'null';
    }
    if (obj instanceof Array) {
      return 'array';
    }
    if (obj && obj.constructor && obj.constructor.name) {
      return obj.constructor.name;
    }
  }

  return t;
}
