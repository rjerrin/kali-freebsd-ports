<html>
<body>

<form action="test.php" method="post">
Name: <input type="text" name="name"><br>
E-mail: <input type="text" name="email"><br>
<input type="submit">
</form>

</body>
</html> 
<?php 
	echo "the input is \n";
		var_dump($_POST["name"]); 
	
?>
