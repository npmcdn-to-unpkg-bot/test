# login as root
# add new user
	$ adduser user_name
	# will create home, group and
	# will ask you to enter password.

# sudoer
	$ vi /etc/sudoers
	在root ALL=(ALL)ALL行下添加XXX ALL=(ALL)ALL，XXX为你的用户名
	:wq!

# disable root account login

