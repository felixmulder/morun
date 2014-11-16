#include "widgets.h"

GtkWidget *create_window(gboolean (*keypress)(GtkWidget *, GdkEventKey *))
{
        GtkWidget       *window;
        GtkWidget       *fixed_cont;
        
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

        fixed_cont = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(window), fixed_cont);
        
        search = create_search(keypress);
        gtk_container_add(GTK_CONTAINER(fixed_cont), search);

        g_signal_connect(G_OBJECT(window), "delete-event", gtk_main_quit, NULL);
        g_signal_connect(G_OBJECT(window), "draw", G_CALLBACK(draw), NULL);
        g_signal_connect(G_OBJECT(search), "draw", G_CALLBACK(draw), NULL);

        style_window(window);
        return window;
}

static void style_window(GtkWidget *window)
{
        GdkDisplay      *display;
        GdkScreen       *screen;
        GtkCssProvider  *provider;
        GFile           *file;
        GError          *err;

        gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        gtk_window_set_default_size(GTK_WINDOW(window), 500, 50);
        gtk_window_set_title(GTK_WINDOW(window), "Morun");
        gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

        file = g_file_new_for_path("./style.css");
        provider = gtk_css_provider_new();
        display = gdk_display_get_default();
        screen = gdk_display_get_default_screen(display);
        err = NULL;

        gtk_style_context_add_provider_for_screen(screen,
                        GTK_STYLE_PROVIDER(provider),
                        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

        gtk_css_provider_load_from_file(GTK_CSS_PROVIDER(provider), file, &err);

        if (err != NULL)
                printf("Error occurred while loading style: %s\n", err->message);

        g_object_unref(provider);
}

static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer userdata)
{
        cairo_t *new_cr = gdk_cairo_create(gtk_widget_get_window(widget));
        cairo_set_source_rgba(new_cr, 1.0, 1.0, 1.0, 0.5);

        /* draw the background */
        cairo_set_operator (new_cr, CAIRO_OPERATOR_SOURCE);
        cairo_paint (new_cr);
        cairo_destroy(new_cr);

        return FALSE;
}

static GtkWidget *create_search(gboolean (*key_pressed)(GtkWidget *, GdkEventKey *))
{
        GtkWidget* entry = gtk_entry_new();
        gtk_widget_set_size_request(entry, 500, 50);
        gtk_widget_set_name(entry, "search");
        gtk_widget_set_events(entry, GDK_KEY_PRESS_MASK);
        g_signal_connect(G_OBJECT(entry),
                         "key-release-event",
                         G_CALLBACK(key_pressed),
                         NULL);
        return entry;
}
