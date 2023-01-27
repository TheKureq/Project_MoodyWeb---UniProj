<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>MoodyWeb 🦾</title>
    <link href="https://fonts.googleapis.com/css2?family=Silkscreen:wght@400;700&display=swap" rel="stylesheet">
    <link rel="stylesheet" type="text/css" href="//cdn.jsdelivr.net/npm/slick-carousel@1.8.1/slick/slick.css" />
    <link rel="stylesheet" href="./css/main.css">
    <link rel="stylesheet" href="./css/pumpkin.css">
    <link rel="stylesheet" type="text/css"
        href="https://cdnjs.cloudflare.com/ajax/libs/slick-carousel/1.8.1/slick.css" />

    <script src="https://unpkg.com/feather-icons"></script>

    <link href="css/lightbox.css" rel="stylesheet">
    <link href="css/lightbox.min.css" rel="stylesheet">
    <script src="js/lightbox-plus-jquery.js"></script>
</head>

<body>

    <!-- NAVIGATION SECTION -->
    <?php include 'navigation.php';?>


    <!-- HERO SECTION -->
    <section id="hero" class="hero" style="height: 50vh;">
        <div class="hero__info">
            <div class="hero__title">
                <p>MoodyV1</p>
            </div>
            <div class="hero__text">
                <p>You are in gallery section, enjoy!</p>
            </div>
        </div>
        <div class="hero__subpage">
            <div class="hero__card hero__card--1"></div>
        </div>
        <div class="hero--shadow"></div>
    </section>
    <section id="login" class="login">
    <?php

    if(isset($_SESSION['nazwa']))
    {

        print '    <div class="file-label"><form action="gallery1.php" method="POST" enctype="multipart/form-data" class="login__form">'; 
        print '        <input type="file" class="file" id="file" name="obraz" >';
        print '        <label for="file">Select File</label>';
        print '        <input type="submit" name="submit" class="button" value="ADD PHOTO">';
        print '    </form></div>';

    }
    ?>
    </div>
    </section>
        <div class="gallery">
        <div class="section-title">gallery</div>
        <?php
                $conn = new mysqli("localhost","root","","test");
                $conn->set_charset("utf8");
                $result = $conn->query("SELECT * FROM zdjecia");
                while ($row = $result->fetch_assoc())
                {
                    $obraz = $row["obraz"];
                    print "<a class='photo_galery' href='$obraz' data-lightbox='foto1' data-title='Moody'>";
                    print "<img src='$obraz' alt='' height='200'></img></a>";
                }
            ?>
            </div>
            </div>
        </div>
    </section>


    <!-- CONTACT SECTION -->
    <section id="contact" class="contact">
        <div class="container">
            <div class="section-title">Developers</div>
            <div class="contact__box">
                <div class="contact__card--one contact__card">
                    <h3>Michal Kurek <i data-feather="tool"></i></h3>
                    <p>+48 000 000 000 <i data-feather="smartphone"></i></p>
                    <p>email@gmail.com <i data-feather="at-sign"></i></p>
                    <a href="https://github.com/TheKureq">Github <i data-feather="github"></i></a>
                </div>
                <div class="contact__card--two contact__card">
                    <h3>Samir Abu Safieh <i data-feather="cpu"></i></h3>
                    <p>+48 000 000 000 <i data-feather="smartphone"></i></p>
                    <p>email@gmail.com <i data-feather="at-sign"></i></p>
                    <a href="https://github.com/Samir420692137">Github <i data-feather="github"></i></a>
                </div>
            </div>
        </div>
    </section>


    <!-- FOOTER SECTION -->
    <footer>
        <div class="footer">
            <p>MoodyWeb &copy; <span class="footer--year">2022</span><br> Michal Kurek & Samir Abu Safieh</p>
        </div>


    </footer>

    <script>
        feather.replace()
    </script>


    <script src="./js/main.js"></script>
    <script type="text/javascript" src="//code.jquery.com/jquery-1.11.0.min.js"></script>
    <script type="text/javascript" src="//code.jquery.com/jquery-migrate-1.2.1.min.js"></script>
    <script type="text/javascript" src="//cdn.jsdelivr.net/npm/slick-carousel@1.8.1/slick/slick.min.js"></script>
    <script src="./js/slicksettings.js"></script>
</body>

</html>