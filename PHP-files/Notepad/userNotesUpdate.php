<?php

 if($_SERVER['REQUEST_METHOD']=='POST'){

 include '../Config/DatabaseConfig.php';
 
 $con = mysqli_connect($HostName,$User,$Password,$dbName,$Port);
 
 $FL_NAME = $_POST['fl_name'];
 $NOTE = $_POST['incnote'];
 $OLD_NOTE = $_POST['oldnote'];

 $Sql_Query = "UPDATE usernotes SET note = '$NOTE' WHERE user = '$FL_NAME' AND note = '$OLD_NOTE'";

if(mysqli_query($con,$Sql_Query)){
	    echo "Note Updated";
} else {
    echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
}

}
mysqli_close($con);
?>