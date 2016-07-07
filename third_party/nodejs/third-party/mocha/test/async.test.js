const chai = require('chai');
const assert = chai.assert;
const expect = chai.expect;

it('测试应该2000毫秒后结束', function(done) {
  var x = true;
  var f = function() {
    x = false;
    expect(x).to.be.ok;
    done(); // 通知Mocha测试结束
  };
  setTimeout(f, 2000);
});