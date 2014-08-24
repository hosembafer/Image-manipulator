#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gtk/gtk.h>

#include "vars.c"

void init();

int main(int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	
	init();
	
	gtk_main();
	
	return 0;
}

void init()
{
	main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
	
	// main window
	mainwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(mainwin), "Image Manipulator");
		gtk_window_set_default_size(GTK_WINDOW(mainwin), 850, 600);
		gtk_container_set_border_width (GTK_CONTAINER(mainwin), 10);
		g_signal_connect(mainwin, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	// toolbar
	toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
		gtk_container_add(GTK_CONTAINER(main_box), toolbar);
		
		button_add = gtk_button_new_with_label("Add");
		gtk_widget_show(button_add);
		
		button_start = gtk_button_new_with_label("Convert");
		gtk_widget_show(button_start);
		
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(button_add), FALSE, FALSE, 1);
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(button_start), FALSE, FALSE, 1);
	gtk_widget_show(toolbar);
	
	
	list = gtk_scrolled_window_new(NULL, NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(list), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_container_add(GTK_CONTAINER(main_box), list);
	gtk_widget_show(list);
	
	list_in = gtk_tree_view_new();
		gtk_container_add(GTK_CONTAINER(list), list_in);
		gtk_drag_dest_set(GTK_WIDGET(list_in),GTK_DEST_DEFAULT_ALL,NULL,100,GDK_DRAG_ENTER);
		gtk_drag_dest_add_uri_targets(GTK_WIDGET(list_in));
	gtk_widget_show(list_in);
	
	
	gtk_container_add(GTK_CONTAINER(mainwin), main_box);
	gtk_widget_show(main_box);
	gtk_widget_show(mainwin);
}