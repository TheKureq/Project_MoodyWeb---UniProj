<?php
if(isset($_POST["submit"]))
{
    $name = $_FILES["obraz"]["name"];
    $tmpname = $_FILES["obraz"]["tmp_name"];
    if($name == "")
    {
        header("Location: gallery.php"); 
    }
    else
    {
    move_uploaded_file($tmpname, "img/$name");

    $conn = new mysqli("localhost","root","","test");
    $conn->set_charset("utf8");
    $result = $conn->query("INSERT INTO zdjecia VALUES (NULL,'', 'img/$name')");
    header("Location: gallery.php"); 
    }
}
