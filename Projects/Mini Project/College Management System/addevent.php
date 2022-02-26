<?php

$conn= mysqli_connect("localhost","root","","coll");
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
$up=$_POST["upd"];
        $uq="insert into events(Ev)  values('$up')";
        $updte="select Ev from events";
        mysqli_query($conn, $uq); 
        echo "<script>location.href='events.php'</script>";
        
       
?>