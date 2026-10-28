#include <iostream>
#include <fstream>
#include <string>

// Estructura para almacenar información de un jugador
struct Jugador
{
    std::string nombre; // Nombre del jugador
    int puntos;         // Puntos acumulados
};

// Función para ordenar el ranking de jugadores por puntos (de mayor a menor)
void ordenarRanking(Jugador ranking[], int n)
{
    // Implementa el algoritmo de ordenación por burbuja
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (ranking[i].puntos < ranking[j].puntos)
            {
                // Intercambia jugadores si el primero tiene menos puntos
                Jugador temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }
}

// Función principal del programa
int main(int argc, char *argv[])
{
    // Verifica si se proporcionó el nombre del archivo como argumento
    if (argc < 2)
    {
        std::cerr << "Uso: ranking <fichero_puntuaciones>\n";
        return 1; // Termina con error
    }

    // Abre el archivo de puntuaciones
    std::ifstream f(argv[1]);
    if (!f)
    {
        std::cerr << "No puedo abrir " << argv[1] << "\n";
        return 1; // Termina con error si no se puede abrir el archivo
    }

    // Arreglo para almacenar hasta 100 jugadores
    Jugador ranking[100];
    int numJugadores = 0; // Contador de jugadores

    // Lee el archivo línea por línea
    while (f)
    {
        int puntos;
        std::string nombre;
        f >> puntos;             // Lee los puntos
        std::getline(f, nombre); // Lee el resto de la línea como nombre
        // Elimina el espacio inicial del nombre, si existe
        if (!nombre.empty() && nombre[0] == ' ')
            nombre.erase(0, 1);

        // Busca si el jugador ya existe en el ranking
        bool encontrado = false;
        for (int i = 0; i < numJugadores; ++i)
        {
            if (ranking[i].nombre == nombre)
            {
                ranking[i].puntos += puntos; // Suma los puntos al jugador existente
                encontrado = true;
                break;
            }
        }

        // Si el jugador no existe y el nombre no está vacío, lo añade
        if (!encontrado && !nombre.empty())
        {
            ranking[numJugadores].nombre = nombre;
            ranking[numJugadores].puntos = puntos;
            ++numJugadores;
        }
    }

    // Ordena el ranking por puntos
    ordenarRanking(ranking, numJugadores);

    // Muestra el ranking de jugadores
    std::cout << "El ranking de jugadores es este:\n";
    for (int i = 0; i < numJugadores; ++i)
    {
        std::cout << ranking[i].nombre << " – " << ranking[i].puntos << " puntos\n";
    }

    return 0;
}