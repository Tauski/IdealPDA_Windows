<?php

 if($_SERVER['REQUEST_METHOD']=='POST'){

 include '../Config/DatabaseConfig.php';
 
 $con = mysqli_connect($HostName,$User,$Password,$dbName,$Port);
 
 $FL_NAME = $_POST['f_name'];
 $E_EVENT = $_POST['event'];

 $Sql_Query = "SELECT event, dateofevent, timeofevent, location, description FROM userevents WHERE user = '$FL_NAME' AND event = '$E_EVENT'";
 
$calendarID = 'eventID'; 
$result = array();
$result['data'] = array();
$response = mysqli_query($con,$Sql_Query);

while($row = mysqli_fetch_array($response))
{
	if($row['event'] != '' || $row['event'] != NULL)
	{
		$index['event'] = $row['0'];
		$index['dateofevent'] = $row['1'];
		$index['timeofevent'] = $row['2'];
		$index['location'] = $row['3'];
		$index['description'] = $row['4'];
		array_push($result['data'], $index);
		array_push($result['data'], $calendarID);
	}		
}

$result["success"] = "1";
echo json_encode($result);
}
mysqli_close($con);
?>