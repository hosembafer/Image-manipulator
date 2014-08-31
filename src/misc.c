void add_files()
{
	GtkWidget *input_chooser = gtk_file_chooser_dialog_new("Choose Files", GTK_WINDOW(mainwin), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(input_chooser), TRUE);
	
	if(gtk_dialog_run(GTK_DIALOG(input_chooser)) == GTK_RESPONSE_ACCEPT)
	{
		
	}
	
	gtk_widget_destroy(input_chooser);
}

void start_convert()
{
	printf("%s\n", "Convert");
}