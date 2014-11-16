#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

#include "widgets.h"
#include "run.h"

static gboolean key_pressed(GtkWidget *entry, GdkEventKey *ekey)
{
        char            *keyval;
        
        keyval = gdk_keyval_name(ekey->keyval);
        printf("key pressed: %s\n", keyval);

        if (strcmp(keyval, "Return") == 0) {
                run_prog(gtk_entry_get_text(GTK_ENTRY(entry)));
                gtk_main_quit();
        }

        return FALSE;
}

int main(int argc, char *argv[])
{
        GtkWidget       *window;

        gtk_init(&argc, &argv);
        window = create_window(key_pressed);
        gtk_widget_show_all(window);
        gtk_main();

        return 0;
}
