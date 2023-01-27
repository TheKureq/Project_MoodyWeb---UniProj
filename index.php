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
        <link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Material+Symbols+Outlined:opsz,wght,FILL,GRAD@48,400,0,0" />
    <script src="https://unpkg.com/feather-icons"></script>
</head>

<body>

    <!-- NAVIGATION SECTION -->
    <?php include 'navigation.php';?>


    <!-- HERO SECTION -->
    <section id="hero" class="hero">
        <div class="hero__info">
            <div class="hero__title">
                <p>MoodyV1</p>
            </div>
            <div class="hero__text">
                <p>Welcome, learn more about our project!</p>
            </div>
            <a href="#shorts"><button class="hero__btn">
                    <p>👀</p>
                </button></a>


        </div>
        <div class="hero__slider">
            <div class="hero__card hero__card--1"></div>
            <div class="hero__card hero__card--2"></div>
            <div class="hero__card hero__card--6"></div>
            <div class="hero__card hero__card--3"></div>
            <div class="hero__card hero__card--4"></div>
            <div class="hero__card hero__card--5"></div>
            <div class="hero__card hero__card--7"></div>
        </div>
        <div class="hero--shadow"></div>
    </section>


    <!-- SHORTS SECTION - section based on grid (still learning this technology)-->
    <section id="shorts">
        <div class="shorts">
            <div class="container">
                <div class="section-title">Shorts 🩳
                </div>
                <div class="shorts__box">
                    <div class="shorts__card">
                        <div class="shorts__img"></div>
                        <div class="shorts__title">Current we are working on:</div>
                        <div class="shorts__info">
                            <ul>
                                <li>
                                    <p>Sequence system, with database</p>
                                </li>
                                <li>
                                    <p>database security</p>
                                </li>
                                <li>
                                    <p>responsivenes of the website</p>
                                </li>
                                <li>
                                    <p>web apperance</p>
                                </li>
                            </ul>
                        </div>
                    </div>
                    <div class="shorts__card">
                        <div class="shorts__img"></div>
                        <div class="shorts__title">Future development plan:</div>
                        <div class="shorts__info">
                            <ul>
                                <li>
                                    <p>Go online, place website in some hosting</p>
                                </li>
                                <li>
                                    <p>Inverse kinematics in control panel</p>
                                </li>
                                <li>
                                    <p>Learning mode in control panel</p>
                                </li>
                                <li>
                                    <p>Registration - user system to allow control your own moody!</p>
                                </li>
                            </ul>
                        </div>
                    </div>
                </div>
                <div class="shorts__box">
                    <div class="shorts__card">
                        <div class="shorts__img"></div>
                        <div class="shorts__title">Main links:</div>
                        <div class="shorts__info">
                            <a href="./control.php"><i data-feather="sliders"></i></a>
                            <a href="./about.php"><i data-feather="info"></i></a>
                            <a href="./gallery.php"><i data-feather="grid"></i></a>  
                            </div>
                        </div>
                        <div class="shorts__card">
                            <div class="shorts__img"></div>
                            <div class="shorts__title">Other links:</div>
                            <div class="shorts__info">
                                <a href="https://youtube.com"><i data-feather="youtube"></i></a>
                                <a href="https://www.instagram.com/kurek_workshop/"><i data-feather="instagram"></i></a>
                                <a href="https://github.com/TheKureq"><i data-feather="github"></i></a>                         
                        </div>
                    </div>
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
        </div>-
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