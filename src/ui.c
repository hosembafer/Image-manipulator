void init_ui()
{
	int i;
	main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	
	// main window
	mainwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(mainwin), "Image Manipulator");
		gtk_window_set_default_size(GTK_WINDOW(mainwin), 850, 600);
		gtk_container_set_border_width (GTK_CONTAINER(mainwin), 10);
		g_signal_connect(mainwin, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	// toolbar
	toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
		gtk_container_add(GTK_CONTAINER(main_box), toolbar);
		
		button_add = gtk_button_new_from_stock(GTK_STOCK_ADD);
		button_start = gtk_button_new_from_stock(GTK_STOCK_CONVERT);
		button_pause = gtk_button_new_with_label("Pause");
			gtk_widget_set_sensitive(button_pause, FALSE);
		button_stop = gtk_button_new_from_stock(GTK_STOCK_STOP);
			gtk_widget_set_sensitive(button_stop, FALSE);
		
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(button_add), FALSE, FALSE, 1);
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(button_start), FALSE, FALSE, 1);
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(button_pause), FALSE, FALSE, 1);
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(button_stop), FALSE, FALSE, 1);
	
	
	// attached file list
	list = gtk_scrolled_window_new(NULL, NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(list), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_container_add(GTK_CONTAINER(main_box), list);
	
	list_in = gtk_tree_view_new();
		gtk_container_add(GTK_CONTAINER(list), list_in);
		gtk_drag_dest_set(GTK_WIDGET(list_in), GTK_DEST_DEFAULT_ALL, NULL, 100, GDK_DRAG_ENTER);
		gtk_drag_dest_add_uri_targets(GTK_WIDGET(list_in));
	
	// progress bar
	progress_bar = gtk_progress_bar_new();
	
	// tabs
	tabs = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(tabs), GTK_POS_TOP);
	
	for(i = 0; i < 2; i++)
	{
		tab_frame = gtk_frame_new("a");
		gtk_container_set_border_width(GTK_CONTAINER(tab_frame), 10);
		
		tab_label = gtk_label_new("q");
		gtk_notebook_append_page(GTK_NOTEBOOK(tabs), tab_frame, tab_label);
	}
	
	gtk_container_add(GTK_CONTAINER(main_box), tabs);
	
	
	gtk_container_add(GTK_CONTAINER(mainwin), main_box);
	gtk_widget_show_all(mainwin);
}