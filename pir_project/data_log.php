<?php
/*************************************************************************************************
 *  Created By: Debabrata Mitra
 *  Created On: 10 march, 2024
 ***********************************************************************************************/
 
$hostname = "127.0.0.1"; 
$username = "root"; 
$password = ""; 
$database = "motion_db"; 

$conn = mysqli_connect($hostname, $username, $password, $database);

if (!$conn) { 
	die("Connection failed: " . mysqli_connect_error()); 
} 

echo "Database connection is OK<br>"; 

if(isset($_POST["SensorId"]) && isset($_POST["SensorStatus"])) {

	$t = $_POST["SensorId"];
	
	$h = $_POST["SensorStatus"];

	$sql = "INSERT INTO pir (SensorId, SensorStatus) VALUES (".$t.", ".$h.")"; 

	if (mysqli_query($conn, $sql)) { 
		echo "\nNew record created successfully"; 
	} else { 
		echo "Error: " . $sql . "<br>" . mysqli_error($conn); 
	}
}

?>