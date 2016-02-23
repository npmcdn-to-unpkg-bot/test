Template.postSubmit.events({
  'submit form': function(e) {
    e.preventDefault();

    var post = {
      // 这个函数使用 jQuery 去获取我们表单字段的值
      url: $(e.target).find('[name=url]').val(),
      title: $(e.target).find('[name=title]').val()
    };
    Meteor.call('postInsert', post, function(error, result) {
      if (error) {
        return alert(error.reason);
      }

      if (result.postExists) {
        alert('This link has already been posted');
      }
    });
    Router.go('postsList');
  }
});