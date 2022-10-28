



function main() {

    // variables
    const nav = document.querySelector('.nav__ul');
    const navMobile = document.querySelector('.nav__ul--mobile');
    const menu = document.querySelector('.menu');
    
    
    let variable = 1;
    

    function navigationToggle () {
   

        if (variable == 1) {
            navMobile.style.left = '0'
            variable = 0;
        } else {
            navMobile.style.left = '-100%'
            variable = 1;
        }


    }

    // listeners
    
    menu.addEventListener('click', navigationToggle)

    addEventListener('scroll', () => {
        window.scrollY < 50
            ? (nav.style.backgroundColor = '')
            : (nav.style.backgroundColor = 'rgba(0,0,0,0.2)');
    });
}

addEventListener('DOMContentLoaded', main);
