# login as root
# add new user
	$ adduser user_name
	# will create home, group and
	# will ask you to enter password.

# sudoer
	$ vi /etc/sudoers
	在root ALL=(ALL)ALL行下添加XXX ALL=(ALL)ALL，XXX为你的用户名
	:wq!


# ssh disable密码登录和root登录
    $ vi /etc/ssh/sshd_config
    PermitRootLogin no
    PasswordAuthentication no

    重启
    $ /etc/init.d/ssh restart