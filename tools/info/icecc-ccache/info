# http://blog.csdn.net/jcracker/article/details/11368597
# http://pointclouds.org/documentation/advanced/distcc.php
 


# install icecc ununtu
$ sudo apt-get install icecc
$ sudo apt-get install icecc-monitor
$ sudo service iceccd start
$ sudo service icecc-scheduler start


# icecc on osx
$ brew install icecream
	To override the toolset with icecc, add to your path:
	  /usr/local/opt/icecream/libexec/bin/icecc

	To have launchd start the icecc daemo at login:
	  cp /usr/local/opt/icecream/org.opensuse.icecc.plist ~/Library/LaunchAgents/
	  launchctl load -w ~/Library/LaunchAgents/org.opensuse.icecc.plist

	To have launchd start icecream at login:
	  ln -sfv /usr/local/opt/icecream/*.plist ~/Library/LaunchAgents
	Then to load icecream now:
	  launchctl load ~/Library/LaunchAgents/org.opensuse.icecc-scheduler.plist

$ OSX
$ export PATH=/usr/local/opt/icecream/libexec/bin/:$PATH
# Ubuntu
$ export PATH=/usr/lib/icecc/bin:$PATH

# DEBUG info
export ICECC_DEBUG=debug

# ccache for clang
export USE_CCACHE=1
export CCACHE_CPP2=yes
export CCACHE_SLOPPINESS=time_macros
export CC="ccache clang"
export CXX="ccache clang++"

