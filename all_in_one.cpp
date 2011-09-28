#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include "co_ordinate_transformation.h"
#include "check_gui.h"



int main( int argc, char *argv[])

{
 char *pFilename = argv[1];
 co_ordinate_transformation c1;

c1.co_ordinate(pFilename);
c1.drawing_points();
check_gui ck;
gtk_init(&argc, &argv);
ck.calling_epidemic_gui();
gtk_main();
return 0;
}









