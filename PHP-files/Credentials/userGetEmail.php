<?php
if($_SERVER['REQUEST_METHOD']=='POST'){

 include '../Config/DatabaseConfig.php';

$con = mysqli_connect($HostName,$User,$Password,$dbName,$Port);

$FL_NAME = $_POST['f_name'];

//check if the user is taken 
$query = "SELECT email FROM users WHERE f_name = '$FL_NAME' ";
$result = $con->query($query);

if($result->num_rows > 0)
{
	while($row = $result->fetch_assoc())
	{
		echo $row['email'];
	}
}else{
	echo "Couldn't find email with this username";
}

} 
mysqli_close($con);
?>