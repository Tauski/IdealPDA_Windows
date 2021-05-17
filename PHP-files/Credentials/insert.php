<?php
if($_SERVER['REQUEST_METHOD']=='POST'){

 include '../Config/DatabaseConfig.php';

$con = mysqli_connect($HostName,$User,$Password,$dbName,$Port);

$FL_NAME = $_POST['f_name'];
$EMAIL = $_POST['email'];
$PASSWORD = $_POST['password'];

//check if the user is taken 
$ChechSQL = "SELECT * FROM users WHERE f_name='$FL_NAME'";
$check = mysqli_fetch_array(mysqli_query($con,$ChechSQL));

if(isset($check)){
	echo 'Name is already taken';
}
else{
	$sql_query = "INSERT INTO users (f_name,email,password) values ('$FL_NAME','$EMAIL','$PASSWORD')";

	if(mysqli_query($con,$sql_query)){
		echo 'user created successfully';
	}
	else{
		echo 'something else went wrong';
	}
}
}

mysqli_close($con);
?>