void add_files()
{
	GtkWidget *input_chooser = gtk_file_chooser_dialog_new("Choose Files", GTK_WINDOW(mainwin), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(input_chooser), TRUE);
	
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(input_chooser), getenv("HOME"));
	
	if(gtk_dialog_run(GTK_DIALOG(input_chooser)) == GTK_RESPONSE_ACCEPT)
	{
		GSList *current_iter;
		GSList *first_iter = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(input_chooser));
		for(current_iter = first_iter; current_iter != first_iter; current_iter = current_iter->next)
		{
			printf("%s\n", "test");
		}
		
		g_slist_free(current_iter);
		g_slist_free(first_iter);
	}
	
	gtk_widget_destroy(input_chooser);
}

void start_convert()
{
	printf("%s\n", "Convert");
}