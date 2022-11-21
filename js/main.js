



function main() {

    // variables
    const nav = document.querySelector('.nav__ul');
    const navMobile = document.querySelector('.nav__ul--mobile');
    const navMobileBar = document.querySelector('.nav__mobile');
    const menu = document.querySelector('.menu');
    
    let variable = 1;
    

    function navigationToggle () {
   

        if (variable == 1) {
            navMobile.style.left = '0'
            variable = 0;
            navMobileBar.style.backgroundColor = '';
        } else {
            navMobile.style.left = '-100%'
            variable = 1;
        }


    }

    // listeners
    
    menu.addEventListener('click', navigationToggle)

    addEventListener('scroll', () => {
        if (window.scrollY < 50) {
            nav.style.backgroundColor = '';
            navMobileBar.style.backgroundColor = '';
        }
        else {
            nav.style.backgroundColor = 'rgba(0,0,0,0.2)';
            navMobileBar.style.backgroundColor = 'rgba(0,0,0,0.2)';

            if (variable == 0) {
                navMobileBar.style.backgroundColor = '';
            }
        }
    });
}

addEventListener('DOMContentLoaded', main);
