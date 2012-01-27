#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include "co_ordinate_transformation.h"
#include "check_gui.h"
#include "final_gui.h"
#include "degree_compute.h"
#include "stochastic_matrix.h"
#include "markov_simulation.h"




int main( int argc, char *argv[])

{
 char *pFilename = argv[1];

 co_ordinate_transformation c1;
 c1.co_ordinate(pFilename);
 c1.drawing_points();
 degree_compute deg;
 stochastic_matrix stochastic;
 markov_simulation ms;
 
 gtk_init(&argc, &argv);
 final_gui fgui;
 fgui.calling_epidemic_gui();


fgui.file_read();


deg.total_degree();
stochastic.calculate_stochastic_matrix();
ms.simulation_caller();

gtk_main();
return 0;
}







