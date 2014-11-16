#ifndef BAR_H
#define BAR_H

#include <gtk/gtk.h>
#include <stdio.h>

#define SEARCH_WIDTH (500)
#define SEARCH_HEIGHT (50)

typedef struct wconf_t wconf_t;
struct wconf_t {
        char *style;
        gboolean (*keypress)(GtkWidget *, GdkEventKey *);
};

/* keeping track of the search entry */
static GtkWidget *search;

/*
 * Creates the main window and initializes the search widgets
 *
 * returns: a pointer to the GtkWidget containing the search entry
 */
GtkWidget *create_window(wconf_t);

/*
 * Creates the search entry
 *
 * returns:     GtkWidget of type GtkEntry
 */
static GtkWidget *create_search(gboolean (*keypress)(GtkWidget*, GdkEventKey*));

/* 
 * Style window using style.css
 */
static void style_window(GtkWidget *, wconf_t);

#endif
