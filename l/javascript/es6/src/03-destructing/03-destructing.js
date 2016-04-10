"use strict"

//  目前node需要这个 flag
// --harmony_destructuring 或者使用 babel-node
// ../../node_modules/.bin/babel-node file.js

// 解构赋值不仅适用于var命令，也适用于let和const命令。

// var [v1, v2, ..., vN ] = array;
// let [v1, v2, ..., vN ] = array;
// const [v1, v2, ..., vN ] = array;

// var { foo: f1, bar: f2, baz: f3} = { foo: "a", bar:"b", baz: "c"}
// 对象的解构赋值的内部机制，是先找到同名属性，然后再赋给对应的变量。真正被赋值的是后者(f1,f2,f3)，而不是前者

{
    let [a, b, c] = [1, 2, 3];
    console.log(a,b,c);
}

{
    let [ , , third] = ['one', 'two', 'three'];
    console.log(third);
}

{
    let [x, , y] = [1, 2, 3];
    console.log(x, y);
}

{
    let [foo, [[bar], baz]] = [1, [[2], 3]];
    console.log(foo, bar, baz);
}

{
   // tail and z1 is an array
    let [head, ...tail] = [1, 2, 3, 4];
    console.log('head:' + head + ',tail:' + tail);

    let [x, y, ...z] = ['a'];
    console.log('x:' + x + ', y:' + y + ', z:' + z); 
}

{
    // 如果解构不成功，变量的值就等于undefined
    let [foo1] = [];
    let [bar1, foo2] = [1];
    console.log(foo1, foo2);
}

{
    // 不完全解构，即等号左边的模式，只匹配一部分的等号右边的数组。这种情况下，解构依然可以成功
    let [x, y] = [1, 2, 3, 4];
    console.log(x, y);

    let [a, [b], d] = [1, [2, 3], 4];
    console.log(a, b, d)
}

{
    // 如果等号的右边不是数组（或者严格地说，不是可遍历的结构），那么将会报错。

    // 报错
    // let [foo] = 1;
    // let [foo] = false;
    // let [foo] = NaN;
    // let [foo] = undefined;
    // let [foo] = null;
    // let [foo] = {};
}

{
    let [x, y, z] = new Set([1, 2, 3]);
    console.log(x, y, z);
}

{
    // 事实上，只要某种数据结构具有Iterator接口，都可以采用数组形式的解构赋值
    function* fibs() {
        var a = 0;
        var b = 1;
        while (true) {
            yield a;
            [a, b] = [b, a+b];
        }
    }

    var [x, y, z] = fibs();
    console.log(x, y, z);
}

{
    // 默认值
    let [foo = 'default'] = [];
    console.log('foo is ' + foo);

    let [x, y = 'b'] = ['a'];
    console.log('x:' + x + ',y:' + y);
}

{
    // 如果默认值是一个表达式，那么这个表达式是惰性求值的，即只有在用到的时候，才会求值
    let num = 1;
    function f() {
        console.log('function f() is running ' + num + ' time');
        return num;
    }

    let [x = f()] = [111]; // 没用到
    console.log('first time x:' + x);
    [x = f()] = []; // f()会运行
    console.log('second time x:' + x);
}

// 对象的解构赋值
{
    // 等号左边的两个变量的次序，与等号右边两个同名属性的次序不一致，但是对取值完全没有影响
    let {bar, foo, baz} = { foo: 'aaa', bar: 'bbb'}
    console.log(foo, bar, baz);
}

{
    // 如果变量名与属性名不一致，必须写成下面这样。

    let { foo: baz } = { foo: "aaa", bar: "bbb" };
    console.log(baz); // "aaa"

    let obj = { first: 'hello', last: 'world' };
    let { first: f, last: l } = obj;
    console.log(f, l); // 'hello' 'world'
}

{
    // 嵌套
    var obj = {
        p: [
            "Hello",
            { y: "World"}
        ],
        p1: {
            a: 1,
            b: 2
        }
    };
    let {p:[x, {y}], p1} = obj;
    console.log(x, y);
    console.log(p1);
}

{
    // 默认值 默认值生效的条件是，对象的属性值严格等于undefined
    let {x = 'default', y = 'default'} = {y:null};
    console.log(x, y);
}

{
    // 如果要将一个已经声明的变量用于解构赋值，必须非常小心。

    // 错误的写法
    var x;
    // {x} = {x: 1};
    // SyntaxError: syntax error
    // 上面代码的写法会报错，因为JavaScript引擎会将{x}理解成一个代码块，从而发生语法错误。只有不将大括号写在行首，避免JavaScript将其解释为代码块，才能解决这个问题。

    // 正确的写法
    ({x} = {x: 1});
    console.log(x);
}

{
    // 字符串的解构
    const [a, b, c] = 'hello';
    console.log(a, b, c);
}

{
    // 数值和布尔值的解构赋值
    // 解构赋值时，如果等号右边是数值和布尔值，则会先转为对象。

    let {toString: s} = 123;
    console.log(s === Number.prototype.toString); // true

    let {toString: s1} = true;
    console.log(s1 === Boolean.prototype.toString); // true
}

{
    // 函数参数的解构
    function add([x, y]) {
        return x + y;
    }
    console.log(add([1, 2, 3]));
}

{
    let a = [[1,2], [3, 4]].map(([a, b]) => a + b);
    console.log(a); // [3, 7]
}

{
    // 默认值
    function move({x=0, y=0} = {}) {
        return [x, y];
    }
    console.log(move({x: 3, y:8}));
    console.log(move({x: 3}));
    console.log(move({}));
    console.log(move());
}
{
    // 注意，下面的写法会得到不一样的结果。

    function move({x, y} = { x: 0, y: 0 }) {
      return [x, y];
    }

    console.log(move({x: 3, y:8}));
    console.log(move({x: 3}));
    console.log(move({}));
    console.log(move());
}

{
    // ndefined就会触发函数参数的默认值。

    console.log( [1, undefined, 3].map((x = 'yes') => x) );
}

// 用途
// 变量的解构赋值用途很多。

{
    // (1）交换变量的值
    let [x, y] = [1, 2];
    [x, y] = [y, x];
    // 上面代码交换变量x和y的值，这样的写法不仅简洁，而且易读，语义非常清晰。  
}

{
    //（2）从函数返回多个值

    // 函数只能返回一个值，如果要返回多个值，只能将它们放在数组或对象里返回。有了解构赋值，取出这些值就非常方便。

    // 返回一个数组
    function example1() {
      return [1, 2, 3];
    }
    var [a, b, c] = example1();

    // 返回一个对象
    function example2() {
      return {
        foo: 1,
        bar: 2
      };
    }
    var { foo, bar } = example2();
}

{
    // （3）函数参数的定义

    // 解构赋值可以方便地将一组参数与变量名对应起来。

    // 参数是一组有次序的值
    function f([x, y, z]) {  }
    f([1, 2, 3]);

    // 参数是一组无次序的值
    function f({x, y, z}) { }
    f({z: 3, y: 2, x: 1});
}

{
    // （4）提取JSON数据

    // 解构赋值对提取JSON对象中的数据，尤其有用。

    var jsonData = {
      id: 42,
      status: "OK",
      data: [867, 5309]
    }

    let { id, status, data: number } = jsonData;

    console.log(id, status, number)
    // 42, "OK", [867, 5309]
    // 上面代码可以快速提取JSON数据的值。
}

{
    // （5）函数参数的默认值
    function ajax(url, {
      async = true,
      beforeSend = function () {},
      cache = true,
      complete = function () {},
      crossDomain = false,
      global = true,
      // ... more config
    }) {
      // ... do stuff
    };
    // 指定参数的默认值，就避免了在函数体内部再写var foo = config.foo || 'default foo';这样的语句。  
}

{
    // （6）遍历Map结构

    // 任何部署了Iterator接口的对象，都可以用for...of循环遍历。Map结构原生支持Iterator接口，配合变量的解构赋值，获取键名和键值就非常方便。

    var map = new Map();
    map.set('first', 'hello');
    map.set('second', 'world');

    for (let [key, value] of map) {
      console.log(key + " is " + value);
    }
    // first is hello
    // second is world
    // 如果只想获取键名，或者只想获取键值，可以写成下面这样。

    // 获取键名
    for (let [key] of map) {
      // ...
    }

    // 获取键值
    for (let [,value] of map) {
      // ...
    } 
}

{
    // （7）输入模块的指定方法

    // 加载模块时，往往需要指定输入那些方法。解构赋值使得输入语句非常清晰。

    // const { SourceMapConsumer, SourceNode } = require("source-map");
}
