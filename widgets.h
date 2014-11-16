#ifndef WIDGETS_H
#define WIDGETS_H

#include <gtk/gtk.h>
#include <stdio.h>

/* keeping track of the search entry */
static GtkWidget *search;

/*
 * Creates the main window and initializes the search widgets
 *
 * returns: a pointer to the GtkWidget containing the search entry
 */
GtkWidget *create_window(gboolean (*keypress)(GtkWidget *, GdkEventKey *));
/*
 * Creates the search entry
 *
 * returns:     GtkWidget of type GtkEntry
 */
static GtkWidget *create_search(gboolean (*keypress)(GtkWidget *, GdkEventKey *));

static void style_window(GtkWidget *);
static gboolean draw(GtkWidget *widget,
                     cairo_t *new_cr,
                     gpointer user_data);

#endif
