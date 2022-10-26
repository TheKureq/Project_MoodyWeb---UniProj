<?php
//  zmienne
    $login = $_POST['login'];
    $password = $_POST['password'];

// łączenie z bazom
    $conn = new mysqli("localhost", "root", "", "test");
    if($conn->connect_error)
    {
        die("Failed to connect" .$conn->connect_error);
    }
    else
    {
        $stmt = $conn->prepare("SELECT * FROM rejestracja WHERE login = ? ");
        $stmt -> bind_param("s", $login);
        $stmt -> execute();
        $stmt_result = $stmt->get_result();
        if($stmt_result->num_rows > 0)
        {
            $data = $stmt_result -> fetch_assoc();
            if($data['password'] === $password)
            {
                header('Location: control.html');
                exit();
            }
        }
        else
        {
            print "invalid Email or Password";
        }
    }





?>