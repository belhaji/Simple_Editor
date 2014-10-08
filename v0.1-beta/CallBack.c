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

#include "CallBack.h"
#include "op.h"

void buffer_text_changed(GtkTextBuffer *buf,gpointer data)
{
	docFile.isSaved = FALSE;
}


void menu_item_new_clicked(GtkWidget *wid,gpointer data)
{
	newFile (GTK_WIDGET(data));
}

void menu_item_open_clicked(GtkWidget *wid,gpointer data)
{
	openFile (GTK_WIDGET(data));
}

void menu_item_save_clicked(GtkWidget *wid,gpointer data)
{ 

	if(docFile.name != NULL && docFile.isSaved == FALSE)
		save (GTK_WIDGET(data));
	else
		saveAs(GTK_WIDGET(data));
}

void menu_item_save_as_clicked(GtkWidget *wid,gpointer data){
	saveAs (GTK_WIDGET(data));
}

void menu_item_quit_clicked(GtkWidget *item,gpointer data){

	quit (GTK_WIDGET(data));
}



void menu_item_copy_clicked(GtkWidget *wid,gpointer data){

	GtkClipboard *clipboard = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(data));
	gtk_text_buffer_copy_clipboard (buffer, clipboard);

}

void menu_item_cut_clicked(GtkWidget *wid,gpointer data){
	GtkClipboard *clipboard = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(data));
	gtk_text_buffer_cut_clipboard (buffer, clipboard,TRUE);
}

void menu_item_paste_clicked(GtkWidget *wid,gpointer data){
	GtkClipboard *clipboard = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(data));
	gtk_text_buffer_paste_clipboard (buffer, clipboard, NULL, TRUE);
}

void menu_item_delete_clicked(GtkWidget *wid,gpointer data){
	GtkWidget	  *textView	= GTK_WIDGET(data);
	GtkTextBuffer *buffer   = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	GtkTextIter iStart,iEnd;

	gtk_text_buffer_get_selection_bounds(buffer,&iStart,&iEnd);
	gtk_text_buffer_delete(buffer,&iStart,&iEnd);
	
}

void menu_item_select_all_clicked(GtkWidget *wid,gpointer data){
	GtkWidget	  *textView	= GTK_WIDGET(data);
	GtkTextBuffer *buffer   = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	GtkTextIter iStart,iEnd;
	gtk_text_buffer_get_bounds(buffer,&iStart,&iEnd);
	gtk_text_buffer_select_range(buffer,&iStart,&iEnd);
}

void menu_item_deselect_clicked(GtkWidget *wid,gpointer data){
	GtkWidget	  *textView	= GTK_WIDGET(data);
	GtkTextBuffer *buffer   = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	GtkTextIter iStart,iEnd;
	gtk_text_buffer_get_bounds(buffer,&iStart,&iEnd);
	gtk_text_buffer_select_range(buffer,&iEnd,&iEnd);
}

void menu_item_about_clicked(GtkWidget *wid,gpointer data){
	GtkWidget   *mainWindow = GTK_WIDGET(data);
	GtkWidget   *aboutDialog;
	const gchar		*author[] = {"adil belhaji",NULL};
	aboutDialog = gtk_about_dialog_new ();
	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(aboutDialog),"About");
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(aboutDialog),"Simple Editor");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(aboutDialog),"0.1 Beta");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(aboutDialog),"2014 (c) Adil Belhaji");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(aboutDialog),"Simple Editor is basic text editor i made it just for testing and apply some knowledge.");
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(aboutDialog),author);
	gtk_dialog_run(GTK_DIALOG (aboutDialog));
	gtk_widget_destroy(aboutDialog);
	
}

void mainWindowDeleteEvent(GtkWidget *wid,GdkEvent  *e,gpointer data)
{
	quit (GTK_WIDGET(data));	
}


