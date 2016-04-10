
# 介绍es6的书
	http://es6.ruanyifeng.com/#README

# 想用es6，那么现在原生支持的并不是很好啊，所以需要一些转换, 例如babel, typescript 之类的
	$ npm install --save-dev babel-cli
	$ npm install --save-dev babel-preset-es2015

	#需要这个配置文件才能用,子目录会地柜往上找，类似 .git
	.babelrc
	{
	    "presets": [
	      "es2015"
	    ],
	    "plugins": []
	}

	$ ./node_modules/.bin/babel-node es6.js
	$ ./node_modules/.bin/babel es6.js -o es5.js

	# build with npm, see package.json
		$ npm run build

# node es6进度
	https://nodejs.org/en/docs/es6/

# nvm node版本管理
	https://github.com/creationix/nvm