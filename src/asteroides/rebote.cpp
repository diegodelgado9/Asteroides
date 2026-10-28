#include "particula.h"
#include "matematicas.h"
#include "bigs.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Define las dimensiones de la ventana
const int WIDTH = 200;
const int HEIGHT = 200;

// Función principal del programa
int main(int argc, char **argv)
{
    // Inicializa la semilla para números aleatorios
    srand(time(nullptr));

    // Abre una ventana gráfica con modo DRAWMODE_DELAYED
    BiGS::windowOpen(WIDTH, HEIGHT, "Partícula rebotando", true, DRAWMODE_DELAYED);

    // Crea 10 partículas con propiedades aleatorias
    for (int i = 0; i < 10; i++)
    {
        // Genera posición aleatoria dentro de los límites, evitando los bordes
        Vector2D pos(aleatorio(30, WIDTH - 30), aleatorio(30, HEIGHT - 30));
        // Genera velocidad aleatoria en módulo y dirección
        Vector2D vel(aleatorio(10, 40), aleatorio(0, 360), Vector2D::Uds::Grados);
        // Genera aceleración aleatoria en módulo y dirección
        Vector2D acel(aleatorio(0, 20), aleatorio(0, 360), Vector2D::Uds::Grados);

        // Crea una partícula con la posición, velocidad y aceleración generadas
        Particula p(pos, vel, acel);
        // Asigna un radio aleatorio entre 10 y 30
        p.radio(aleatorio(10, 30));

        // Asigna un color fijo (rojo) a la partícula
        BiGS::Color color = BiGS::CRed;
        p.color(color);

        // Establece el tipo de partícula como 2 (representada como flecha)
        p.tipo(2);

        // Bucle de animación para la partícula
        while (!BiGS::closeRequested())
        {
            // Obtiene el tiempo transcurrido desde la última actualización
            double dt = BiGS::timeFromLastCall();

            // Obtiene la posición y velocidad actuales de la partícula
            Vector2D posicion = p.posicion();
            Vector2D velocidad = p.velocidad();

            // Variables para indicar si la partícula debe rebotar en cada eje
            bool rebote_x = false, rebote_y = false;

            // Verifica si la partícula choca con los bordes horizontales
            if (posicion.getX() - p.radio() < 0 || posicion.getX() + p.radio() >= WIDTH)
                rebote_x = true;
            // Verifica si la partícula choca con los bordes verticales
            if (posicion.getY() - p.radio() < 0 || posicion.getY() + p.radio() >= HEIGHT)
                rebote_y = true;

            // Maneja el rebote en el eje X
            if (rebote_x)
            {
                // Invierte la componente X de la velocidad
                velocidad.setX(-velocidad.getX());
                p.velocidad(velocidad);
                // Corrige la posición para evitar que la partícula quede fuera de los límites
                if (posicion.getX() - p.radio() < 0)
                    p.posicion(p.radio(), posicion.getY());
                if (posicion.getX() + p.radio() >= WIDTH)
                    p.posicion(WIDTH - p.radio(), posicion.getY());
            }

            // Maneja el rebote en el eje Y
            if (rebote_y)
            {
                // Invierte la componente Y de la velocidad
                velocidad.setY(-velocidad.getY());
                p.velocidad(velocidad);
                // Corrige la posición para evitar que la partícula quede fuera de los límites
                if (posicion.getY() - p.radio() < 0)
                    p.posicion(posicion.getX(), p.radio());
                if (posicion.getY() + p.radio() >= HEIGHT)
                    p.posicion(posicion.getX(), HEIGHT - p.radio());
            }

            // Actualiza la posición y velocidad de la partícula usando MUA
            p.avanzaMUA(dt);

            // Limpia la pantalla con fondo negro
            BiGS::clear(BiGS::CBlack);

            // Dibuja la partícula, incluyendo vectores de velocidad y aceleración
            p.dibujar(true);

            // Actualiza la pantalla para mostrar los cambios
            BiGS::refresh();

            // Introduce un retraso para controlar la velocidad de la animación
            BiGS::timeDelay(5);
        }
    }

    return 0;
}