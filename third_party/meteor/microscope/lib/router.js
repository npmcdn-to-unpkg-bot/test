Router.configure({
  layoutTemplate: 'layout',
  loadingTemplate: 'loading',
  notFoundTemplate: 'notFound',
  waitOn: function() {
    return Meteor.subscribe('posts');
  }
});

Router.route('/', {name: 'postsList'});
Router.route('/posts/:_id', {
  name: 'postPage',
  data: function() { return Posts.findOne(this.params._id); }
});
Router.route('/submit', {name: 'postSubmit'});

// 如果有人输入了像 http://localhost:3000/posts/xyz 这种格式的 URL,
// xyz 不是一个合法的帖子 _id 怎么办？虽然是合法的路由，但是没有指向任何数据。
// 幸好，如果我们在 route.js 结尾添加了特别的 dataNotFound hook
// Iron Rounter 就能足够智能地解决这个问题。
// 这会告诉 Iron Router 不仅在非法路由情况下，而且在 postPage 路由，
// 每当 data 函数返回“falsy”（比如 null、false、undefined 或 空）对象时，显示“无法找到”的页面。
//      ^^^  
Router.onBeforeAction('dataNotFound', {only: 'postPage'});