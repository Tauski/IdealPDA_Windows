<?php

 if($_SERVER['REQUEST_METHOD']=='POST'){

 include '../Config/DatabaseConfig.php';
 
 $con = mysqli_connect($HostName,$User,$Password,$dbName,$Port);
 
 $FL_NAME = $_POST['f_name'];
 
 $Sql_Query = "SELECT note FROM usernotes WHERE user = '$FL_NAME'";
 
$notesID = 'notesID';
$result = array();
$result['data'] = array();
$response = mysqli_query($con,$Sql_Query);

while($row = mysqli_fetch_array($response))
{
		if($row['note'] != '' || $row['note'] != NULL)
	{
		$index['note'] = $row['0'];
		array_push($result['data'], $index);
		array_push($result['data'], $notesID);
	}		
}

$result["success"] = "1";
echo json_encode($result);

}
mysqli_close($con);
?>