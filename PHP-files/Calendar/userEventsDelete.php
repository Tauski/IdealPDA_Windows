<?php

 if($_SERVER['REQUEST_METHOD']=='POST'){

 include '../Config/DatabaseConfig.php';
 
 $con = mysqli_connect($HostName,$User,$Password,$dbName,$Port);
 
 $FL_NAME = $_POST['fl_name']; 
 $OLD_EVENT = $_POST['oldevent'];

 $Sql_Query = "DELETE FROM userevents WHERE event = '$OLD_EVENT' AND user = '$FL_NAME'";

if(mysqli_query($con,$Sql_Query)){
	    echo "Event Deleted";
} else {
    echo "ERROR: Could not execute $sql. " . mysqli_error($link);
}

}
mysqli_close($con);
?>