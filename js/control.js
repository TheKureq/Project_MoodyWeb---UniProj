<<<<<<< HEAD
$(document).ready(function () {
	let ip = document.querySelector('.ip');
	let ip_adress = '';
    let adress = 'http://' + ip.value + ':80/';
    console.log(adress);

	ip.addEventListener('input', () => {
		ip_adress = ip.value;
		console.log(ip_adress);
		adress = 'http://' + ip_adress + ':80/';
		console.log(adress);
	});

	$('.button').on('click touchend', function () {
		var p = $(this).attr('value');
		$.get(adress, { select: p });

		// 192.168.137.230 telefon
		// 10.0.0.12:80 dltech1 local
		console.log('axis');
	});
	$('.axis1').on('click touchend', function () {
		// dodać on telephone click
		var p = $(this).attr('value');
		$.get(adress, { axis1: p });
		console.log('axis1');
	});
	$('.axis2').on('click touchend', function () {
        console.log('axis2');
		var p = $(this).attr('value');
		$.get(adress, { axis2: p });
	});
	$('.axis3').on('click touchend', function () {
		var p = $(this).attr('value');
        console.log('axis3');
		$.get(adress, { axis3: p });
	});
	$('.axis4').on('click touchend', function () {
		var p = $(this).attr('value');
		$.get(adress, { axis4: p });
        console.log('axis4');
	});
	$('.axis5').on('click touchend', function () {
		var p = $(this).attr('value');
		$.get(adress, { axis5: p });
        console.log('axis5');
	});
	$('.axis6').on('click touchend', function () {
		var p = $(this).attr('value');
		$.get(adress, { axis6: p });
        console.log('axis6');
	});
});
=======
$(document).ready(function(){
    $(".button").click(function(){
        var p = $(this).attr('value');
        $.get("http://10.0.0.12:80/", {select:p});
    });
    $(".axis1").click(function(){
        var p = $(this).attr('value');
        $.get("http://10.0.0.12:80/", {axis1:p});
    });
    $(".axis2").click(function(){
        var p = $(this).attr('value');
        $.get("http://10.0.0.12:80/", {axis2:p});
    });
    $(".axis3").click(function(){
        var p = $(this).attr('value');
        $.get("http://10.0.0.12:80/", {axis3:p});
    });
    $(".axis4").click(function(){
        var p = $(this).attr('value');
        $.get("http://10.0.0.12:80/", {axis4:p});
    });
    $(".axis5").click(function(){
        var p = $(this).attr('value');
        $.get("http://10.0.0.12:80/", {axis5:p});
    });
});
>>>>>>> b64b1fde5fceb67526597633a6218113f9e3a6da
