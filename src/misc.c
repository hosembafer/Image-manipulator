char *get_full_name(char* path)
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

double get_file_size(char *filepath)
{
	struct stat st;
	double f_b_size = 0, mb = 0;
	
	if(stat(filepath, &st) == 0)
		f_b_size = st.st_size;
	
	mb = f_b_size / (1024 * 1024);
	
	return mb;
}

void add_to_list(gchar *str)
{
	double file_size;
	char* fullname;
	GtkTreeIter iter;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view)));
	
	if(!g_file_test(str, G_FILE_TEST_IS_SYMLINK) && !g_file_test(str, G_FILE_TEST_IS_DIR) && g_file_test(str, G_FILE_TEST_IS_REGULAR))
	{
		fullname = get_full_name(str);
		file_size = get_file_size(str);
		
		printf("%s - %f - %s - %s\n", fullname, file_size, "Waiting...", str);
		
		gtk_list_store_append(GTK_LIST_STORE(store), &iter);
		gtk_list_store_set(GTK_LIST_STORE(store), &iter, C_COLUMN_NAME, fullname, C_COLUMN_SIZE, file_size, C_COLUMN_STATUS, "Waiting", C_COLUMN_PATH, str, -1);
		
		free(fullname);
	}
}

void add_files()
{
	GtkWidget *input_chooser = gtk_file_chooser_dialog_new("Choose Files", GTK_WINDOW(mainwin), GTK_FILE_CHOOSER_ACTION_OPEN, "CANCEL", GTK_RESPONSE_CANCEL, "ADD", GTK_RESPONSE_ACCEPT, NULL);
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

void browse_out_dir()
{
	GtkWidget *output_chooser = gtk_file_chooser_dialog_new("Choose Folder", GTK_WINDOW(mainwin), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "CANCEL", GTK_RESPONSE_CANCEL, "OPEN", GTK_RESPONSE_ACCEPT, NULL);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(output_chooser), getenv("HOME"));
	
	if(gtk_dialog_run(GTK_DIALOG(output_chooser)) == GTK_RESPONSE_ACCEPT)
	{
		char *folder_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(output_chooser));
		if(access(folder_name, 7) == 0)
		{
			gtk_entry_set_text(GTK_ENTRY(output_dir_path), folder_name);
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