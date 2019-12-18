cmake_minimum_required(VERSION 3.15)
project(nf05_project C)

# Use C11 standard
set(CMAKE_C_STANDARD 11)

file(GLOB nf05_project_sources "src/*.c")

add_executable(nf05_project ${nf05_project_sources})