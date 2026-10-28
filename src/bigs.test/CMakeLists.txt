cmake_minimum_required(VERSION 3.12)
project(BiGSTest VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

include(../bigs/bigs.cmake)

add_executable(hola hola.cpp)
target_link_libraries(hola bigs)

add_executable(draw draw.cpp)
target_link_libraries(draw bigs)

add_executable(circulos circulos.cpp)
target_link_libraries(circulos bigs)

add_executable(antialiasing antialiasing.cpp)
target_link_libraries(antialiasing bigs)

add_executable(eventos eventos.cpp)
target_link_libraries(eventos bigs)

add_executable(teclado1 teclado1.cpp)
target_link_libraries(teclado1 bigs)

add_executable(teclado2 teclado2.cpp)
target_link_libraries(teclado2 bigs)
