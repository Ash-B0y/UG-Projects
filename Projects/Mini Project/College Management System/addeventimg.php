<?php

$conn= mysqli_connect("localhost","root","","coll");
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
$us=$_POST["image"];
$file = $_FILES['image']['tmp_name'];

  if (!isset($file))
     echo "please select file";
  else
  {

     $image= addslashes(file_get_contents($_FILES['image']['tmp_name']));
     if (!$uq= mysql_query("INSERT INTO image VALUES ('$image')"))
             echo "Problem";
}
 mysqli_query($conn, $uq); 
        echo "<script>location.href='events.php'</script>";
        
       
?>