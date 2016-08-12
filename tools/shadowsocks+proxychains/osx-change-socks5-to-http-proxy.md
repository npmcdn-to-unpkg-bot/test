    # use polipo on OSX
    $ brew install polipo
    $ polipo socksParentProxy=localhost:1080

    # polipo 端口是 8123
    # 现在可以用 127.0.0.1:8123 作为http(s)的代理了

    # 或者brew services start polipo
    # 不过要修改配置文件
    # /usr/local/opt/polipo/homebrew.mxcl.polipo.plist
    # <string>socksParentProxy=localhost:1080</string> 这是增加的内容

        <?xml version="1.0" encoding="UTF-8"?>
        <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
        <plist version="1.0">
          <dict>
            <key>Label</key>
            <string>homebrew.mxcl.polipo</string>
            <key>RunAtLoad</key>
            <true/>
            <key>KeepAlive</key>
            <true/>
            <key>ProgramArguments</key>
            <array>
              <string>/usr/local/opt/polipo/bin/polipo</string>
              <string>socksParentProxy=localhost:1080</string>
            </array>
            <!-- Set `ulimit -n 65536`. The default OS X limit is 256, that's
                 not enough for Polipo (displays 'too many files open' errors).
                 It seems like you have no reason to lower this limit
                 (and unlikely will want to raise it). -->
            <key>SoftResourceLimits</key>
            <dict>
              <key>NumberOfFiles</key>
              <integer>65536</integer>
            </dict>
          </dict>
        </plist>