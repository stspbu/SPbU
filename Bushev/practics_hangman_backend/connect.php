<?php
header('Content-Type: text/html; charset=cp1251');
if($_POST['hash'] != "HCXt7xC47HGvVwo_68XX25Tgs789XBZ4fhsP0") exit("#������, ������ ��������");

include_once("mysql/sql_connect.php");

$gid = (int)$_POST['gid'];
$player = mysqli_real_escape_string($db, $_POST['player']);
if(!isset($player) || empty($player)) exit("#������, ������ ������������ ������������� ����");

$data = mysqli_query($db, "SELECT gid, host, player FROM hangman_games WHERE gid='$gid'") or exit("#�� ������� ������������ � �������, ���������� �����");
$fdata = mysqli_fetch_assoc($data);

if(!isset($fdata['gid'])) exit("#��������� ���� �� ����������");
else if(!empty($fdata['player']) || !empty($fdata['active'])) exit("#������ ���� ��� ��������");

mysqli_query($db, "UPDATE hangman_games SET player='$player', active=1 WHERE gid='$gid'") or exit("#�� ������� ������������ � �������, ���������� �����");
exit($fdata['host']);
?>