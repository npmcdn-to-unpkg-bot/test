var Sequelize = require('sequelize');

var sequelize = new Sequelize(
	process.env['DATABASE_NAME'],
	process.env['DATABASE_USERNAME'],
	process.env['DATABASE_PASSWORD'],
	{
		host: 'localhost',
		port : '3306',
		dialect : 'mysql',
		pool : {
			max : 5,
			min : 0,
			idle : 10000
		}
	}
);

// connection
sequelize
	.authenticate()
	.then(function(err) {
		console.log('>> Connection has been established successfully');
	}, function(err) {
		console.log('>> Unable to connect to the database:', err);
	});

// defining a model
// Models are defined with
// sequelize.define('name', {attributes}, {options}).
// http://docs.sequelizejs.com/en/latest/docs/models-definition/#data-types

var User = sequelize.define('User', {
	firstName : {
		type : Sequelize.STRING, // varchar(255)
		field : 'first_name' // // Will result in an attribute that is firstName when user facing but first_name in the database
	},
	lastName : {
		type : Sequelize.STRING(96) // varchar(96)
	},
	password : Sequelize.STRING,
	goal : Sequelize.INTEGER
}, {
	// freezeTableName : true // Model tableName will be the same as the model name
	tableName : 'my_user_table',
	// timestamps : false, //  this will deactivate the timestamp columns
	updatedAt : 'last_update',
	createdAt : 'date_of_creation'
});

// Create this table
// User.sync({force: true}).then(function () {
//   	console.log('>> Table created...');
//   	insert();
// }, function (err) {
// 	console.log('>> An error occurred while creating the table:', err);
// });

var insert = function () {
	// Creating and persisting instances
	// two step way
	var user = User.build({
		lastName : 'Rock',
		firstName : 'John',
		password : 'aaaaaa',
		goal : 10
	});
	user.save().then(function() {
		console.log('>> save instance successfully');
		select();
	}, function(err) {
		console.log('>> failed to save instance:', err);
	});

	// one step way
	User.create({
		lastName: 'One',
		firstName : 'Step',
		password : 'one step',
		goal : 10
	}).then(function(user) {
		console.log('>> save instance one step successfully');
		// select
		// select();
	}, function(err) {
		console.log('>> save instance one step failed:', err);
	});
};

var select = function () {
	User.find( {where : { lastName : 'Rock'}})
		.then(function(rock) {
			if (!rock) {
				console.log('>> No user with lastName Rock found');
			} else {
				console.log('>> Hello ' + rock.lastName);
				// console.log('All attributes of rock:', rock.get());
			}
		});
};


// associations
// 1:1
// in mysql, use 'desc Source1to1' to see the table.
var Source1to1 = sequelize.define('Source1to1', {})
  , Target1to1 = sequelize.define('Target1to1', {});
Source1to1.hasOne(Target1to1);
Target1to1.belongsTo(Source1to1);
// Even if we didn't define any foreign key or something else,
// instances of Target will have a column SourceId!


// 1:N
var Source1toN = sequelize.define('Source1toN', {})
  , Target1toN = sequelize.define('Target1toN', {});
Source1toN.hasMany(Source1toN);
Target1toN.belongsTo(Target1toN);
// Even if we didn't define any foreign key or something else,
// instances of Target will have a column SourceId!

// N:N
var SourceNtoN = sequelize.define('SourceNtoN', {})
  , TargetNtoN = sequelize.define('TargetNtoN', {});
SourceNtoN.hasMany(SourceNtoN);
TargetNtoN.hasMany(TargetNtoN);
// Even if we didn't define any foreign key or something else,
// Sequelize will create a table SourcesTargets.

// create all tables
sequelize
	.sync({force: true})
	.then(function() {
		console.log('>> tables created...');
		insert();
	});
