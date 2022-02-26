
<html>
<body  style="background-color:lightgrey">

<h3 style="text-align:center"><i>Events</i></h3>
<br>
<img src="ms.jpg"width="300px" height="150px"></img><img src="eve.jpg"width="300px" height="150px"></img>
<marquee style="font-family:Cursive;font-size:14pt;color:brown;"scrollamount="6"direction="left">Department of Electronics and Instrumentation Engineering in association with TI university program of Texas Instruments is conducting a Faculty Development Program on ‘ARM Cortex</marquee>
<marquee behavior="alternate" direction="left">The Department of Electronics and Communication Engineering is planning to conduct One Day National Workshop on“Network Simulator” on September 2015</marquee>
<marquee style="font-family:Cursive;font-size:14pt;color:grey;"scrollamount="6"direction="left">Department of Civil Engineering is Conducting One Day Workshop on “<b>Modern Surveying”</b> on 22<sup>nd </sup>September 2015 (Tuesday) in &#8216;B&#8217; Block Seminar Hall.</marquee>
<marquee behavior="scroll" direction="right">Department of Electronics & Instrumentation organizes National Symposium on Instrumentation (NSI 40) from Oct 30th to 31st 2015</marquee>
<?php

$conn=mysqli_connect("localhost","root","","coll");
$updte="select Ev from events";
$op=mysqli_query($conn, $updte); 
while($result=mysqli_fetch_assoc($op))
{
echo $result['Ev'];

}

?>	
</body>
</html>