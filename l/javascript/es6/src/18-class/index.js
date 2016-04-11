"use strict"


class Point {
    constructor(x = 0, y = 0) {
        this.x = x;
        this.y = y;
    }

    toString() {
        return '(' + this.x + ',' + this.y + ')';
    }
}

console.log('typeof Point:' + typeof Point);
console.log('Point === Point.prototype.constructor: ' + (Point === Point.prototype.constructor));

let point = new Point(1);
console.log(point);

// 与ES5一样，实例的属性除非显式定义在其本身（即定义在this对象上），否则都是定义在原型上（即定义在class上）
console.log(point.hasOwnProperty('x')); // true
console.log(point.hasOwnProperty('y')); // true
console.log(point.hasOwnProperty('toString')); // false
console.log(point.__proto__.hasOwnProperty('toString')); // true

// 与ES5一样，类的所有实例共享一个原型对象
let point2 = new Point(2);
console.log(point2.__proto__ === point.__proto__); // true

// name属性
// 由于本质上，ES6的Class只是ES5的构造函数的一层包装，所以函数的许多特性都被Class继承，包括name属性。

console.log(Point.name);



// constructor方法是类的默认方法，通过new命令生成对象实例时，自动调用该方法。
// 一个类必须有constructor方法，如果没有显式定义，一个空的constructor方法会被默认添加

{
    const MyClass = class Me {
        getClassName() {
            return Me.name;
        }
    };

    let c = new MyClass();
    console.log(c.getClassName()); // Me
    // Me只在Class内部有定义
    // Me.name; // error
}

{
    const MyClass = class {
    };
}

{
    let person = new class {
        constructor(name) {
            this.name = name;
        }

        sayName() {
            return this.name;
        }
    }("张三");

    console.log(person.sayName()); // "张三"
}


// Class的继承
// Class之间可以通过extends关键字实现继承

class ColorPoint extends Point {

  constructor(x, y, color) {
    super(x, y); // 调用父类的constructor(x, y)
    this.color = color;
  }

  toString() {
    return this.color + ' ' + super.toString(); // 调用父类的toString()
  }

}

let point3 = new ColorPoint(1, 2, 'red');
console.log(point3.toString());

// Object.getPrototypeOf()
// Object.getPrototypeOf方法可以用来从子类上获取父类。

console.log(Object.getPrototypeOf(ColorPoint) === Point); // true
// 因此，可以使用这个方法判断，一个类是否继承了另一个类

{
    // getter, setter
    class MyClass {
        get prop() {
            return 'this is getter';
        }

        set prop(value) {
            console.log('setter:' + value);
        }
    }

    const a = new MyClass();
    a.prop = 123;
    console.log(a.prop);
}

// Generator
{
    class Foo {
        constructor(...args) {
            this.args = args;
        }

        * [Symbol.iterator]() {
            for (let arg of this.args) {
                yield arg;
            }
        }
    }

    for (let x of new Foo('Hello', 'world')) {
        console.log(x);
    }
}

// Class的静态方法
// 加上static关键字，就表示该方法不会被实例继承，而是直接通过类来调用
{
    class Foo {
        static classMethod() {
            console.log('Hello classMethod');
        }
    }

    class Bar extends Foo {

    }

    Foo.classMethod();
    Bar.classMethod();
}

// Class的静态属性和实例属性
{
   // 静态属性指的是Class本身的属性，即Class.propname，而不是定义在实例对象（this）上的属性。

    class Foo {
    }

    Foo.prop = 1;
    Foo.prop // 1
    // 上面的写法为Foo类定义了一个静态属性prop。
    // 目前，只有这种写法可行，因为ES6明确规定，Class内部只有静态方法，没有静态属性。 
}

{
    // Mix
    class Loggable {

    }
    class Serializable {

    }

    class DistributedEdit extends mix(Loggable, Serializable) {
      // ...
    }
}