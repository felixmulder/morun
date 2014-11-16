#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "bar.h"
#include "run.h"

static gboolean key_pressed(GtkWidget *entry, GdkEventKey *ekey)
{
        const char *text;

        switch (ekey->keyval) {
        case GDK_KEY_Return:
                text = gtk_entry_get_text(GTK_ENTRY(entry));
                if (strcmp(text, "") == 0)
                        break;
                run_prog(text);
                gtk_main_quit();
                break;
        case GDK_KEY_Escape:
                gtk_main_quit();
                break;
        default:
                break;
        }

        return FALSE;
}

/*
 * parses args and returns style string, should be
 * re-written to use unistd arg parsing
 */
static char *parse_args(int argc, char *argv[])
{
        int i;
        for (i = 0; i < argc; i++) {
                if (strcmp(argv[i], "-s") == 0 && i + 1 <= argc) {
                        size_t len = strlen(argv[i+1]);
                        char *style = malloc((len + 1)* sizeof(char));
                        snprintf(style, len + 1, "%s", argv[i+1]);
                        return style;
                } else if (strcmp(argv[i], "--help") == 0 ||
                           strcmp(argv[i], "-h") == 0) {
                        printf("Usage: morun -s STYLE\n");
                        exit(0);

                }
        }

        return NULL;
}

int main(int argc, char *argv[])
{
        GtkWidget       *window;

        gtk_init(&argc, &argv);

        wconf_t conf = {
                .style = parse_args(argc, argv),
                .keypress = key_pressed
        };

        window = create_window(conf);
        gtk_widget_show_all(window);
        gtk_main();

        return 0;
}
