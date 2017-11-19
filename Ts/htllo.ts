class Shape {

	area: number;
	color: string;
	name: string;
	width: number
	height: number

	constructor(name: string, width: number, height: number) {
		this.area = width * height;
		this.color = "pink";
		this.name = name;
		this.width = width;
		this.height = height;
	};

	shoutout() {
		return "I'm " + this.color + " " + this.name + " with an area of " + this.area + " cm squared.";
	}
}


function test1() {
	var square = new Shape("square", 30, 30);

	console.log(square.shoutout());
	console.log('Area of Shape: ' + square.area);
	console.log('Name of Shape: ' + square.name);
	console.log('Color of Shape: ' + square.color);
	console.log('Width of Shape: ' + square.width);
	console.log('Height of Shape: ' + square.height);
}

function test2() {
	const a = 11;
	console.log(a);
}


// /////////////////////////////////////

interface Callable {
	func2(): void;
}

class Action implements Callable {

	num: number;

	func2(): void {
		console.log(this.num);
	}

	constructor(a: number) {
		this.num = a;
	}
};

function test() {
	let a = new Action(1);
	a.func2();
}

// /////////////////////////////////////

// function interface

interface Func {
	(): void;
};

function test_func() {
	let f: Func = function(): void {
		console.log("this is a function interface");
	}

	f();

	let num = "string".trim().indexOf('t');
	console.log(num);
}


//

// use my own interface

class MyOwnInterface {

	constructor() {

	};

	static GetTime() {
		return '' + new Date();
	}
}

function test_own_interface() {
	let date = MyOwnInterface.GetTime();
	console.log(date);
	[1, 2, 3].forEach(function(value: number, index: number, arr: number[]) {
		console.log("" + index + " 	" + value)
	});

	[1, 2, 3, 4].forEach(function(value, index, arr) {
		console.log("hahahhaha " + value);
	});


	["string", "array", "object", "number"].forEach(function(value) {
		console.log(value);
	});
}


function VertyGood() {
	console.log("this is very good ! year, i love it !!!!!");
}


//

function main() {
	// test_own_interface();
	VertyGood();
}

main();
