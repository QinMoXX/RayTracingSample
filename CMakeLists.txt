cmake_minimum_required(VERSION 2.8)	  		# CMake最低版本要求，低于2.6的构建过程会被终止
project( RayTracingSample )					  	# 定义工程名称
include_directories( ${PROJECT_SOURCE_DIR}/include)
add_executable( RayTracingSample src/main.cpp ) 		# 生成一个叫 Hello的可执行文件，其中可执行源文件路径为 src/main.cpp
