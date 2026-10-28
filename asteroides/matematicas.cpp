#include "matematicas.h"
#include "particula.h"
#include <cstdlib>
#include <ctime>

// Convierte una cadena de caracteres a un número double
bool cad2num(const char *c, double &n)
{
    n = 0.0;               // Inicializa el resultado en 0
    double factor = 1.0;   // Factor para manejar números negativos
    bool decimal = false;  // Indica si se ha encontrado un punto decimal
    double divisor = 10.0; // Divisor para procesar la parte decimal

    // Verifica si la cadena está vacía
    if (*c == '\0')
        return false;

    // Maneja el signo del número
    if (*c == '-')
    {
        factor = -1.0; // Establece el número como negativo
        c++;
    }
    else if (*c == '+')
    {
        c++; // Salta el signo positivo
    }

    // Recorre cada carácter de la cadena
    while (*c != '\0')
    {
        if (*c >= '0' && *c <= '9') // Si el carácter es un dígito
        {
            if (!decimal)
            {
                n = n * 10.0 + (*c - '0'); // Construye la parte entera
            }
            else
            {
                n = n + (*c - '0') / divisor; // Construye la parte decimal
                divisor *= 10.0;              // Incrementa el divisor para el próximo dígito decimal
            }
        }
        else if (*c == '.' && !decimal) // Si es un punto decimal (y no se ha encontrado antes)
        {
            decimal = true; // Activa el modo decimal
        }
        else // Si el carácter no es válido
        {
            return false; // Devuelve error
        }
        c++;
    }

    // Aplica el signo al resultado
    n *= factor;

    return true; // Conversión exitosa
}

// Genera un número aleatorio en el rango [min, max]
double aleatorio(double min, double max)
{
    return min + (max - min) * (rand() / (double)RAND_MAX); // Escala el valor aleatorio al rango deseado
}

// Corrige las velocidades de dos partículas tras una colisión elástica
void corrige_velocidad(Particula &a1, Particula &a2)
{
    Vector2D v1 = a1.velocidad(); // Velocidad de la primera partícula
    Vector2D v2 = a2.velocidad(); // Velocidad de la segunda partícula
    // Verifica si las partículas se están acercando
    if ((v1.getX() - v2.getX()) * (a2.posicion().getX() - a1.posicion().getX()) +
            (v1.getY() - v2.getY()) * (a2.posicion().getY() - a1.posicion().getY()) >=
        0)
    {
        double sum = a1.masa() + a2.masa();              // Suma de las masas
        Vector2D difp12 = a1.posicion() - a2.posicion(); // Vector de posición relativa (1 a 2)
        Vector2D difp21 = a2.posicion() - a1.posicion(); // Vector de posición relativa (2 a 1)
        double dot1 = difp12 * (v1 - v2);                // Producto escalar para la primera partícula
        double dot2 = (v2 - v1) * difp21;                // Producto escalar para la segunda partícula
        double norma1 = difp12.mod();
        norma1 *= norma1; // Norma al cuadrado del vector de posición 1
        double norma2 = difp21.mod();
        norma2 *= norma2; // Norma al cuadrado del vector de posición 2
        // Calcula las nuevas velocidades usando la fórmula de colisión elástica
        Vector2D nueva_v1 = v1 - (2 * a2.masa() / sum) * dot1 * (1.0 / norma1) * difp12;
        Vector2D nueva_v2 = v2 - (2 * a1.masa() / sum) * dot2 * (1.0 / norma2) * difp21;
        a1.velocidad(nueva_v1); // Actualiza la velocidad de la primera partícula
        a2.velocidad(nueva_v2); // Actualiza la velocidad de la segunda partícula
    }
}