#include <iostream>
#include "vector2d.h"
using namespace std;

// Función para manejar errores de entrada
void error()
{
    // Muestra un mensaje de error y termina el programa
    cout << "Error en la lectura de datos. Los vectores se escriben con el formato (x,y)" << endl;
    exit(1);
}

// Función principal del programa
int main()
{
    Vector2D v1, v2; // Declara dos vectores 2D

    // Solicita al usuario el primer vector
    cout << "Dime un primer vector v1: ";
    cin >> v1;   // Lee el vector en formato (x,y)
    if (!cin)    // Verifica si la entrada es válida
        error(); // Llama a la función de error si falla

    // Solicita al usuario el segundo vector
    cout << "Dime un segundo vector v2: ";
    cin >> v2;   // Lee el vector en formato (x,y)
    if (!cin)    // Verifica si la entrada es válida
        error(); // Llama a la función de error si falla

    // Muestra los vectores ingresados
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;

    // Calcula y muestra la suma de los vectores
    Vector2D v3;
    v3 = v1 + v2;
    cout << "v1 + v2 = " << v3 << endl;

    // Calcula y muestra el producto del vector v1 por un escalar (4)
    v3 = v1 * 4;
    cout << "v1 * 4 = " << v3 << endl;

    // Calcula y muestra el producto de un escalar (4) por el vector v1
    v3 = 4 * v1;
    cout << "4 * v1 = " << v3 << endl;

    // Calcula y muestra la resta de los vectores
    v3 = v1 - v2;
    cout << "v1 - v2 = " << v3 << endl;

    // Calcula y muestra el producto escalar de los vectores
    double producto = v1 * v2;
    cout << "v1 * v2 (producto escalar) = " << producto << endl;

    // Calcula y muestra la división del vector v1 por un escalar (4)
    v3 = v1 / 4;
    cout << "v1 / 4 = " << v3 << endl;

    // Calcula y muestra el módulo (magnitud) del vector v1
    cout << "|v1| = " << v1.mod() << endl;

    return 0;
}