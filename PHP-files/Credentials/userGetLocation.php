<?php
if($_SERVER['REQUEST_METHOD']=='POST'){

 include '../Config/DatabaseConfig.php';

$con = mysqli_connect($HostName,$User,$Password,$dbName,$Port);

$FL_NAME = $_POST['f_name'];

///get location from userdatabase
$query = "SELECT location FROM users WHERE f_name = '$FL_NAME' ";
$result = $con->query($query);

if($result->num_rows > 0)
{
	while($row = $result->fetch_assoc())
	{
		$echoRow = $row['location'];
		$echoRow .= ' locationID';
		echo $echoRow;
	}
}else{
	echo "ERROR: Couldn't find location with this username";
}

} 
mysqli_close($con);
?>