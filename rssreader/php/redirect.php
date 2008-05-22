<?php
//error_reporting(6143);
$hits = 0;
    if ($db = new SQLiteDatabase('/home/a3253051/db/hitcounter.db')) {
        $q = @$db->query("SELECT counter FROM rsshits WHERE url = '".$_GET['url']."'");
        if ($q === false) {
            $db->queryExec('CREATE TABLE rsshits (url TEXT, counter int)');
            $hits = 1;
        } else {
            $result = $q->fetchSingle();
            $hits = intval($result)+1;
	    $db->queryExec("INSERT INTO rsshits VALUES ('".$_GET['url']."',".$hits.")");
	    $db->queryExec("UPDATE rsshits SET counter=".$hits." WHERE url='".$_GET['url']."'");   
        }
    } else {
        die($err);
    }
?>
<?
header("Location: ".$_GET['url']);
//exit();
?>
