
let sliders = document.querySelectorAll(".axis-slider")
let outputs = document.querySelectorAll(".axis__value")
outputs.forEach((x,i) => {
    x.innerHTML = sliders[i].value;
})

sliders.forEach((x,i) => {
    x.oninput = function() {
        outputs[i].innerHTML = x.value;
    }
})
