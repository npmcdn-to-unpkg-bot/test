
function isBlank(objid,border) //判断是否为空
{
    if($("#"+objid).val().replace(/^\s*$/g,'')=="")
    {
       
        if(border!="")
        {
            $("#"+objid).css("border","solid 1px "+border);
        }
        return true;
    }
    return false;
}