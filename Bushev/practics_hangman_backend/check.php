<?php
header('Content-Type: text/html; charset=cp1251');
if($_POST['hash'] != "HCXt7xC47HGvVwo_68XX25Tgs789XBZ4fhsP0") exit("#ќшибка, доступ запрещен");

include_once("mysql/sql_connect.php");

$gid = (int)$_POST['gid'];
$data = mysqli_query($db, "SELECT player FROM hangman_games WHERE gid='$gid'") or exit();
$fdata = mysqli_fetch_assoc($data);

if(isset($fdata['player']) && !empty($fdata['player'])) exit($fdata['player']);
?>