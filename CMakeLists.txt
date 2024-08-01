cmake_minimum_required(VERSION 3.22)   #指定camke最低版本
project(RayTracingSample)   #指定项目名称
 
set(CMAKE_C_COMPILER gcc)   #设置编译器
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)  #设置c++版本
 
 
include_directories( ${PROJECT_SOURCE_DIR}/include)
 
add_executable( RayTracingSample src/main.cpp ) 
 
