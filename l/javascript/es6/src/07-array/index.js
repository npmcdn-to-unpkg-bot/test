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