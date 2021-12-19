<?php
include('dbconnection.php');
//$dateadd = strtotime("+5 Hours +30 Minutes");
//$date = date("YmdHis", $dateadd);
//$dates = date("Y/m/d H:i:s", $dateadd);
$temp = $_POST['sendval1'];
$humidity = $_POST['sendval2'];
$pressure= $_POST['sendval3'];
$light= $_POST['sendval4'];
$date = $_POST['sendval5'];
$query = mysqli_query($con, "INSERT INTO data(temp,humidity,pressure,light,date,status) VALUES ('$temp','$humidity','$pressure','$light','$date','1')");
if ($query){
    echo "success";
}
?>