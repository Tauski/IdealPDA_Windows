<?php

 if($_SERVER['REQUEST_METHOD']=='POST'){

 include '../Config/DatabaseConfig.php';
 
 $con = mysqli_connect($HostName,$User,$Password,$dbName,$Port);
 
 $FL_NAME = $_POST['f_name'];
 $EDATE = $_POST['date'];

 $Sql_Query = "SELECT event, timeofevent FROM userevents WHERE user = '$FL_NAME' AND dateofevent = '$EDATE'";
 
$result = array();
$result['data'] = array();
$response = mysqli_query($con,$Sql_Query);

while($row = mysqli_fetch_array($response))
{
	if($row['event'] != '' || $row['event'] != NULL)
	{
		$index['event'] = $row['0'];
		array_push($result['data'], $index);
	}		
}

$result["success"] = "1";
echo json_encode($result);
}
mysqli_close($con);
?>