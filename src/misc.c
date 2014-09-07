void add_files()
{
	GtkWidget *input_chooser = gtk_file_chooser_dialog_new("Choose Files", GTK_WINDOW(mainwin), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(input_chooser), TRUE);
	
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(input_chooser), getenv("HOME"));
	
	if(gtk_dialog_run(GTK_DIALOG(input_chooser)) == GTK_RESPONSE_ACCEPT)
	{
		
		GSList *selected_file, *sel;
		selected_file = sel = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(input_chooser));
		while(selected_file)
		{
			printf("%s\n", selected_file->data);
			main_list = g_slist_append(main_list, selected_file->data);
			
			add_to_list(store, selected_file->data);
			
			g_free(selected_file->data);
			selected_file = selected_file->next;
		}
		
		g_slist_free(selected_file);
		g_slist_free(sel);
	}
	
	gtk_widget_destroy(input_chooser);
}

void add_to_list(GtkWidget *list, gchar *str)
{
	if(!g_file_test(str,G_FILE_TEST_IS_SYMLINK) && !g_file_test(str,G_FILE_TEST_IS_DIR) && g_file_test(str,G_FILE_TEST_IS_REGULAR))
	{
		/*GtkTreeIter iter;
		store = GTK_LIST_STORE(  gtk_tree_view_get_model( GTK_TREE_VIEW(list) )  );
		gtk_list_store_append(store, &iter);
		
		char* fullname=get_full_name(str);
		
		gtk_list_store_set(store, &iter, "Name", fullname, "Status", "Waiting", "Path", str, -1);
		
		free(fullname);*/
	}
}

void start_convert()
{
	printf("%s\n", "Convert");
}