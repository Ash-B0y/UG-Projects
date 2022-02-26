<!DOCTYPE html>
<html>
<body>
<?php
$servername="localhost";
$username="root";
$password="";
$dbname="coll";
$conn= mysqli_connect($servername, $username, $password, $dbname);
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
$email=$_POST["email"];
$password=$_POST["password"];
$upda=$_POST["booleantype"];

$sql="SELECT * FROM admin WHERE Username='$email' AND Password='$password'";

$result=mysqli_query($conn, $sql);

if (mysqli_num_rows($result) > 0) 
{
   if($upda=="r1")
   {
        echo "<script>location.href='upd.html'</script>";
        $up=$_POST["upd"];
        $uq="insert into events values('$up')";
        $updte="select Ev from events";
         }
else if($upda=="r2")
{
 echo "<script>location.href='events.php'</script>";
}
}
 else {  
        if(($upda=="r1")||($upda=="r2"))
        {
        echo "<script>alert('Invalid email or password')</script>"; 
        echo "<script>location.href='valid.html'</script>";
      }
     }

mysqli_close($conn);
?>

</body>
</html>

        