cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(asteroides)

# Incluir configuración de BiGS
include(../bigs/bigs.cmake)

set(CPACK_SOURCE_GENERATOR ZIP)
include(CPack)

add_library(particulas particula.cpp vector2d.cpp matematicas.cpp listaparticulas.cpp)
target_link_libraries(particulas bigs)

# Ejecutables y sus dependencias
add_executable(testparticula testparticula.cpp)
target_link_libraries(testparticula bigs particulas)

add_executable(rebote rebote.cpp)
target_link_libraries(rebote bigs particulas)

add_executable(testsobrecarga testsobrecarga.cpp)
target_link_libraries(testsobrecarga particulas)

add_executable(testlista testlista.cpp)
target_link_libraries(testlista particulas)

add_executable(rebotes rebotes.cpp)
target_link_libraries(rebotes bigs particulas)

add_executable(asteroides asteroides.cpp)
target_link_libraries(asteroides bigs particulas)

add_executable(ranking ranking.cpp)
target_link_libraries(ranking particulas)

# Copiar la carpeta 'datos' al directorio de compilación
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR}/)