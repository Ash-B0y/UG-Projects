<!Doctype html>
<html>
<body  style="background-color:#b0c4de">
<h1><i>FACULTY LIST</i></h1>
<head>
<style>
table,th,td{
width:50%;
padding:15px;
border:1px groove #112233;
font-family:forte;

}
</style>
</head>

<body>
<?php
$dept=$_GET["dept"];
$co=mysqli_connect("localhost","root","","coll");
$q="select Id,Name,Sex,Programme,Position from faculties where Department='$dept'";
$op=mysqli_query($co,$q);

echo "<table>
<td>Name</td>
<td>Id</td>
<td>Sex</td>
<td>Programme</td>
<td>Position</td>
</th>";
while($result=mysqli_fetch_assoc($op))
{

echo "<tr><td>".$result['Name']."</td><td>".$result['Id']."</td><td>".$result['Sex']."</td><td>".$result['Programme']."</td><td>".$result['Position']."</td></tr>";

}
echo "</table>";

?>
</body>
</html>