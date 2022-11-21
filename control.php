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
</head>

<body>

    <!-- NAVIGATION SECTION -->
    <?php 
    include 'navigation.php';

    if(!isset($_SESSION['nazwa']))
    {
        print '<h1>Musisz byc zalogowany</h1>';
        header("Location: login1.php");
        exit();
    }    
    
    
    ?>


    <!-- HERO SECTION -->
    <section id="hero" class="hero" style="height: 50vh;">
        <div class="hero__info">
            <div class="hero__title">
                <p>MoodyV1</p>
            </div>
            <div class="hero__text">
                <p>You can control robot now!!</p>
            </div>
        </div>
        <div class="hero__subpage">
            <div class="hero__card hero__card--1"></div>
        </div>
        <div class="hero--shadow"></div>
    </section>



    <section id="control" class="control">
        <div class="container">
            <div class="section-title">
                Control Panel
            </div>
            <div class="control__box">
                <div class="control__ip-box">
                    <input type="text" name="ip-adress" id="ip" class="ip" value="10.0.0.12" placeholder="ip adress">
                </div>
                <div class="control__buttons">
                    <button class="button btn" value="1001">Axis
                        1</button>
                    <button class="button btn" value="1002">Axis
                        2</button>
                    <button class="button btn" value="1003">Axis
                        3</button>
                    <button class="button btn" value="1004">Axis
                        4</button>
                    <button class="button btn" value="1005">Axis
                        5</button>
                    <button class="button btn" value="1006">
                        Gripper</button>
                    <button class="button btn" value="1007">
                        Demo</button>
                    <button class="button btn" value="1008">
                        Seq 1</button>
                    <button class="button btn" value="1009">
                    Seq 2</button>
                    <!-- <button class="button btn" value="1010">
                    Seq 3</button> -->
                        
                    <button class="button btn btn--estop" value="1008">
                        E-Stop</button>

                    <div class="slidecontainer">
                        <div><input class="axis1 axis-slider" type="range" min="0" max="180" value="90" id="myRange">
                            Axis 1 Value: <span class="axis__value1 axis__value"></span></div>
                        <div><input class="axis2 axis-slider" type="range" min="0" max="180" value="90" id="myRange">
                            Axis 2 Value: <span class="axis__value2 axis__value"></span></div>
                        <div><input class="axis3 axis-slider" type="range" min="0" max="160" value="80" id="myRange">
                            Axis 3 Value: <span class="axis__value3 axis__value"></span></div>
                        <div><input class="axis4 axis-slider" type="range" min="0" max="150" value="75" id="myRange">
                            Axis 4 Value: <span class="axis__value4 axis__value"></span></div>
                        <div><input class="axis5 axis-slider" type="range" min="0" max="150" value="75" id="myRange">
                            Axis 5 Value: <span class="axis__value5 axis__value"></span></div>
                        <div><input class="axis6 axis-slider" type="range" min="30" max="90" value="60" id="myRange">
                            Gripper Value: <span class="axis__value6 axis__value"></span></div>
                    </div>
                </div>
                <div class="control__visualization">

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

    <script src="./js/slider.js"></script>
    <script src="./js/jquery.min.js"></script>
    <script src="./js/control.js"></script>
    <script src="./js/main.js"></script>
    <script type="text/javascript" src="//code.jquery.com/jquery-1.11.0.min.js"></script>
    <script type="text/javascript" src="//code.jquery.com/jquery-migrate-1.2.1.min.js"></script>
    <script type="text/javascript" src="//cdn.jsdelivr.net/npm/slick-carousel@1.8.1/slick/slick.min.js"></script>
    <script src="./js/slicksettings.js"></script>
</body>

</html>