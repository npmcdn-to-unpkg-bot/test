Posts = new Mongo.Collection('posts');
// 要 Var 还是不要 Var?
// 在 Meteor 中, 关键字 var 限制对象的作用域在文件范围内.
// 我们想要 Posts 作用于整个应用范围内，因此我们在这里不要 Var 这个关键字

Posts.allow({
  update: function(userId, post) { return ownsDocument(userId, post); },
  remove: function(userId, post) { return ownsDocument(userId, post); }
});

Posts.deny({
  update: function(userId, post, fieldNames) {
    // 只能更改如下两个字段
    return (_.without(fieldNames, 'url', 'title').length > 0);
  }
});

Meteor.methods({
  postInsert: function(postAttributes) {
    check(Meteor.userId(), String);
    check(postAttributes, {
      title: String,
      url: String
    });

    if (Meteor.isServer) {
      postAttributes.title += "(server)";
      // wait for 5 seconds
      // Meteor._sleepForMs(5000);
    } else {
      postAttributes.title += "(client)";
    }

    var postWithSameLink = Posts.findOne({url: postAttributes.url});
    if (postWithSameLink) {
      return {
        postExists: true,
        _id: postWithSameLink._id
      }
    }

    var user = Meteor.user();
    // _.extend() 方法来自于 Underscore 库，作用是将一个对象的属性传递给另一个对象
    var post = _.extend(postAttributes, {
      userId: user._id,
      author: user.username,
      submitted: new Date()
    });;
    var postId = Posts.insert(post);
    return {
      _id: postId
    }
  }
});