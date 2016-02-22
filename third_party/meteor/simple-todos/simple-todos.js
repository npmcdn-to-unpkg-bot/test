Tasks = new Mongo.Collection("tasks");
if (Meteor.isServer) {
  // This code only runs on the server
  // Only publish tasks that are public or belong to the current user
  Meteor.publish("tasks", function() {
    return Tasks.find({
      $or: [
        {private: {$ne: true}},
        {owner: this.userId}
      ]
    });
  });
}

if (Meteor.isClient) {
  // this code only runs the client
  Meteor.subscribe("tasks");

  Template.body.helpers({
    tasks : function() {
      if (Session.get("hideCompleted")) {
        return Tasks.find({checked: {$ne: true}}, {sort: {createdAt: -1}});
      }
      return Tasks.find({}, {sort: {createdAt: -1}});
    },
    hideCompleted : function() {
      return Session.get("hideCompleted");
    },
    incompleteCount : function() {
      return Tasks.find({checked: {$ne:true}}).count();
    }
  });

  Template.body.events({
    "submit .new-task": function(event) {
      console.log(event);
      event.preventDefault();

      var text = event.target.text.value;

      // Insert a task
      Meteor.call("addTask", text);

      event.target.text.value = "";
    },
    "change .hide-completed input" : function(event) {
      Session.set("hideCompleted", event.target.checked);
    }
  });

  Template.task.helpers({
    isOwner: function() {
      return this.owner == Meteor.userId();
    }
  });
  Template.task.events({
    "click .toggle-checked" : function(event) {
      Meteor.call("setChecked", this._id, !this.checked);
    },
    "click .delete" : function() {
      Meteor.call("deleteTask", this._id);
    },
    "click .toggle-private" : function() {
      Meteor.call("setPrivate", this._id, !this.private);
    }
  });
  Accounts.ui.config({
    passwordSignupFields: "USERNAME_ONLY"
  });
}

Meteor.methods({
  addTask: function(text) {
    // make sure the user is logged in before inserting a task
    if (!Meteor.userId()) {
      throw new Meteor.Error("not-authorized");
    }
    Tasks.insert({
        text: text,
        createdAt: new Date(),
        owner: Meteor.userId(), // _id of logged in user
        username: Meteor.user().username
    });
  },
  deleteTask: function(taskId) {
    var task = Tasks.findOne(taskId);
    if (task.private && task.owner !== Meteor.userId()) {
      throw new Meteor.Error("not-authorized");
    }
    Tasks.remove(taskId);
  },
  setChecked: function(taskId, setChecked) {
    var task = Tasks.findOne(taskId);
    if (task.private && task.owner !== Meteor.userId()) {
      throw new Meteor.Error("not-authorized");
    }
    Tasks.update(taskId, {$set: {checked: setChecked}});
  },
  setPrivate: function(taskId, setToPrivate) {
    var task = Tasks.findOne(taskId);
    if (task.owner !== Meteor.userId()) {
      throw new Meteor.Error("not-authorized");
    }
    Tasks.update(taskId, {$set:{private: setToPrivate}});
  }
});

if (Meteor.isServer) {
  Meteor.startup(function () {
    // code to run on server at startup
  });
}