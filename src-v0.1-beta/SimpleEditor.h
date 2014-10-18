/*
 * Copyright (C) 2014 adil belhaji <belhaji.dev@gmail.com>
 * 
 * SimpleEditor is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * SimpleEditor is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SIMPLEEDITOR_H
#define SIMPLEEDITOR_H

#include <gtk/gtk.h>







GtkWidget * createWindow(gchar *title,
                         gint width,
                         gint height,
                         GtkWindowPosition pos);


GtkWidget * createMenuBar(GtkWidget * textView,GtkWidget *mainWindow);



GtkWidget * createToolBar(GtkWidget * textView);


#endif /* SIMPLEEDITOR_H */
