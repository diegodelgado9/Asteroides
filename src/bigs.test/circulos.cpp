#include "bigs.h"

using namespace BiGS;

// Con Allegro es obligatorio usar este prototipo de main()
// Si se usa el prototipo simplificado, main(), mostrará un error en tiempo de ejecución:
//   symbol not found in flat namespace '__al_mangled_main'
int main(int argc, char *argv[]) {
  const int W = 400, H=400;
  windowOpen(W,H,"BiGS: circulos",true,DRAWMODE_INSTANT);

  // Dibujamos círculos aleatorios
  const int RMAX = 30;
  for (int i=0; i<10000; ++i)
    drawCircle(RMAX+rand()%(W-2*RMAX),RMAX+rand()%(H-2*RMAX),rand()%RMAX,colorRGB(rand()%255,rand()%255,rand()%255),colorRGB(rand()%255,rand()%255,rand()%255));

  // Esperamos a que se pulse una tecla
  eventWaitKeyboard();
  
  return 0;
}