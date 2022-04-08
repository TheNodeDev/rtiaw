cmake_minimum_required(VERSION 3.21)
project(rtiaw)

set(CMAKE_CXX_STANDARD 20)

add_executable(rtiaw main.cpp vec3.h color.h ray.h hittable.h objects/sphere.h hittable_list.h utils.h camera.h)
