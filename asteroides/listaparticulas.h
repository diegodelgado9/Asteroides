#ifndef LISTAPARTICULAS_H
#define LISTAPARTICULAS_H

#include "particula.h"

class ListaParticulas
{
private:
    Particula *lista;
    int num;

public:
    ListaParticulas();
    ~ListaParticulas();
    ListaParticulas(const ListaParticulas &orig);
    ListaParticulas &operator=(const ListaParticulas &orig);

    int size() const;
    void set(const Particula &p, int pos);
    Particula get(int pos) const;
    void borra(int pos);
    void inserta(const Particula &p, int pos = -1);
};

#endif
