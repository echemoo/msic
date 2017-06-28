/**
* @construcor math.type.Unit
*
* @param {Number} {value} 单位对象的值，例如 5.2
* @param {String} {prefixUnit} 单位 例如 "cm" 或 "inch"
*/
function Unit(value, prefixUnit) {
    if (this.constructor != Unit) {
        throw new Error('Unit constructor must be called with the new operator');
    }
    this.value = 1;
    this.unit = prefixUnit;
}

math.type.Unit = Unit;
