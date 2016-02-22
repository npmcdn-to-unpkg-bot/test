Template.layout.helpers({
  pageTitle: function() {
    if (!Session.get('pageTitle')) {
      Session.set('pageTitle', 'Microscope');
    }
    return Session.get('pageTitle');
  }
});