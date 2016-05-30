'use strict';

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
    comments: [ {
        month: {type: String},
        comments: [Comment]
    }]
});

var BlogPostModel = mongoose.model('BlogPost', BlogPost)


function insertCommnets(title, month, comments) {


        BlogPostModel.findOne({title: title}, function(err, post) {
            if (err) {
                console.log(err)
            } else {
                if (!post) {
                    console.log('no post')
                    post = new BlogPostModel({
                        title: 'War is coming',
                        comments: [
                            {month: month, comments}
                        ]
                    })
                    post.save(function(err) {
                        if (err) {
                            console.log(err)
                        } else {
                            console.log('save ok')
                        }
                    })
                } else {
                    var index = -1;
                    for (let i = 0; i < post.comments.length; i++) {
                        if (post.comments[i].month === month) {
                            index = i;
                            break;
                        }
                    }
                    if (index === -1) {
                        console.log('No month: ' + month);
                        post.comments.push({month:month, comments})
                    }else {
                        console.log('has month: ' + month)
                        for (let i of comments) {
                            post.comments[index].comments.push(i)
                        }
                    }
                    post.save(function(err) {
                        if (err) {
                            console.log(err)
                        } else {
                            console.log(`month:${month} save ok`)
                        }
                    })      
                }
            }
        })
}

insertCommnets('War is coming', '201601', [{name: 'Lily', age: 22}, {name: 'Lucy', age: 23}])
setTimeout(insertCommnets, 1000, 'War is coming', '201601', [{name: 'Bob', age: 22}, {name: 'John', age: 23}])
setTimeout(insertCommnets, 2000, 'War is coming', '201602', [{name: 'Bob', age: 22}, {name: 'John', age: 23}])

