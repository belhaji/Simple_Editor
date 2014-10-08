/***************************************************************************
 *            operations.h
 *
 *  Sat October 04 12:30:52 2014
 *  Copyright  2014  adil belhaji
 *  
 ****************************************************************************/
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


#ifndef	 OP_H

#define  OP_H

#include <gtk/gtk.h>


typedef struct {
	gchar *name;
	gboolean isSaved;
	gboolean isOnDisk;
}Document;

extern Document docFile;

void newFile(GtkWidget *textView);

void openFile(GtkWidget *textView);

void save(GtkWidget *textView);

gboolean saveAs(GtkWidget *textView);

void quit();

#endif /* OPERETIONS_H */