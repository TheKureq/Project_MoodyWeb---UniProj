<?php
            $conn = new mysqli("localhost","root","","test");
            $conn->set_charset("utf8");

        //Zapamiętuje strona że sie logowaliśmy 
        // session_start();

        if(isset ($_SESSION["nazwa"]) && isset($_GET["logout"]))
        {
            unset($_SESSION["nazwa"]);

            header ("Location: index.php");
            exit();

        }
       
        $login2 = $_POST["nazwa"];
        $password = $_POST["password"];
        $password = md5($password); 
    
        if(isset ($_POST["button"]))
        {
                $valid = true; //sprawdza czy wszystko jest OK
            

                //Sprawdza czy jest wypełnione
                if(empty($_POST["nazwa"]))
                {
                    $valid = false;
                }

                if(empty($_POST["password"]))
                {
                    $valid = false;
                }
          
                else
                {
                
                    $err = 'Błąd logowania błedy login lub hasło';
                    header("Location: login1.php");
                }
        }

            $sql = "SELECT * FROM rejestracja WHERE login='$login2' AND password='$password'";
            $result = mysqli_query($conn, $sql);
            if($valid == true)
            {
                if (mysqli_num_rows($result) === 1) 
                {
                    $row = mysqli_fetch_assoc($result);
                    if ($row["login"] === $login2 && $row["password"] === $password) 
                    {
                        $_SESSION["nazwa"] = $row["login"];
                        $_SESSION["password"] = $row["password"];
                        header("Location: control.php");
                        exit();
                    }
                    else
                    {
                      
                    $err = 'Wrong Login or Password';
                    

                    }
                }
                else
                    {
                      
                    $err = 'Wrong Login or Password';
                    

                    }
            }   
            else
            {
                $err = 'Wrong Login or Password';
            }
        
    ?>