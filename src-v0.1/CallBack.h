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

#ifndef CALLBACK_H
#define CALLBACK_H

#include <gtk/gtk.h>
#include "op.h"


void buffer_text_changed(GtkTextBuffer *buf,gpointer data);

void menu_item_new_clicked(GtkWidget *wid,gpointer data);

void menu_item_open_clicked(GtkWidget *wid,gpointer data);

void menu_item_save_clicked(GtkWidget *wid,gpointer data);

void menu_item_save_as_clicked(GtkWidget *wid,gpointer data);

void menu_item_quit_clicked(GtkWidget *item,gpointer data);




void menu_item_copy_clicked(GtkWidget *wid,gpointer data);

void menu_item_cut_clicked(GtkWidget *wid,gpointer data);

void menu_item_paste_clicked(GtkWidget *wid,gpointer data);

void menu_item_delete_clicked(GtkWidget *wid,gpointer data);

void menu_item_select_all_clicked(GtkWidget *wid,gpointer data);

void menu_item_deselect_clicked(GtkWidget *wid,gpointer data);


void menu_item_settings_clicked(GtkWidget *wid,gpointer data);

void menu_item_about_clicked(GtkWidget *wid,gpointer data);


void mainWindowDeleteEvent(GtkWidget *wid,GdkEvent  *e,gpointer data);


void textViewChanged(GtkTextBuffer *buffer,gpointer data);
void textViewCut(GtkWidget *textView,gpointer data);
void textViewCopy(GtkWidget *textView,gpointer data);
void textViewPaste(GtkWidget *textView,gpointer data);
void textViewDelete(GtkWidget *textView,gpointer data);


#endif /* CALLBACK_H */
