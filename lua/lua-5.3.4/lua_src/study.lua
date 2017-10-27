function name_func(arg)
	print(arg.name);
end

function print_name( name )
	print(name);
end

function return_2(  )
	return 1,2
end

function new_counter()
	local i = 0;
	return function ( )
		i = i + 1;
		return i;
	end 
end

function test_counter()
	counter = new_counter();
	print("this is a test of counter, return function :")
	print(counter());
	print(counter());
	print(counter());
	print(counter());
	print(counter());
	print(counter());
end

-- this is main function
function main()
	print_name("wangyuan")
	name_func{name = "wangyuan"};	

	a,b,c = return_2();
	print(a," ",b," ",c)

	c = return_2();
	print(c);

	test_counter();
end

main();