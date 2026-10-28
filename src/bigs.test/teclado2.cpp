#include <iostream>
#include "bigs.h"

using namespace std;

// Con Allegro es obligatorio usar este prototipo de main()
// Si se usa el prototipo simplificado, main(), mostrará un error en tiempo de ejecución:
//   symbol not found in flat namespace '__al_mangled_main'
int main(int argc, char *argv[]) {
  BiGS::windowOpen(500,400,"BiGS: Teclado 2");
  BiGS::txtDraw("Mira el resultado en la consola",10,10,BiGS::CGreen);

  // Bucle típico: mientras no se pulse cerrar ventana
  while (!BiGS::closeRequested()) {
    BiGS::Event e;
    if (BiGS::eventNext(e) && 
        e.type==BiGS::KEY_CHAR && 
        e.keyboard.keycode == ALLEGRO_KEY_A)
          cout << "  ... se ha generado un evento de pulsación de la tecla A" << endl;
    if (BiGS::isKeyPressed(ALLEGRO_KEY_A))
      cout << "Atención: la tecla A está pulsada" << endl;
    BiGS::timeDelay(5);
  }

  return 0;
}