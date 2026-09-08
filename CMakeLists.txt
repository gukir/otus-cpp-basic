cmake_minimum_required(VERSION 3.5)

project(08.Classes)

add_executable(lec_08_01_struct lec_08_01_struct.cpp)
set_target_properties(lec_08_01_struct PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(lec_08_02_struct_stream lec_08_02_struct_stream.cpp)
set_target_properties(lec_08_02_struct_stream PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(lec_08_03_struct_operators lec_08_03_struct_operators.cpp)
set_target_properties(lec_08_03_struct_operators PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(lec_08_04_struct_nested lec_08_04_struct_nested.cpp)
set_target_properties(lec_08_04_struct_nested PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(lec_08_05_struct_inheritance lec_08_05_struct_inheritance.cpp)
set_target_properties(lec_08_05_struct_inheritance PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(lec_08_06_class lec_08_06_class.cpp)
set_target_properties(lec_08_06_class PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

