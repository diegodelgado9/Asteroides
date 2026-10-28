#include "listaparticulas.h"
#include "particula.h"
#include <iostream> // Para mensajes de error

// Constructor por defecto: inicializa la lista como vacía
ListaParticulas::ListaParticulas()
{
    lista = nullptr;
    num = 0;
}

// Destructor: libera la memoria de la lista
ListaParticulas::~ListaParticulas()
{
    if (lista != nullptr)
        delete[] lista;
}

// Constructor de copia: crea una copia de otra lista de partículas
ListaParticulas::ListaParticulas(const ListaParticulas &orig)
{
    num = orig.num;
    lista = new Particula[num];
    for (int i = 0; i < num; ++i)
        lista[i] = orig.lista[i]; // Copia cada partícula
}

// Operador de asignación: asigna el contenido de otra lista
ListaParticulas &ListaParticulas::operator=(const ListaParticulas &orig)
{
    if (this != &orig)
    { // Evita la autoasignación
        if (lista != nullptr)
            delete[] lista; // Libera la memoria actual

        num = orig.num;
        lista = new Particula[num];
        for (int i = 0; i < num; ++i)
            lista[i] = orig.lista[i]; // Copia cada partícula
    }
    return *this;
}

// Devuelve el número de partículas en la lista
int ListaParticulas::size() const
{
    return num;
}

// Establece una partícula en una posición específica
void ListaParticulas::set(const Particula &p, int pos)
{
    if (pos >= 0 && pos < num)
        lista[pos] = p; // Actualiza la partícula en la posición dada
    else
        std::cout << "Error: posición inválida en set().\n"; // Mensaje de error si la posición no es válida
}

// Obtiene una partícula en una posición específica
Particula ListaParticulas::get(int pos) const
{
    if (pos >= 0 && pos < num)
        return lista[pos]; // Devuelve la partícula en la posición dada
    else
    {
        std::cout << "Error: posición inválida en get().\n"; // Mensaje de error si la posición no es válida
        return Particula();                                  // Devuelve una partícula vacía si hay error
    }
}

// Elimina una partícula en una posición específica
void ListaParticulas::borra(int pos)
{
    if (pos < 0 || pos >= num)
    {
        std::cout << "Error: posición inválida en borra().\n"; // Mensaje de error si la posición no es válida
        return;
    }

    // Crea una nueva lista con un elemento menos
    Particula *nueva = new Particula[num - 1];
    for (int i = 0, j = 0; i < num; ++i)
    {
        if (i != pos)
            nueva[j++] = lista[i]; // Copia todas las partículas excepto la que se elimina
    }

    delete[] lista; // Libera la memoria de la lista anterior
    lista = nueva;
    num--; // Reduce el contador de partículas
}

// Inserta una partícula en una posición específica (o al final si pos == -1)
void ListaParticulas::inserta(const Particula &p, int pos)
{
    if (pos < -1 || pos > num)
    {
        std::cout << "Error: posición inválida en inserta().\n"; // Mensaje de error si la posición no es válida
        return;
    }

    // Crea una nueva lista con un elemento más
    Particula *nueva = new Particula[num + 1];
    for (int i = 0, j = 0; i <= num; ++i)
    {
        if (i == pos || (pos == -1 && i == num))
            nueva[i] = p; // Inserta la nueva partícula
        else
            nueva[i] = lista[j++]; // Copia las partículas existentes
    }

    delete[] lista; // Libera la memoria de la lista anterior
    lista = nueva;
    num++; // Incrementa el contador de partículas
}