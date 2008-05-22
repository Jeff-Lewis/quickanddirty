<?php
function hitcounter($url) {

//error_reporting(6143);
$hits = 0;
    if ($db = new SQLiteDatabase('/home/a3253051/db/hitcounter.db')) {
        $q = @$db->query("SELECT counter FROM rsshits WHERE url = '".$url."'");
        if ($q === false) {
            $db->queryExec('CREATE TABLE rsshits (url TEXT, counter int)');
            //$hits = 1;
        } else {
            $result = $q->fetchSingle();
            $hits = intval($result);
	    //$db->queryExec("INSERT INTO rsshits VALUES ('".$_GET['url']."',".$hits.")");
	    //$db->queryExec("UPDATE rsshits SET counter=".$hits." WHERE url='".$_GET['url']."'");   
        }
    } else {
        die($err);
    }
	return $hits;
}
?>
