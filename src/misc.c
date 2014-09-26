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

void get_msg_win(gchar *msg)
{
	GtkWidget *popwin = gtk_message_dialog_new(GTK_WINDOW(mainwin), GTK_DIALOG_MODAL, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, msg);
	gtk_dialog_run(GTK_DIALOG(popwin));
	gtk_widget_destroy(popwin);
}

void add_to_list(GtkWidget *list, gchar *str)
{
	double file_size;
	char* fullname;
	GtkTreeIter iter;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
	
	if(!g_file_test(str, G_FILE_TEST_IS_SYMLINK) && !g_file_test(str, G_FILE_TEST_IS_DIR) && g_file_test(str, G_FILE_TEST_IS_REGULAR))
	{
		fullname = get_full_name(str);
		file_size = get_file_size(str);
		
		printf("%s - %f - %s - %s\n", fullname, file_size, "Waiting...", str);
		
		gtk_list_store_append(GTK_LIST_STORE(store), &iter);
		gtk_list_store_set(GTK_LIST_STORE(store), &iter,
			COLUMN_NAME, fullname,
			COLUMN_SIZE, file_size,
			COLUMN_STATUS, "Waiting",
			COLUMN_PATH, str,
			-1);
		
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
			add_to_list(tree_view, selected_file->data);
			
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

	printf("%s\n", gtk_entry_get_text(GTK_ENTRY(output_dir_path)));
}

void legal_quit()
{
	printf("quit\n");
	gtk_main_quit();
}

void get_convert()
{
	gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress_bar), TRUE);
	
	gtk_widget_set_sensitive(button_add, FALSE);
	gtk_widget_set_sensitive(button_convert, FALSE);
	gtk_widget_set_sensitive(button_stop, TRUE);
	gtk_widget_set_sensitive(button_choose_dir, FALSE);
	
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 0.3);
	
	printf("%s\n", "Convert");
}

void get_stop()
{
	gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress_bar), FALSE);
	
	gtk_widget_set_sensitive(button_add, TRUE);
	gtk_widget_set_sensitive(button_convert, TRUE);
	gtk_widget_set_sensitive(button_stop, FALSE);
	gtk_widget_set_sensitive(button_choose_dir, TRUE);

	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 0.0);

	printf("Stop\n");
}

void remove_store_item()
{
	printf("Remove item\n");
}