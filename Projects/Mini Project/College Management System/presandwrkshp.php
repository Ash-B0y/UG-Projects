<!Doctype html>
<html>
<body  style="background-color:#b0c4de">
<h1><i>PRESENTATION AND WORKSHOP SCHEDULE</i></h1>
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

$conn=mysqli_connect("localhost","root","","coll");
$q="select Title,Id,StaffIncharge,type,date,time from wrkshpandpres";
$op=mysqli_query($conn,$q);

echo "<table>
<td>Title</td>
<td>Id</td>
<td>Staff Incharge</td>
<td>Type</td>
<td>Date</td>
<td>Time</td>
</th>";
while($result=mysqli_fetch_assoc($op))
{

echo "<tr><td>".$result['Title']."</td><td>".$result['Id']."</td><td>".$result['StaffIncharge']."</td><td>".$result['type']."</td><td>".$result['date']."</td><td>".$result['time']."</td></tr>";

}
echo "</table>";

?>
</body>
</html>