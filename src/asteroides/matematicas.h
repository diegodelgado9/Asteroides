#ifndef MATEMATICAS_H
#define MATEMATICAS_H

#include "particula.h"
const double PI = 3.141592653589793;

bool cad2num(const char *c, double &n);
double aleatorio(double min, double max); // <<< AÑADIDO
void corrige_velocidad(Particula &a1, Particula &a2);

#endif // MATEMATICAS_H
