#include <gtk/gtk.h>

int main(int argc, char **argv) {
    gtk_init(&argc,&argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(win), 800, 600);
    gtk_window_set_title(GTK_WINDOW(win), "Hello, World!");
    g_signal_connect(G_OBJECT(win), "destroy", gtk_main_quit, NULL);
    gtk_widget_show(win);

    gtk_main();
}
