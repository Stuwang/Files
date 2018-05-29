#!/usr/bin/python3


class TestClass:
	def __init__(self):
		self.name = "";

def test_class_assign():
	a = TestClass();
	a.name = "wangyuan";
	print(a.name);
	a.type = "error ?";
	print(a.type)

def test_exception():
	try:
		err
	except Exception as e:
		print(e)
	else:
		print('ok')
	finally:
		print("finally");

def write_file():
	file_object = open('testfile.txt', 'w')
	file_object.write("#ifndef __");
	file_object.close( )

def test_range():
	for x in range(1,10):
		print(x," ");

def main():
	# test_class_assign();
	# test_exception();
	# write_file();
	test_range();
	pass

if __name__ == '__main__':
	main()