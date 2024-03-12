// WRITE HERE all the Project's logic / Flow.
// **** Libraries to include here ...
#include <color.h>
#include <InfraRed.h>

// **** Project code definition here ...

// **** Project code functions here ...
void project_setup() {
   // Start LED Strip color control
      color_setup();

   // Start IR device
      IR_setup();
}

void project_loop() {
  // Ambient handing
      //if (TIMER >0) if ((millis() - 3500) % (TIMER * 60000) < 5) ambient_data();      // TIMER bigger than zero on div or dog bites!!
  
  //  LED Strip color handling
      color_loop();

  //  IR handling
      IR_loop();

  // (conceptual) Switch Handling 
}
