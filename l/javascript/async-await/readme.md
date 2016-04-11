# async/await usage
    right now, we still need babel to use aysnc/await
    $ npm install babel-cli --save
    $ npm install babel-preset-es2015 --save
    $ npm install babel-preset-stage-3 --save   // async/await is ES7


    {
        "presets": [
            "stage-3",
            "es2015",
        ],
        "plugins": []
    }
