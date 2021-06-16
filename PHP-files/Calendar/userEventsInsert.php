<?php
if($_SERVER['REQUEST_METHOD']=='POST'){

 include '../Config/DatabaseConfig.php';

$con = mysqli_connect($HostName,$User,$Password,$dbName,$Port);

$FL_NAME = $_POST['fl_name'];
$EVENT = $_POST['event'];
$DATEOFEVENT = $_POST['edate'];
$TIMEOFEVENT = $_POST['etime'];
$LOCATION = $_POST['elocation'];
$DESCRIPTION = $_POST['edescription'];

echo $DATEOFEVENT;

	$sql_query = "INSERT INTO userevents (user,event,dateofevent,timeofevent,location,description) values ('$FL_NAME','$EVENT','$DATEOFEVENT','$TIMEOFEVENT','$LOCATION','$DESCRIPTION')";
	if(mysqli_query($con,$sql_query)){
		echo 'Event Saved';
	}
	else{
		echo 'something else went wrong';
	}
}
mysqli_close($con);
?>