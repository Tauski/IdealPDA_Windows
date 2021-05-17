<?php

 if($_SERVER['REQUEST_METHOD']=='POST'){

 include '../Config/DatabaseConfig.php';
 
 $con = mysqli_connect($HostName,$User,$Password,$dbName,$Port);
 
 $FL_NAME = $_POST['fl_name']; 
 $OLD_NOTE = $_POST['oldnote'];

 $Sql_Query = "DELETE FROM usernotes WHERE note = '$OLD_NOTE' AND user = '$FL_NAME'";

if(mysqli_query($con,$Sql_Query)){
	    echo "Note Deleted";
} else {
    echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
}

}
mysqli_close($con);
?>