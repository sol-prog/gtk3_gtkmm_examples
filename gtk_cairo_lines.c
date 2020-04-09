#include <cairo.h>
#include <gtk/gtk.h>

typedef struct {
    GRand *gr;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    int niter;
} UData;

static void draw_line(cairo_t *cr, double r, double g, double b, double x0, double y0, double x1, double y1) {
    cairo_set_source_rgb(cr, r, g, b);
    cairo_move_to(cr, x0, y0);
    cairo_line_to(cr, x1, y1);
    cairo_stroke(cr);
}

static gboolean display(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    UData *ud = (UData *) user_data;
    for(int i = 0; i < ud->niter; ++i) {
        double r = g_rand_double_range(ud->gr, 0.0, 1.0);
        double g = g_rand_double_range(ud->gr, 0.0, 1.0);
        double b = g_rand_double_range(ud->gr, 0.0, 1.0);

        double x0 = g_rand_double_range(ud->gr, ud->xmin, ud->xmax);
        double y0 = g_rand_double_range(ud->gr, ud->ymin, ud->ymax);
        double x1 = g_rand_double_range(ud->gr, ud->xmin,ud->xmax);
        double y1 = g_rand_double_range(ud->gr, ud->ymin, ud->ymax);

        draw_line(cr, r, g, b, x0, y0, x1, y1);
    }
    return FALSE;
}

int main(int argc, char *argv[]) {
    UData user_data = {g_rand_new(), 0, 800, 0, 600, 100};

    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    GtkWidget *draw_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), draw_area);

    g_signal_connect(G_OBJECT(draw_area), "draw", G_CALLBACK(display), (gpointer) &user_data);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_default_size(GTK_WINDOW(window), (gint) user_data.xmax, (gint) user_data.ymax);
    gtk_window_set_title(GTK_WINDOW(window), "Random Lines Demo");

    gtk_widget_show_all(window);

    gtk_main();
}
