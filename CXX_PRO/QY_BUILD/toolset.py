#

class GunCppCompiler:
    def __init__(self):
        self.command = "";
        self.flags = [];
        self.inputs = [];
        self.output = "";

    def add_input(self,list):
        self.inputs.extend(list);

    # option flag
    def set_compiler(self,cpl_name):
        self.command = cpl_name;

    def set_debug(self):
        self.add_option("-g")

    def unset_debug(self):
        self.remove_option("-g")

    def add_define(self,define):
        self.add_option("-D " + define);

    def remove_define(self,define):
        pass;

    def add_option(self,option):
        self.flags.append(option);

    def remove_option(self,option):
        self.flags.remove(option);


