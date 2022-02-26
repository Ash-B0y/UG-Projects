<!DOCTYPE html>
<html>
<body>
<?php
$servername="localhost";
$username="root";
$password="";
$dbname="port";
$conn= mysqli_connect($servername, $username, $password, $dbname);
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
$srvar=$_POST["bna"];

$sql="SELECT * FROM book WHERE Bookname like'%$srvar %'";

$result=mysqli_query($conn, $sql);

if (mysqli_num_rows($result) > 0) 
{
         echo "<script>alert('The Book is Available in the Portal')</script>";
      }
else
{
echo "<script>alert('Sorry!!!! The Book is not Available in the Portal')</script>";
           
}

mysqli_close($conn);
?>

</body>
</html>

        