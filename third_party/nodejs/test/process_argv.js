
console.log(process.argv);

process.argv.forEach(function(val, index, array) {
	console.log(val + ':' + index );
});
