const container = document.querySelector('.container-test');
let inputOne = document.querySelectorAll('.input1')
let inputThree = document.querySelectorAll('.input3')
let inputFour = document.querySelectorAll('.input4')
let index = 0;
// .................
// BUTTONS FUNCTIONS
// .................
document.addEventListener('mousemove', () => {
	let btnDelete = document.querySelectorAll('.btnX');
	btnDelete.forEach((x) => {
		x.onclick = () => {
			x.parentElement.parentElement.remove();
			container.childElementCount == 0 ? container.innerHTML = `<p class="info" id="test">You can drag task here!</p>` : {};
		};
	});
});

document.addEventListener('click', () => {
	inputOne = document.querySelectorAll('.input1')
	inputThree = document.querySelectorAll('.input3')
	inputFour = document.querySelectorAll('.input4')
})

// .................
// INPUT ERROR HANDLING
// .................
document.addEventListener('input touchend',(e) => {
	e.oninput = function () {
		if (this.value.length > 4) {
			console.log("test")
			this.value = this.value.slice(0,4); 
		}
	}
})


// ...................
// DRAG AND DROP LOGIC3
// ...................
function onDragStart(e) {
	e.dataTransfer.setData('text/plain', e.target.id);
	const id = e.dataTransfer.getData('text');
	const draggable = document.getElementById(id);
	draggable.classList.add('dragging');
}

function onDragStartTask(e) {
	e.dataTransfer.setData('text/plain', e.target.id);
	const id = e.dataTransfer.getData('text');
	const draggable = document.getElementById(id);
	draggable.classList.add('draggingTask');
}

function onDragOver(e) {
	e.preventDefault();
	const afterElement = getDragAfterElement(container, e.clientY);
	const draggable = document.querySelector('.draggingTask');

	if (draggable != null) {
		if (afterElement == null) {
			container.appendChild(draggable);
		} else {
			container.insertBefore(draggable, afterElement);
		}
	}
}

function onDrop(e) {
	// event.preventDefault();
	const id = e.dataTransfer.getData('text');
	const draggable = document.getElementById(id);
	const dropzone = document.getElementById('dest_copy');
	draggable.classList.remove('draggingTask');
	draggable.classList.remove('dragging');
	if (
		// copy task from programs panel
		id == 'src_copy-1' ||
		id == 'src_copy-2' ||
		id == 'src_copy-3' ||
		id == 'src_copy-4' ||
		id == 'src_copy-5' ||
		id == 'src_copy-6'
	) {
		document.getElementById('test')
			? dropzone.removeChild(document.getElementById('test'))
			: '';
		const draggableElementCpy = document.getElementById(id).cloneNode(true);
		draggableElementCpy.id = 'index' + index;
		draggableElementCpy.classList.add('draggableTask');
		draggableElementCpy.setAttribute('ondragstart', 'onDragStartTask(event)');
		draggableElementCpy.setAttribute('value',draggable.getAttribute('value'));

		inputOne = document.querySelectorAll('.input1')

		// Dynamically added new divs and buttons to tasks, for better controll
		let taskControl = document.createElement('div');
		taskControl.classList.add('sequence__task-control');

		let btnX = document.createElement('button');
		btnX.id = 'btnX';
		btnX.classList.add('btnX', 'btn');
		btnX.innerHTML = `<span class="material-symbols-outlined">
		close
		</span>`;

		switch (id) {
			case 'src_copy-1':
				// UWAGA NIE ZMIENIAC, KOLEJNOSC DIVOW JEST WYK. W control.js
				draggableElementCpy.innerHTML += `<input class="input1" maxlength="1" type="" placeholder="axis:" value=""></input>`;
				draggableElementCpy.innerHTML += `<input maxlength="3" type="" placeholder="angle:" value=""></input>`;
				break;

			case 'src_copy-2':
				// UWAGA NIE ZMIENIAC, KOLEJNOSC DIVOW JEST WYK. W control.js
				draggableElementCpy.innerHTML += `<input class="input1" maxlength="1" type="" placeholder="axis 1:" value=""></input>`;
				draggableElementCpy.innerHTML += `<input maxlength="3" type="" placeholder="angle 1:" value=""></input><br><br>`;
				draggableElementCpy.innerHTML += `<input class="input1" maxlength="1" type="" placeholder="axis 2:" value=""></input>`;
				draggableElementCpy.innerHTML += `<input maxlength="3" type="" placeholder="angle 2:" value=""></input>`;
				break;

			case 'src_copy-3':
				break;

			case 'src_copy-4':
				break;

			case 'src_copy-5':
				break;

			case 'src_copy-6':
				draggableElementCpy.innerHTML += `<input maxlength="4" class="input-4 "type="" placeholder="Delay:" value=""></input>`
				break;
		}

		taskControl.appendChild(btnX);
		taskControl.innerHTML += `<span class="material-symbols-outlined">
		swipe_vertical
		</span>`
		draggableElementCpy.appendChild(taskControl);

		// dropzone end effect
		draggableElementCpy.classList.remove('dragging');
		draggableElementCpy.classList.remove('draggingTask');
		dropzone.appendChild(draggableElementCpy);
		index++;
	}

	e.dataTransfer.clearData();
}


// inputOne.forEach((x) => {
// 	x.addEventListener('input', () => {
// 		console.log('test')
// 		if (x.value.length > 1) {
// 			x.value = x.value.slice(0,1); 
// 		}
// 	})
// })
// inputThree.forEach(e => {
// 	e.oninput = function(){
// 		if (e.value.length > 1) {
// 			e.value = e.value.slice(0,1); 
// 		}
// 	}
// })
// inputFour.forEach(e => {
// 	e.addEventListener('input',() => {
// 		if (e.value.length > 4) {
// 			this.value = this.value.slice(0,4); 
// 		}
// 	})
// })


function getDragAfterElement(container, y) {
	const draggableElements = [
		...container.querySelectorAll('.draggableTask:not(.draggingTask)'),
	];
	return draggableElements.reduce(
		(closest, child) => {
			const box = child.getBoundingClientRect();
			const offset = y - box.top - box.height / 2;
			if (offset < 0 && offset > closest.offset) {
				return { offset: offset, element: child };
			} else {
				return closest;
			}
		},
		{ offset: Number.NEGATIVE_INFINITY }
	).element;
}

function getDragAfterElementProgram(container, y) {
	const draggableElements = [
		...container.querySelectorAll('.draggable:not(.dragging)'),
	];
	return draggableElements.reduce(
		(closest, child) => {
			const box = child.getBoundingClientRect();
			const offset = y - box.top - box.height / 2;
			if (offset < 0 && offset > closest.offset) {
				return { offset: offset, element: child };
			} else {
				return closest;
			}
		},
		{ offset: Number.NEGATIVE_INFINITY }
	).element;
}
