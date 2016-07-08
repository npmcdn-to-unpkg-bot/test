    # use polipo on OSX
    $ brew install polipo
    $ polipo socksParentProxy=localhost:1080

    # polipo 端口是 8123
    # 现在可以用 127.0.0.1:8123 作为http(s)的代理了
