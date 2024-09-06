cmake_minimum_required(VERSION 3.25)
project(AED2 C)

set(CMAKE_C_STANDARD 99)

add_executable(grafoMatrizadj main.c
        grafoMatrizadj.c
)

add_executable(grafoListaadj main.c
        grafoListaadj.c
)

target_compile_options(grafoMatrizadj PRIVATE -DMATRIZ)
