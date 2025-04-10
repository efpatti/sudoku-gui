#include <gtk/gtk.h>
#include "sudoku.h"

int board[9][9]; // matriz do jogo
GtkWidget *entries[9][9]; // entradas da GUI

// Atualiza a interface com os números do board
void update_grid() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char text[2];
            if (board[i][j] != 0)
                sprintf(text, "%d", board[i][j]);
            else
                sprintf(text, "");
            gtk_entry_set_text(GTK_ENTRY(entries[i][j]), text);
        }
    }
}

void start_game(GtkWidget *widget, gpointer data) {
    generate_sudoku(board);
    update_grid();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sudoku por Ilelo");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Botão de iniciar
    GtkWidget *button = gtk_button_new_with_label("Start Game");
    g_signal_connect(button, "clicked", G_CALLBACK(start_game), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);

    // Grid do Sudoku
    GtkWidget *grid = gtk_grid_new();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            entries[i][j] = gtk_entry_new();
            gtk_entry_set_max_length(GTK_ENTRY(entries[i][j]), 1);
            gtk_widget_set_size_request(entries[i][j], 40, 40);
            gtk_grid_attach(GTK_GRID(grid), entries[i][j], j, i, 1, 1);
        }
    }
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 5);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}
