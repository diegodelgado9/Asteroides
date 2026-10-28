#include <iostream>
#include "listaparticulas.h"
using namespace std;

// Función para mostrar la lista de partículas
void mostrar(ListaParticulas l)
{
    ListaParticulas tmp;
    tmp = l; // Crea una copia de la lista para evitar modificar la original
    // Itera sobre cada partícula en la lista
    for (int i = 0; i < tmp.size(); ++i)
    {
        // Imprime la representación en cadena de cada partícula
        cout << tmp.get(i).to_string() << endl;
    }
}

// Función principal del programa
int main()
{
    ListaParticulas l; // Crea una lista vacía de partículas
    Particula p;       // Crea una partícula para usar en las operaciones

    // Inserta 10 partículas iniciales con propiedades específicas
    for (int i = 0; i < 10; i++)
    {
        p.radio(10 + i);           // Asigna un radio creciente (10, 11, ..., 19)
        p.densidad(1);             // Asigna densidad constante de 1
        p.posicion(i, i * 2);      // Asigna posición (x, y) = (i, 2*i)
        p.velocidad(i + 1, i + 3); // Asigna velocidad con módulo i+1 y ángulo i+3 grados
        l.inserta(p);              // Inserta la partícula al final de la lista
    }

    // Borra las partículas en las posiciones 3 y 7
    l.borra(3);
    l.borra(7); // Nota: La posición 7 después de borrar la 3 es relativa a la lista actualizada
    cout << "Borrados el 3 y el 7:" << endl;
    mostrar(l); // Muestra la lista después de los borrados

    // Inserta una partícula con radio 100 en la posición 0
    p.radio(100);    // Modifica el radio de la partícula
    l.inserta(p, 0); // Inserta al inicio de la lista
    cout << "Insertado en 0: " << endl;
    mostrar(l); // Muestra la lista después de la inserción

    // Inserta una partícula con radio 200 en la posición 5
    p.radio(200);    // Modifica el radio de la partícula
    l.inserta(p, 5); // Inserta en la posición 5
    cout << "Insertado en 5: " << endl;
    mostrar(l); // Muestra la lista después de la inserción

    // Borra la última partícula de la lista
    l.borra(l.size() - 1); // Elimina el elemento en la última posición
    cout << "Borrado el último: " << endl;
    mostrar(l); // Muestra la lista después del borrado

    return 0;
}