CREATE TABLE `compile_uint_info`(
	file_name	text NOT NULL COMMENT "文件名，clean 绝对路径",
	type	int  NOT NULL COMMENT "类型  0,cpp 文件,1,头文件，",
	uint_file	text NOT NULL  COMMENT "头文件->CPP 文件",
	project text NOT NULL COMMENT "所属项目",
	ycm_project text NOT NULL COMMENT "ycm 项目路径"
);

DROP TABLE `compile_uint_info`;
CREATE TABLE `compile_uint_info`(
	file_name	text NOT NULL  PRIMARY KEY,
	type	int  NOT NULL ,
	uint_file	text NOT NULL  ,
	project text NOT NULL ,
	ycm_project text NOT NULL 
);