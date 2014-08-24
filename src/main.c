#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gtk/gtk.h>

#include "vars.c"
#include "ui.c"

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	
	init_ui();
	
	//init();
	
	gtk_main();
	
	return 0;
}