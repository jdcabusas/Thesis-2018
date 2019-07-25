<?php
// Include config file
require_once 'config.php';
 
// Define variables and initialize with empty values
$location = "EMPTY";
$location_err = "";
 
// Processing form data when form is submitted

    //Get hidden input value
    $id =  trim($_GET["id"]);
    
    
 
        // Prepare an update statement
        $sql = "UPDATE bins SET status=:location WHERE id=:id";
 
        if($stmt = $pdo->prepare($sql)){
            // Bind variables to the prepared statement as parameters
            $stmt->bindParam(':location', $param_location);
            $stmt->bindParam(':id', $param_id);
            
            // Set parameters
            $param_location = $location;
            $param_id = $id;
            
            // Attempt to execute the prepared statement
            if($stmt->execute()){
                // Records updated successfully. Redirect to landing page
                header("location: index.php");
                exit();
            } else{
                echo "Something went wrong. Please try again later.";
            }
        }
         
        // Close statement
        unset($stmt);
    
    
    // Close connection
    unset($pdo);


?>