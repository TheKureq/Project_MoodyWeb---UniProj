<?php
        session_start();
?>

<!-- NAV SECTION -->
<nav id="link" class="nav">


    <ul class="nav__ul--mobile">
        <li><a class="navi" href="index.php">HOMEPAGE</a></li>
        <li><a class="navi" href="about.php">ABOUT PROJECT</a></li>
        <?php
            if(isset ($_SESSION["nazwa"]))
            {

                echo '<li><a class="navi" href="control.php">CONTROL PANEL</a></li>';
                echo '<li><a class="navi__logout-btn" href="logout.php">LOG OUT</a></li>';
            }
            else
            {
                echo '<li><a class="navi" href="login1.php">LOG IN</a></li>';
                
            }
            ?>
        <li><a class="navi" href="gallery.php">GALLERY</a></li>
    </ul>

    <div class="nav__mobile">
        <button class="menu"
            onclick="this.classList.toggle('opened');this.setAttribute('aria-expanded', this.classList.contains('opened'))"
            aria-label="Main Menu">
            <svg width="64" height="64" viewBox="0 0 100 100">
                <path class="line line1"
                    d="M 20,29.000046 H 80.000231 C 80.000231,29.000046 94.498839,28.817352 94.532987,66.711331 94.543142,77.980673 90.966081,81.670246 85.259173,81.668997 79.552261,81.667751 75.000211,74.999942 75.000211,74.999942 L 25.000021,25.000058" />
                <path class="line line2" d="M 20,50 H 80" />
                <path class="line line3"
                    d="M 20,70.999954 H 80.000231 C 80.000231,70.999954 94.498839,71.182648 94.532987,33.288669 94.543142,22.019327 90.966081,18.329754 85.259173,18.331003 79.552261,18.332249 75.000211,25.000058 75.000211,25.000058 L 25.000021,74.999942" />
            </svg>
        </button>
    </div>



    <ul class="nav__ul">
        <li><a class="navi" href="index.php">HOMEPAGE</a></li>
        <li><a class="navi" href="about.php">ABOUT PROJECT</a></li>
        <li><a class="navi" href="index.php">
                <div class="moody"></div>
            </a></li>
            <?php
            if(isset ($_SESSION["nazwa"]))
            {

                echo '<li><a class="navi" href="control.php">CONTROL PANEL</a></li>';
                echo '<li><a class="navi__logout-btn" href="logout.php">LOG OUT</a></li>';
            }
            else
            {
                echo '<li><a class="navi" href="login1.php">LOG IN</a></li>';
                
            }
            ?>
        <li><a class="navi" href="gallery.php">GALLERY</a></li>
    </ul>

    <?php
    if(isset ($_SESSION["nazwa"]))
    {
        echo '<div class="loginStatus">';
        echo'<div class="dot">';
        echo '<div class="dottest dottest--admin"></div>';
        echo'</div>';
        echo'</div>';
    }
    else
    {
        echo '<div class="loginStatus">';
        echo'<div class="dot">';
        echo '<div class="dottest"></div>';
        echo'</div>';
        echo'</div>';
    }
    ?>
</nav>