void init_ui()
{
	int i;
	main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	
	// main window
	mainwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(mainwin), C_TITLE);
		gtk_window_set_default_size(GTK_WINDOW(mainwin), 850, 600);
		gtk_container_set_border_width (GTK_CONTAINER(mainwin), 10);
		g_signal_connect(mainwin, "destroy", G_CALLBACK(legal_quit), NULL);
	
	// toolbar
	toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
		gtk_container_add(GTK_CONTAINER(main_box), toolbar);
		
		button_add = gtk_button_new_with_label("ADD");
			g_signal_connect(button_add, "clicked", G_CALLBACK(add_files), NULL);
		
		button_convert = gtk_button_new_with_label("CONVERT");
			g_signal_connect(GTK_WIDGET(button_convert), "clicked", G_CALLBACK(get_convert), NULL);
			gtk_widget_set_sensitive(button_convert, FALSE);
		
		button_stop = gtk_button_new_with_label("STOP");
			gtk_widget_set_sensitive(button_stop, FALSE);
			g_signal_connect(GTK_WIDGET(button_stop), "clicked",G_CALLBACK(get_stop), NULL);
		
		GtkWidget *empty_space = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
		
		output_dir_path = gtk_entry_new();
			gtk_entry_set_text(GTK_ENTRY(output_dir_path), getenv("HOME"));
			gtk_entry_set_width_chars(GTK_ENTRY(output_dir_path), 10);
			gtk_editable_set_editable(GTK_EDITABLE(output_dir_path), FALSE);
		
		button_choose_dir = gtk_button_new_with_label("OPEN");
			g_signal_connect(button_choose_dir, "clicked", G_CALLBACK(browse_out_dir), NULL);
		
		GtkWidget *separator_pre_empty_space = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
		GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
		GtkWidget *separator_end_empty_space = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
		
		button_quit = gtk_button_new_with_label("QUIT");
			g_signal_connect(button_quit, "clicked", G_CALLBACK(legal_quit), NULL);
		
		
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(button_add), FALSE, FALSE, 1);
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(button_convert), FALSE, FALSE, 1);
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(button_stop), FALSE, FALSE, 1);
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(empty_space), TRUE, TRUE, 1);
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(output_dir_path), TRUE, TRUE, 1);
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(button_choose_dir), FALSE, FALSE, 1);
		
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(separator_pre_empty_space), FALSE, FALSE, 1);
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(separator), FALSE, FALSE, 1);
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(separator_end_empty_space), FALSE, FALSE, 1);
		
		gtk_box_pack_start(GTK_BOX(toolbar), GTK_WIDGET(button_quit), FALSE, FALSE, 1);
	
	
	// attached file list
	scrolled_win = gtk_scrolled_window_new(NULL, NULL);
		gtk_widget_set_margin_top(scrolled_win, 10);
		gtk_widget_set_margin_bottom(scrolled_win, 5);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_win), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolled_win), GTK_SHADOW_ETCHED_IN);
		gtk_box_pack_start(GTK_BOX(main_box), GTK_WIDGET(scrolled_win), TRUE, TRUE, 0);
	
	// tree view
	tree_view = gtk_tree_view_new();
		gtk_container_add(GTK_CONTAINER(scrolled_win), tree_view);
		gtk_drag_dest_set(GTK_WIDGET(tree_view), GTK_DEST_DEFAULT_ALL, NULL, 100, GDK_DRAG_ENTER);
		gtk_drag_dest_add_uri_targets(GTK_WIDGET(tree_view));

		GtkCellRenderer *renderer;
		renderer = gtk_cell_renderer_text_new();
		
		GtkTreeViewColumn *column_name = gtk_tree_view_column_new_with_attributes(C_COLUMN_NAME, renderer, "text", COLUMN_NAME, NULL);
		gtk_tree_view_column_set_min_width(column_name, C_COLUMN_NAME__WIDTH);
		gtk_tree_view_column_set_resizable(column_name, TRUE);
		gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column_name);
		
		GtkTreeViewColumn *column_size = gtk_tree_view_column_new_with_attributes(C_COLUMN_SIZE, renderer, "text", COLUMN_SIZE, NULL);
		gtk_tree_view_column_set_min_width(column_size, C_COLUMN_SIZE__WIDTH);
		gtk_tree_view_column_set_resizable(column_size, TRUE);
		gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column_size);
		
		GtkTreeViewColumn *column_status = gtk_tree_view_column_new_with_attributes(C_COLUMN_STATUS, renderer, "text", COLUMN_STATUS, NULL);
		gtk_tree_view_column_set_min_width(column_status, C_COLUMN_STATUS__WIDTH);
		gtk_tree_view_column_set_resizable(column_status, TRUE);
		gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column_status);
		
		GtkTreeViewColumn *column_path = gtk_tree_view_column_new_with_attributes(C_COLUMN_PATH, renderer, "text", COLUMN_PATH, NULL);
		gtk_tree_view_column_set_resizable(column_path, TRUE);
		gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column_path);
		
	// files store
	store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_STRING, G_TYPE_STRING);
		gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(store));
		g_object_unref(store);
	
	// progress bar
	progress_bar = gtk_progress_bar_new();
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), "Files 15/12");
	gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress_bar), FALSE);
	gtk_widget_set_margin_bottom(progress_bar, 15);
	gtk_container_add(GTK_CONTAINER(main_box), progress_bar);
	
	// tabs
	tabs = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(tabs), GTK_POS_TOP);
	
	for(i = 0; i < 2; i++)
	{
		if(i == 0)
			tab_label = gtk_label_new("Properties");
		else
			tab_label = gtk_label_new("Filters");
		
		tab_frame = gtk_frame_new("q");
		gtk_container_set_border_width(GTK_CONTAINER(tab_frame), 10);
		
		gtk_notebook_append_page(GTK_NOTEBOOK(tabs), tab_frame, tab_label);
		
		if(i == 0)
		{
			
		}
		else
		{
			
		}
	}
	
	gtk_container_add(GTK_CONTAINER(main_box), tabs);
	
	
	gtk_container_add(GTK_CONTAINER(mainwin), main_box);
	gtk_widget_show_all(mainwin);
}