page is a server serving a webpage which will change dom.

    $ cd page
    $ npm install
    $ node index.js


in another teminal
    to see if the injected js willlisten to events for dom changes.
    $ phantom monitor.js
    or
    $ phantom monitor-with-juqery-watch.js  # this works.


Monitor CSS change:
    使用 MutationObserver 兼容性好一点
    https://developer.mozilla.org/en-US/docs/Web/API/MutationObserver#Example_usage

    使用DOMAttrModified 貌似不是很好用，不过其他的还行
    DOMSubtreeModified, DOMNodeInserted等等


