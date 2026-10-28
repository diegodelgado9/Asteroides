#include "bigs.h"

using namespace BiGS;

// Con Allegro es obligatorio usar este prototipo de main()
// Si se usa el prototipo simplificado, main(), mostrará un error en tiempo de ejecución:
//   symbol not found in flat namespace '__al_mangled_main'
int main(int argc, char *argv[]) {
  windowOpen(200,200,"BiGS: antialiasing",true);

  // Dibujamos líneas rectas (tonos violeta)
  for (int i=0; i<6; ++i)
    drawLine(10,40+i*25,100,160-i*25,CWhite,3);

  // Esperamos a que se pulse una tecla
  eventWaitKeyboard();

  return 0;
}