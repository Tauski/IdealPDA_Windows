<?php

 if($_SERVER['REQUEST_METHOD']=='POST'){

 include '../Config/DatabaseConfig.php';
 
 $con = mysqli_connect($HostName,$User,$Password,$dbName,$Port);
 
 $FL_NAME = $_POST['fl_name'];
 $NEW_ENAME = $_POST['event'];
 $OLD_ENAME = $_POST['oldevent'];
 $NEW_ELOCATION = $_POST['elocation'];
 $NEW_EDESCRIPTION = $_POST['edescription'];
 $NEW_EDATE = $_POST['edate'];
 $NEW_ETIME = $_POST['etime'];

 $Sql_Query = "UPDATE usernotes SET event = '$NEW_ENAME', dateofevent = '$NEW_EDATE', timeofevent = '$NEW_ETIME', location = '$NEW_ELOCATION', description = '$NEW_EDESCRIPTION' WHERE user = '$FL_NAME' AND event = '$OLD_ENAME'";

if(mysqli_query($con,$Sql_Query)){
	    echo "Note Updated";
} else {
    echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
}

}
mysqli_close($con);
?>