#include "bigs.h"
#include "particula.h"

// Función principal del programa
int main(int argc, char **argv)
{
    // Define las dimensiones de la ventana
    const int height = 200, width = 200;
    // Abre una ventana gráfica con las dimensiones especificadas
    BiGS::windowOpen(width, height, "Dibujar partículas", true);

    // Crea una partícula para la nave con posición, velocidad y aceleración
    Particula nave(Vector2D(100, 100),                       // Posición en el centro (100, 100)
                   Vector2D(50, -45, Vector2D::Uds::Grados), // Velocidad: módulo 50, ángulo -45 grados
                   Vector2D(40, 90, Vector2D::Uds::Grados)); // Aceleración: módulo 40, ángulo 90 grados
    nave.tipo(1);                                            // Establece el tipo como nave (1)
    nave.color(BiGS::CGreen);                                // Asigna color verde
    nave.radio(30);                                          // Asigna un radio de 30
    nave.direccion(30);                                      // Establece la dirección a 30 grados
    nave.dibujar(true);                                      // Dibuja la nave con vectores de velocidad y aceleración

    // Crea la primera partícula para un asteroide
    Particula aster1(Vector2D(40, 50),                          // Posición en (40, 50)
                     Vector2D(70, 45, Vector2D::Uds::Grados),   // Velocidad: módulo 70, ángulo 45 grados
                     Vector2D(10, 135, Vector2D::Uds::Grados)); // Aceleración: módulo 10, ángulo 135 grados
    aster1.tipo(2);                                             // Establece el tipo como asteroide (2)
    aster1.color(BiGS::CCyan);                                  // Asigna color cian
    aster1.radio(20);                                           // Asigna un radio de 20
    aster1.dibujar(true);                                       // Dibuja el asteroide con vectores

    // Crea la segunda partícula para un asteroide
    Particula aster2(Vector2D(150, 50),                          // Posición en (150, 50)
                     Vector2D(40, -30, Vector2D::Uds::Grados),   // Velocidad: módulo 40, ángulo -30 grados
                     Vector2D(20, -110, Vector2D::Uds::Grados)); // Aceleración: módulo 20, ángulo -110 grados
    aster2.tipo(2);                                              // Establece el tipo como asteroide (2)
    aster2.color(BiGS::CCyan);                                   // Asigna color cian
    aster2.radio(10);                                            // Asigna un radio de 10
    aster2.dibujar(true);                                        // Dibuja el asteroide con vectores

    // Crea una partícula para un disparo
    Particula disp(Vector2D(50, 150),                          // Posición en (50, 150)
                   Vector2D(40, -30, Vector2D::Uds::Grados),   // Velocidad: módulo 40, ángulo -30 grados
                   Vector2D(20, -110, Vector2D::Uds::Grados)); // Aceleración: módulo 20, ángulo -110 grados
    disp.tipo(3);                                              // Establece el tipo como disparo (3)
    disp.color(BiGS::CRed);                                    // Asigna color rojo
    disp.radio(3);                                             // Asigna un radio de 3
    disp.dibujar(true);                                        // Dibuja el disparo con vectores

    // Espera a que se presione una tecla para cerrar la ventana
    BiGS::eventWaitKeyboard();
    return 0;
}