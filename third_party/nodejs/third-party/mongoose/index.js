var mongoose = require('mongoose');

mongoose.connect('mongodb://localhost/my_database');

var Schema = mongoose.Schema,
    ObjectId = Schema.ObjectId;


var Comment = new Schema({
  name: { type: String, default: 'hahaha' },
  age: { type: Number, min: 18, index: true },
  bio: { type: String, match: /[a-z]/ },
  date: { type: Date, default: Date.now },
});

var BlogPost = new Schema({
    title     : { type: String, default: 'War is coming' },
    date      : { type: Date, default: Date.now },
    comments: [Comment]
});

var BlogPostModel = mongoose.model('BlogPost', BlogPost)

var post = new BlogPostModel()
post.title = 'a test one';
post.comments.push({name: 'bob', age: 20})
post.save(function(err) {
    if (err) {
        console.log(err)
    } else {
        console.log('save ok')
    }
})