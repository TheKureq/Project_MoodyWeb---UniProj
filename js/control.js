$(document).ready(function () {
	// BUTTONS AND SLIDERS
	let axis1 = document.querySelector('.axis1');
	let axis2 = document.querySelector('.axis2');
	let axis3 = document.querySelector('.axis3');
	let axis4 = document.querySelector('.axis4');
	let axis5 = document.querySelector('.axis5');
	let axis6 = document.querySelector('.axis6');
	let zeroBtn = document.querySelector('.zero');
	let sliders = document.querySelectorAll('.axis-slider');
	let outputs = document.querySelectorAll('.axis__value');

	// ESP8266 COMUNICATION
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

		// ZERO BUTTON - RESET SLIDERS ON CLICK
		if (p == 1010) {
			outputs[0].innerHTML = 90;
    		sliders[0].value = 90;
			outputs[1].innerHTML = 90;
    		sliders[1].value = 90;
			outputs[2].innerHTML = 90;
    		sliders[2].value = 90;
			outputs[3].innerHTML = 75;
    		sliders[3].value = 75;
			outputs[4].innerHTML = 75;
    		sliders[4].value = 75;
			outputs[5].innerHTML = 60;
    		sliders[5].value = 60;
		}
	});
	$('.axis1').on('click touchend', function () {
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


	
	let btnon = document.querySelector('.btn');
	btnon.addEventListener('click', () => {
		console.log('test');
	})


	// SLIDERS VALUE 
	outputs.forEach((x,i) => {
		x.innerHTML = sliders[i].value;
	})
	
	sliders.forEach((x,i) => {
		x.oninput = function() {
			outputs[i].innerHTML = x.value;
		}
	})



	// .........
	// SEQUENCES
	// .........

	$('.btnStart').on('click touchend', function () {
		let sequenceLoop = document.getElementById('loop').checked
		let p = '';

		if (sequenceLoop === false) {
			console.log('Loop On');
			p = 'lon';		
		}
		else {
			p = 'lof';
			console.log('Loop Off');
		}

		const sequenceArray = [...document.querySelectorAll('.draggableTask')]
		for (let i = 0; i < sequenceArray.length; i++) {
			let task
			p += sequenceArray[i].getAttribute('value');
			if (sequenceArray[i].getAttribute('value') == 'A') {
				if ((!isNaN(sequenceArray[i].children[1].value) && !isNaN(sequenceArray[i].children[2].value))) {
					p += 'x' + (sequenceArray[i].children[1].value-1);	
					p += 'v' + sequenceArray[i].children[2].value;
					p += ' '
				}
			}
			else if (sequenceArray[i].getAttribute('value') == 'B') {
				if (!isNaN(sequenceArray[i].children[1].value) && !isNaN(sequenceArray[i].children[2].value) && !isNaN(sequenceArray[i].children[5].value) && !isNaN(sequenceArray[i].children[6].value)) {
					p += 'x' + (sequenceArray[i].children[1].value-1);
					p += 'v' + sequenceArray[i].children[2].value;
					p += 'y' + (sequenceArray[i].children[5].value-1);
					p += 'z' + sequenceArray[i].children[6].value;
					p += ' ';
				}
			}
			else if (sequenceArray[i].getAttribute('value') == 'C') {p += ' ';}
			else if (sequenceArray[i].getAttribute('value') == 'D') {p += ' ';}
			else if (sequenceArray[i].getAttribute('value') == 'E') {p += ' ';}
			else if (sequenceArray[i].getAttribute('value') == 'F') {
				p += 'd' + (sequenceArray[i].children[1].value);
				p += ' ';
			}
		}

		console.log(p)
		$.get(adress, { seqon: p });
	});

	$('.btnStop').on('click touchend', function () {
		let p = "1"
		$.get(adress, { seqof: p });
		console.log('stop')
	});
});
