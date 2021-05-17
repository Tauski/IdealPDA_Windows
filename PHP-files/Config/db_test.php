<?php

error_reporting(E_ALL);
ini_set('display_errors', 1);

$host = "localhost";
$username = "root";
$password = "";
$dbname = "firstdb";
$port = 3306;


//$mysqli = new mysqli($host,$username,$password,$dbname,$port);
$con=mysqli_connect($host,$username,$password,$dbname,$port);
// Check connection
if ($con -> connect_errno) {
  echo "Failed to connect to MySQL: " . $mysqli -> connect_error;
  exit();
}

$sql="SELECT name,city FROM users ORDER BY name";

if($result=mysqli_query($con,$sql))
{
    //seek to row 15
    mysqli_data_seek($result,2);
    //fetch row
    $row=mysqli_fetch_row($result);

    printf("name: %s city: %s\n", $row[0],$row[1]);

    //free result set
    mysqli_free_result($result);
}

mysqli_close($con);
?>