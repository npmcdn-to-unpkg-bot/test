Template.postSubmit.events({
  'submit form': function(e) {
    e.preventDefault();

    var post = {
      // 这个函数使用 jQuery 去获取我们表单字段的值
      url: $(e.target).find('[name=url]').val(),
      title: $(e.target).find('[name=title]').val()
    };

    var errors = validatePost(post);
    if (errors.title || errors.url)
      return Session.set('postSubmitErrors', errors);

    Meteor.call('postInsert', post, function(error, result) {
      if (error) {
        return throwError(error.reason);
      }

      if (result.postExists) {
        return throwError('This link has already been posted');
      }
    });
    Router.go('postsList');
  }
});

Template.postSubmit.onCreated(function() {
  Session.set('postSubmitErrors', {});
});

Template.postSubmit.helpers({
  errorMessage: function(field) {
    return Session.get('postSubmitErrors')[field];
  },
  errorClass: function(field) {
    return !!Session.get('postSubmitErrors')[field] ? 'has-error' : '';
  }
});