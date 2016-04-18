
var testStr = "now test001 test002";   
var re = /test(\d+)/ig;    
var r = "";   
while(r = re.exec(testStr)) {
    console.log(r)
    console.log(r[0] + "  " + r[1]);   
}  