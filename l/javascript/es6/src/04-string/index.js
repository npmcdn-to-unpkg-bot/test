"use strict"

// node 5.9.1 已经默认支持了

{
    // includes(), startsWith(), endsWith()
    // 传统上，JavaScript只有indexOf方法，可以用来确定一个字符串是否包含在另一个字符串中。ES6又提供了三种新方法

    var s = 'Hello world!';
    console.log( s.startsWith('Hello') );
    console.log( s.endsWith('!') );
    console.log( s.includes('lo'));

    // 这三个方法都支持第二个参数，表示开始搜索的位置。
    console.log( s.startsWith('Hello', 6))
}

{
    // repeat()
    console.log( 'x'.repeat(3) );
    console.log( 'Hello'.repeat(2.99) );
    console.log( 'na'.repeat(0) );
}

{
    // 模板字符串
    console.log(`In Javascript '\n' is a lined-feed.`);

    // 如果使用模板字符串表示多行字符串，所有的空格和缩进都会被保留在输出之中
    console.log(`In Javascript this is
    not legal.`);

    let name = "Bob", time = "today";
    // 模板字符串中嵌入变量，需要将变量名写在${}之中。
    console.log(`Hello ${name}, how are you ${time}?`)

    // 调用函数
    function fn(argument) {
        return "Hello world";
    }
    console.log(`foo ${fn()} bar`);


    // 由于模板字符串的大括号内部，就是执行JavaScript代码，因此如果大括号内部是一个字符串，将会原样输出。
    console.log(`Hello ${'World'}`); // "Hello World"
}

{
    let a = 5;
    let b = 10;

    function tag(s, v1, v2) {
        console.log(s[0]);
        console.log(s[1]);
        console.log(s[2]);
        console.log(v1);
        console.log(v2);

        return "OK";
    }

    tag`Hello ${a+b} world ${a*b}`;
    // 'Hello '
    // ' world'
    // ' ''
    // 15
    // 50
}
