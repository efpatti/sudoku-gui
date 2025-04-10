#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 9

GtkWidget *entries[SIZE][SIZE];

// Limita input a 1 caractere (só número de 1 a 9)
static void on_insert_text(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer data) {
    if (!g_ascii_isdigit(*text) || *text == '0') {
        g_signal_stop_emission_by_name(editable, "insert-text");
    } else if (gtk_editable_get_chars(editable, 0, -1)[0] != '\0') {
        g_signal_stop_emission_by_name(editable, "insert-text");
    }
}

static void create_grid(GtkWidget *grid) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            GtkWidget *entry = gtk_entry_new();
            gtk_entry_set_max_length(GTK_ENTRY(entry), 1);
            gtk_widget_set_size_request(entry, 40, 40);
            gtk_entry_set_alignment(GTK_ENTRY(entry), 0.5);
            gtk_editable_set_editable(GTK_EDITABLE(entry), TRUE);
            g_signal_connect(entry, "insert-text", G_CALLBACK(on_insert_text), NULL);
            gtk_grid_attach(GTK_GRID(grid), entry, col, row, 1, 1);
            entries[row][col] = entry;
        }
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sudoku");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 2);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 2);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);

    create_grid(grid);
    gtk_container_add(GTK_CONTAINER(window), grid);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
