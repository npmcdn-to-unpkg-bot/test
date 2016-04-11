"use strict"

{
    // Array.from()
    let arrayLike = {
        'e': 'a',
        '1': 'b',
        '2': 'c',
        length: 3
    };

    // ES5
    console.log([].slice.call(arrayLike));
    // ES6
    console.log(Array.from(arrayLike));
}

{
    // 实际应用中，常见的类似数组的对象是DOM操作返回的NodeList集合，以及函数内部的arguments对象。Array.from都可以将它们转为真正的数组。

    // NodeList对象
    // let ps = document.querySelectorAll('p');
    // Array.from(ps).forEach(function (p) {
    //   console.log(p);
    // });

    // arguments对象
    function foo() {
      var args = Array.from(arguments);
      // ...
    }
}

{
    // Iterator
    console.log(Array.from('hello'));

    let namesSet = new Set(['a', 'b']);
    console.log(Array.from(namesSet));
}

{
    // 扩展运算符（...）也可以将某些数据结构转为数组。
    // 展运算符背后调用的是遍历器接口（Symbol.iterator），如果一个对象没有部署这个接口，就无法转换

    // arguments对象
    function foo() {
      var args = [...arguments];
    }

    // NodeList对象
    // [...document.querySelectorAll('div')]
}

{
    // Array.from方法则是还支持类似数组的对象。所谓类似数组的对象，本质特征只有一点，即必须有length属性。因此，任何有length属性的对象，都可以通过Array.from方法转为数组，而此时扩展运算符就无法转换
    console.log(Array.from({length:3}));
}

{
    // Array.from还可以接受第二个参数，作用类似于数组的map方法，用来对每个元素进行处理，将处理后的值放入返回的数组。

    let arrayLike = {
        '0': 1,
        '1': 2,
        '2': 3,
        length: 3
    };

    console.log(Array.from(arrayLike, x => x * x));
    // 等同于
    console.log(Array.from(arrayLike).map(x => x * x));

    console.log(Array.from([1, 2, 3], (x) => x * x));
    // [1, 4, 9]
}

{
    // 下面的例子将数组中布尔值为false的成员转为0。

    console.log(Array.from([1, , 2, , 3], (n) => n || 0));
    // [1, 0, 2, 0, 3]
}

// Array.of() 方法用于将一组值，转换为数组
// Array.of总是返回参数值组成的数组。如果没有参数，就返回一个空数组
{
    console.log(Array.of(3, 11, 8));
    console.log(Array.of(3));
    console.log(Array.of(3).length);
}

{
    // 这个方法的主要目的，是弥补数组构造函数Array()的不足。因为参数个数的不同，会导致Array()的行为有差异。

    Array() // []
    Array(3) // [, , ,]
    Array(3, 11, 8) // [3, 11, 8]
}

// copyWithin()
// Array.prototype.copyWithin(target, start=0, end = this.length)
// 在当前数组内部，将指定位置的成员复制到其他位置（会覆盖原有成员），然后返回当前数组。
// 也就是说，使用这个方法，会修改当前数组。
{
    let a = [1, 2, 3, 4, 5];
    a.copyWithin(0, 1);
    console.log(a);
}

{
    // 将3号位复制到0号位
    console.log([1, 2, 3, 4, 5].copyWithin(0, 3, 4));
    // [4, 2, 3, 4, 5]

    // -2相当于3号位，-1相当于4号位
    console.log([1, 2, 3, 4, 5].copyWithin(0, -2, -1));
    // [4, 2, 3, 4, 5]

    // 将3号位复制到0号位
    console.log([].copyWithin.call({length: 5, 3: 1}, 0, 3));
    // {0: 1, 3: 1, length: 5}

    // 将2号位到数组结束，复制到0号位
    var i32a = new Int32Array([1, 2, 3, 4, 5]);
    console.log(i32a.copyWithin(0, 2));
    // Int32Array [3, 4, 5, 4, 5]

    // 对于没有部署TypedArray的copyWithin方法的平台
    // 需要采用下面的写法
    console.log([].copyWithin.call(new Int32Array([1, 2, 3, 4, 5]), 0, 3, 4));
    // Int32Array [4, 2, 3, 4, 5]
}

// 数组实例的find()和findIndex()
{
    console.log([1, 4, -5, 10].find((n) => n < 0));
    console.log([1, 4, -5, 10].find(function(value, index, arr) {
        return value < 0;
    }));

    console.log([1, 4, -5, 10].findIndex((n) => n < 0));
    console.log([1, 4, -5, 10].findIndex(function(value, index, arr) {
        return value < 0;
    }));
}

// 数组实例的fill() 
{
    console.log(['a', 'a', 'a'].fill(7));
    console.log(new Array(3).fill(8));

    // fill方法还可以接受第二个和第三个参数，用于指定填充的起始位置和结束位置
    console.log(['a', 'a', 'a'].fill(7, 1, 3));
}

// 数组实例的entries()，keys()和values()
// 它们都返回一个遍历器对象，可以用for...of循环进行遍历，唯一的区别是keys()是对键名的遍历、values()是对键值的遍历，entries()是对键值对的遍历。
{
    for (let index of ['a', 'b'].keys()) {
        console.log(index);
    }

    // node not supported yet
    for (let value of ['a', 'b'].values()) {
        console.log(value);
    }

    for (let [index, value] of ['a', 'b'].entries()) {
        console.log(index, value);
    } 
}

{
    // includes 该方法属于ES7，但Babel转码器已经支持
    console.log([1, 2, 3].includes(2));
    console.log([1, 2, 3].includes(22));
}