const nav = document.querySelector('.nav__ul');


addEventListener('scroll',() => {
    window.scrollY < 50 ? nav.style.backgroundColor = '' :  nav.style.backgroundColor = 'rgba(0,0,0,0.2)';
})