char* get_full_name(char* path)
{
	char* fullname;
	char* full_name_iter;
	char* path_iter;
	char* last_slash = strrchr(path, '/');
	
	fullname = calloc(strlen(path) - (last_slash - path) + 1, sizeof(char));
	full_name_iter = fullname;

	path_iter = last_slash + 1;
	while(*path_iter != '\0')
	{
		*full_name_iter = *path_iter;
		full_name_iter++;
		path_iter++;
	}
	*full_name_iter = '\0';
	return fullname;
}

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
			add_to_list(selected_file->data);
			
			g_free(selected_file->data);
			selected_file = selected_file->next;
		}
		
		g_slist_free(selected_file);
		g_slist_free(sel);
	}
	
	gtk_widget_destroy(input_chooser);
}

void add_to_list(gchar *str)
{
	if(!g_file_test(str, G_FILE_TEST_IS_SYMLINK) && !g_file_test(str, G_FILE_TEST_IS_DIR) && g_file_test(str, G_FILE_TEST_IS_REGULAR))
	{
		GtkTreeIter iter;
		store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view)));
		gtk_list_store_append(store, &iter);
		
		char* fullname = get_full_name(str);
		
		gtk_list_store_set(store, &iter, C_COLUMN_NAME, fullname, C_COLUMN_STATUS, "Waiting", C_COLUMN_PATH, str, -1);
		
		free(fullname);
	}
}

void browse_out_dir()
{
	GtkWidget *output_chooser = gtk_file_chooser_dialog_new("Choose Folder", GTK_WINDOW(mainwin), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(output_chooser), getenv("HOME"));
	
	if(gtk_dialog_run(GTK_DIALOG(output_chooser)) == GTK_RESPONSE_ACCEPT)
	{
		char *folder_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(output_chooser));
		if(access(folder_name, 7) == 0)
		{
			gtk_entry_set_text(output_dir_path, folder_name);
		}
		free(folder_name);
	}
	
	gtk_widget_destroy(output_chooser);
}

void legal_quit()
{
	printf("quit\n");
	gtk_main_quit();
}

void start_convert()
{
	printf("%s\n", "Convert");
}