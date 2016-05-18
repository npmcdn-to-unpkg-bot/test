# ubuntu install
    $ sudo apt-get install mongodb

    $ sudo service mongodb start/stop


# manually install

    https://docs.mongodb.org/manual/tutorial/install-mongodb-on-linux/

    $ curl -O https://fastdl.mongodb.org/linux/mongodb-linux-x86_64-3.2.5.tgz
    $ tar -zxvf mongodb-linux-x86_64-3.2.5.tgz
    $ sudo mv mongodb-linux-x86_64-3.2.5/ /usr/local/mongodb

    // You can add path into PATH or create links.
    // export PATH=<mongodb-install-directory>/bin:$PATH
    $ find /usr/local/mongodb/bin/* | sudo xargs -i  ln -sf {} /usr/local/bin/

# Run mongodb

    // mongodb default data directry.
    $ mkdir -p /data/db


# OSX install
    $ brew udpate
    $ brew install mongodb

# Run mongodb
    # 指定自己的数据的存储目录.
    $ mkdir -p /tmp/data/mongodb
    $ mongodb -dbpath /tmp/data/mongodb

# Usage
    $ mongo
    > db.help
    > use mydb
    switched to db mydb
    # insert
    > var data = {
        title: 'hello',
        content: 'this is a test'};

# insert
    > db.blog.insert(data)

# query
    > db.blog.find()
    > db.blog.findOne()
    > db.blog.find({title: 'hello'})

# update
    > data.post = 'this is a post';
    > db.blog.update({title: 'hello'}, data)

# remove
    > db.blog.remove({title: 'hello'})
    > db.blog.remove() // remove all

# upsert, insert和update的合体,没有就创建,有就更新
    > 

## $inc 原子增加,没有会创建
    > db.blog.update({title:'hello' }, {$inc: {pages: 8}})
    > db.blog.update({title:'hello' }, {$inc: {pages: -2}})

## $set 没有就创建,有了会更改数据
    > db.blog.update({title: 'hello'}, {$set: {url: 'a fake url'}})  
    > db.blog.update({title: 'hello'}, {$set: {url: ['url-01', 'url-02']}})
    > var author = {
            name: 'Kii',
            email: 'kii@kii.com',
            }
    > db.blog.update({title: 'hello'}, {$set: {author: author})
    > db.blog.update({'author.name': 'Kii'}, {$set: {'author.email': 'kii@gmail.com'}})

## $unset 删除
    > db.blog.update({title: 'hello'}, {$unset: {url: 1}})

## $push 数组修改器,没有自动创建数组,默认插入队尾
    > db.blog.update({title: 'hello'}, {$push: {comments: 'comment one'}})

## $addToSet,跟push一样,但是不会插入重复数据,默认插入队尾
    > db.blog.update({title: 'hello'}, {$addToSet: { 'visitors': 'xiaoming'}})
    > db.blog.update({title: 'hello'}, {$addToSet: { 'visitors': 'Bob'}})
    > db.blog.update({title: 'hello'}, {$addToSet: { 'visitors': 'xiaoming'}})
    // 搭配each添加多,但是不会重复数据
    > db.blog.update({title: 'hello'}, {$addToSet: { 'visitors': {$each: ['xiaoming', 'Bob', 'Jhon', 'Rock']}}})

## $pop 删除
    > db.blog.update({title: 'hello'}, {$pop: {'visitors': 1}}) // 从尾部删除
    > db.blog.update({title: 'hello'}, {$pop: {'visitors': -1}}) // 从头删除

## $pull 根据条件来删除
    > db.blog.update({title: 'hello'}, {$pull: {visitors: 'Bob'}})

## $ 数组定位修改器
    > db.mylist.insert({id: 1, 'comments': [{author: 'Bob', vote: 3}, {author: 'Lily', vote: 3},{author: 'Lucy', vote: -1}]})
    > db.mylist.update({id: 1}, {$inc: {'comments.1.vote': 10}}) // 1是下标
    > db.mylist.update({'comments.author': 'Bob'}, {$inc: {'comments.$.vote': 10}}) // $代替前面查询到的下标
