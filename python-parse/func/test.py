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

def main():
	# test_class_assign();
	test_exception();
	pass

if __name__ == '__main__':
	main()