#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include "co_ordinate_transformation.h"
#include "check_gui.h"
#include "final_gui.h"
#include "degree_compute.h"

#include "simulation.h"




int main( int argc, char *argv[])

{
 char *pFilename = argv[1];

 co_ordinate_transformation c1;
 c1.co_ordinate(pFilename);
 c1.drawing_points();
 degree_compute deg;
 
 

final_gui fgui;
gtk_init(&argc, &argv);
fgui.file_read();
fgui.calling_epidemic_gui();

deg.total_degree();


gtk_main();
return 0;
}








