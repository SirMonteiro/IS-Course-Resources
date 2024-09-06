cmake_minimum_required(VERSION 3.25)
project(EP1_AED2 C)

set(CMAKE_C_STANDARD 99)

add_executable(grafo_matrizadj ep1_14746450.c
        grafo_matrizadj.c
)

add_executable(grafo_listaadj ep1_14746450.c
        grafo_listaadj.c
)

target_compile_options(grafo_matrizadj PRIVATE -DMATRIZ)
