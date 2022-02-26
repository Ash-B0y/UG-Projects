<!doctype html>
<html>
<style>
body {
    background: url("529330_501847336529831_881927634_n.jpg");
    background-size: 1920px 1080px;
}
</style>
<body>
<?php
$conn= mysqli_connect("localhost","root","","test");
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
$n=$_POST["na"];
$c=$_POST["ca"];
$m=$_POST["ma"];
$p=$_POST["ph"];
$ce=$_POST["ch"];
$d=$_POST["de"];
$s=($m/2+$p/4+$ce/4);
echo "<font color='white'>Hi " .$n. ", your Cut-Off is:</font><input type='text' value=".$s.">";
echo"<br>";
echo"<br>";
echo "<font color='white'>Colleges available for suggestion:</font>";
echo"<br>";
echo"<br>";
 $updte="select Name,clginfo from clgsg where caste='$c'and dep='$d' and cutoff<='$s' ";
$result=mysqli_query($conn,$updte);
if(mysqli_num_rows($result)>0)
{
while($row=mysqli_fetch_assoc($result))
{
echo "<font color='white'>".$row['Name']."</font>";
echo"<br>";
echo "<font color='white'>".$row['clginfo']."</font>";
echo"<br>";
echo"<br>";
}
}
else
{
	echo"<br>";
	echo"<font color='white'>NO SUGGESTIONS AVAILABLE</font>";
}	
?>
</body>
</html>