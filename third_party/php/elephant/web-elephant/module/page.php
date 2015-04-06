<?php
    function get_friendLinks()
    {
    	global $myDB;
        return $myDB->execForArray("select * from friendlinks");
    }

?>