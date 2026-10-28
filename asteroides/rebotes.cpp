#include "bigs.h"
#include "matematicas.h"
#include "particula.h"
#include "listaparticulas.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Función principal del programa
int main(int argc, char **argv)
{
    // Verifica si se proporcionaron los argumentos correctos
    if (argc != 10)
    {
        std::cout << "Uso: " << argv[0] << " ancho alto N Rmin Rmax Vmin Vmax Amin Amax\n";
        return 1; // Termina con error si faltan argumentos
    }

    // Convierte los argumentos de entrada a valores numéricos
    const int ANCHO = atoi(argv[1]);   // Ancho de la ventana
    const int ALTO = atoi(argv[2]);    // Alto de la ventana
    const int N = 23;                  // Número fijo de partículas (ajustado a 23)
    const double RMIN = atof(argv[4]); // Radio mínimo de las partículas
    const double RMAX = atof(argv[5]); // Radio máximo de las partículas
    const double VMIN = atof(argv[6]); // Velocidad mínima de las partículas
    const double VMAX = atof(argv[7]); // Velocidad máxima de las partículas
    const double AMIN = atof(argv[8]); // Aceleración mínima de las partículas
    const double AMAX = atof(argv[9]); // Aceleración máxima de las partículas

    // Inicializa la semilla para números aleatorios
    srand(time(nullptr));
    // Abre una ventana gráfica con modo DRAWMODE_DELAYED
    BiGS::windowOpen(ANCHO, ALTO, "Rebotes de partículas", true, DRAWMODE_DELAYED);

    // Crea una lista para almacenar las partículas
    ListaParticulas lista;

    // Genera N partículas con propiedades aleatorias
    for (int i = 0; i < N; ++i)
    {
        double radio = aleatorio(RMIN, RMAX); // Radio aleatorio
        double densidad = aleatorio(1, 10);   // Densidad aleatoria entre 1 y 10
        // Posición aleatoria, asegurando que la partícula esté dentro de los límites
        double px = aleatorio(radio, ANCHO - radio);
        double py = aleatorio(radio, ALTO - radio);
        double vmod = aleatorio(VMIN, VMAX); // Módulo de velocidad aleatorio
        double vang = aleatorio(0, 359);     // Ángulo de velocidad aleatorio
        double amod = aleatorio(AMIN, AMAX); // Módulo de aceleración aleatorio
        double aang = aleatorio(0, 359);     // Ángulo de aceleración aleatorio

        // Crea una partícula con posición, velocidad y aceleración
        Particula p(Vector2D(px, py),
                    Vector2D(vmod, vang, Vector2D::Uds::Grados),
                    Vector2D(amod, aang, Vector2D::Uds::Grados));
        p.radio(radio);       // Asigna el radio
        p.densidad(densidad); // Asigna la densidad

        // Asigna un color aleatorio en formato RGB
        BiGS::Color color = BiGS::colorRGB(rand() % 256, rand() % 256, rand() % 256);
        p.color(color);

        // Inserta la partícula en la lista
        lista.inserta(p);
    }

    // Bucle principal de animación
    while (!BiGS::closeRequested())
    {
        // Obtiene el tiempo transcurrido desde la última actualización
        double dt = BiGS::timeFromLastCall();

        // Verifica colisiones con los bordes de la ventana
        for (int i = 0; i < lista.size(); ++i)
        {
            Particula p = lista.get(i);
            Vector2D pos = p.posicion();  // Posición actual
            Vector2D vel = p.velocidad(); // Velocidad actual
            double r = p.radio();         // Radio de la partícula

            bool colisionX = false, colisionY = false;

            // Verifica colisión con los bordes horizontales
            if (pos.getX() - r < 0)
            {
                pos.setX(r);           // Corrige la posición
                vel.setX(-vel.getX()); // Invierte la velocidad en X
                colisionX = true;
            }
            if (pos.getX() + r >= ANCHO)
            {
                pos.setX(ANCHO - r);   // Corrige la posición
                vel.setX(-vel.getX()); // Invierte la velocidad en X
                colisionX = true;
            }
            // Verifica colisión con los bordes verticales
            if (pos.getY() - r < 0)
            {
                pos.setY(r);           // Corrige la posición
                vel.setY(-vel.getY()); // Invierte la velocidad en Y
                colisionY = true;
            }
            if (pos.getY() + r >= ALTO)
            {
                pos.setY(ALTO - r);    // Corrige la posición
                vel.setY(-vel.getY()); // Invierte la velocidad en Y
                colisionY = true;
            }

            // Actualiza la partícula si hubo colisión
            if (colisionX || colisionY)
            {
                p.posicion(pos.getX(), pos.getY());
                p.velocidad(vel);
                lista.set(p, i);
            }
        }

        // Verifica colisiones entre partículas
        for (int i = 0; i < lista.size(); ++i)
        {
            for (int j = i + 1; j < lista.size(); ++j)
            {
                Particula pi = lista.get(i);
                Particula pj = lista.get(j);
                // Calcula la distancia entre las partículas
                double dist = (pi.posicion() - pj.posicion()).mod();
                // Si la distancia es menor o igual a la suma de los radios, hay colisión
                if (dist <= pi.radio() + pj.radio())
                {
                    corrige_velocidad(pi, pj); // Corrige las velocidades por colisión elástica
                    lista.set(pi, i);          // Actualiza la primera partícula
                    lista.set(pj, j);          // Actualiza la segunda partícula
                }
            }
        }

        // Actualiza las posiciones de todas las partículas usando MUA
        for (int i = 0; i < lista.size(); ++i)
        {
            Particula p = lista.get(i);
            p.avanzaMUA(dt); // Avanza con movimiento uniformemente acelerado
            lista.set(p, i); // Actualiza la partícula en la lista
        }

        // Limpia la pantalla con un fondo azul claro
        BiGS::clear(BiGS::colorRGB(173, 216, 230));

        // Dibuja todas las partículas, incluyendo vectores de velocidad y aceleración
        for (int i = 0; i < lista.size(); ++i)
            lista.get(i).dibujar(true);

        // Actualiza la pantalla para mostrar los cambios
        BiGS::refresh();

        // Introduce un retraso para mantener aproximadamente 60 FPS
        BiGS::timeDelay(16);
    }

    return 0;
}