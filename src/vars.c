GtkWidget *mainwin;

GtkWidget *button_add;
GtkWidget *button_convert;
GtkWidget *button_stop;

GtkWidget *progress_bar;

GtkWidget *tabs;

	GtkWidget *prop_box;
	GtkWidget *prop_label;
	
	GtkWidget *filt_box;
	GtkWidget *filt_label;

GtkWidget *main_box;
	GtkWidget *toolbar;
	GtkWidget *scrolled_win;
		GtkWidget *tree_view;
			GtkListStore *store;

GtkWidget *output_dir_path;
GtkWidget *button_choose_dir;
GtkWidget *button_quit;


const char *C_TITLE = "Image Manipulator";

const char *C_COLUMN_NAME = "Name";
const char *C_COLUMN_SIZE = "Size (MB)";
const char *C_COLUMN_STATUS = "Status";
const char *C_COLUMN_PATH = "Path";

const int C_COLUMN_NAME__WIDTH = 150;
const int C_COLUMN_SIZE__WIDTH = 80;
const int C_COLUMN_STATUS__WIDTH = 80;

enum {
	COLUMN_NAME,
	COLUMN_SIZE,
	COLUMN_STATUS,
	COLUMN_PATH,
	N_COLUMNS
};