# this

CHECK_K_INTVALUE = 1;


class CoreBaseObject:
	def get_last_build_time(self):
		pass

	def depends(self):
		pass

	def build(self):
		pass


class PlainObject(CoreBaseObject):

	def get_last_build_time(self):
		pass

	def depends(self):
		pass

	def get_build_target(self):
		pass
	pass

class DynamicLibrary(CoreBaseObject):
	def add_sources_file(self,files):
		pass

	def add_static_library(self,librarys):
		pass

	def add_dynamic_library(self,librarys):
		pass

	def add_definitions(self,defs):
		pass

	def add_include_path(self,include_paths):
		pass

	def get_last_build_time(self):
		pass
	pass

class StaticLibrary(CoreBaseObject):
	def add_sources_file(self,files):
		pass

	def add_static_library(self,librarys):
		pass

	def add_dynamic_library(self,librarys):
		pass

	def add_definitions(self,defs):
		pass

	def add_include_path(self,include_paths):
		pass

	def get_last_build_time(self):
		pass
	pass

class Program(CoreBaseObject):

	def __init__(self,name = ""):
		self.name = "";
		self.target_name = self.name;
		self.depends = [];

	def add_sources_file(self,files):
		pass

	def add_static_library(self,librarys):
		pass

	def add_dynamic_library(self,librarys):
		pass

	def add_definitions(self,defs):
		pass

	def add_include_path(self,include_paths):
		pass

	def get_last_build_time(self):
		pass

	def depends(self):
		pass

	def build(self):

		pass

	def output(self):
		pass

	pass


class CompileUnit(CoreBaseObject):

	def add_definitions(self,defs):
		pass

	def del_definitions(self,defs):
		pass

	def add_include_path(self,include_paths):
		pass
	pass

class HeadUnit(CoreBaseObject):
	def get_last_build_time(self):
		pass
	def depends(self):
		pass
	def build(self):
		pass


print("this s string print from package Check")

