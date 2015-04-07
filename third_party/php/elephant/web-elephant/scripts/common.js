function isBlank(objid, border)
{
	console.log($("#"+objid).val().replace(/^\s*$/g, "") + "dafei");
	
	if($("#"+objid).val().replace(/^\s*$/g, '') == "") {
		if (border != "") {
			$("#"+objid).css("border", "solid 1px "+border);
		}
		return true;
	}
	return false;
}
