cmake_minimum_required(VERSION 3.15)
project(nf05_project C)

# Use C11 standard
set(CMAKE_C_STANDARD 11)

# Cross compile for Windows on Linux, using x86_64-w64-mingw32-gcc compiler
#set(CMAKE_SYSTEM_NAME Windows)
#set(GNU_HOST x86_64-w64-mingw32)
#set(CMAKE_C_COMPILER ${GNU_HOST}-gcc)
#set(CMAKE_RC_COMPILER ${GNU_HOST}-windres)

# Add all .c files in src folder
file(GLOB nf05_project_sources "src/*.c")

add_executable(nf05_project ${nf05_project_sources})