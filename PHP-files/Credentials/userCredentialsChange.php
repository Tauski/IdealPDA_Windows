<?php

 if($_SERVER['REQUEST_METHOD']=='POST'){

 include '../Config/DatabaseConfig.php';
 
 $con = mysqli_connect($HostName,$User,$Password,$dbName,$Port);
 
 ///Set variables for all new and old data
 $OLD_NAME = $_POST['old_name'];
 $NEW_NAME = $_POST['new_name'];
 $OLD_PASSWORD = $_POST['old_password'];
 $NEW_PASSWORD = $_POST['new_password'];
 $OLD_EMAIL = $_POST['old_email'];
 $NEW_EMAIL = $_POST['new_email'];
 $OLD_LOCATION = $_POST['old_location'];
 $NEW_LOCATION = $_POST['new_location'];

///Check what operations are needed
if(empty($NEW_NAME))
{
	$nameBool = false;
}else{
	$nameBool = true;
}

if(empty($NEW_EMAIL))
{
	$emailBool = false;
}else{
	$emailBool = true;
}

if(empty($NEW_PASSWORD))
{
	$pwBool = false;
}else{
	$pwBool = true;
}

if(empty($NEW_LOCATION))
{
	$locBool = false;
}else{
	$locBool = true;
}

echo $nameBool;
echo $pwBool;
echo $emailBool;
echo $locBool;

 //First check if we have user with that username (it should have, becouse old name is retrieved from database in preperation for this...).
 $Sql_Query = "SELECT * FROM users WHERE f_name = '$OLD_NAME' ";
 
 $check = mysqli_fetch_array(mysqli_query($con,$Sql_Query));
 
 if(isset($check)){

 	///updating the email
	if($emailBool == true)
 	{
 		$Sql_Query = "UPDATE users SET email = '$NEW_EMAIL' WHERE f_name = '$OLD_NAME' AND email = '$OLD_EMAIL' ";
 		if(mysqli_query($con,$Sql_Query))
 		{
 			echo "email updated ";
 		}else{
 			echo "ERROR: while updating email";
 		}
 	}

 	///Updating the password
 	if($pwBool == true)
 	{
 		$Sql_Query = "UPDATE users SET password = '$NEW_PASSWORD' WHERE f_name = '$OLD_NAME' AND password = '$OLD_PASSWORD' ";
 		if(mysqli_query($con,$Sql_Query))
 		{
 			echo "password updated ";
 		}else{
 			echo "ERROR: while updating password";
 		}
 	}

	///Updating the name
 	if($locBool == true)
 	{
 		$Sql_Query = "UPDATE users SET location = '$NEW_LOCATION' WHERE f_name = '$OLD_NAME' AND location = '$OLD_LOCATION' ";
 		if(mysqli_query($con,$Sql_Query))
 		{
 			echo "location updated ";
 		}else{
 			echo "ERROR: while updating location";
 		}
 	}

 	
 		///Changing the name at the last place. Previous queries use old_name that will be changed if this query runs  
 	if($nameBool == true)
 	{
 		$Sql_Query = "UPDATE users SET f_name = '$NEW_NAME' WHERE f_name = '$OLD_NAME' ";
 		if(mysqli_query($con,$Sql_Query))
 		{
 			echo "user updated";
 		}else{
 			echo "ERROR: while updating username";
 		}

 		//change notes of this user to new username
 		$Sql_Query_note_change = "UPDATE usernotes SET user = '$NEW_NAME' WHERE user = '$OLD_NAME'";
 		if(mysqli_query($con,$Sql_Query_note_change))
 		{
 			echo "user updated";
 		}else{
 			echo "ERROR: while updating users notes";
 		}
 	}

 }
 else{
 echo "ERROR: Couldn't find user with given username";
 }
 }
mysqli_close($con);
?>