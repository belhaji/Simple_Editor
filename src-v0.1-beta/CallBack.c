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


void menu_item_font_clicked (GtkWidget *wid,gpointer data){
	GtkWidget *dialog,*textView;
	gchar * fontName;
	PangoFontDescription *fontDesc;
	gchar* configFileName = g_malloc(sizeof(gchar)*50);
	FILE* configFile;
	sprintf(configFileName,"%s/.simple_editor.conf",g_get_home_dir ());
	textView = GTK_WIDGET(data);
	dialog = gtk_font_selection_dialog_new ("Choose Font ");
	switch(gtk_dialog_run (GTK_DIALOG(dialog)))
	{
		case GTK_RESPONSE_OK:
			fontName = gtk_font_selection_dialog_get_font_name (GTK_FONT_SELECTION_DIALOG(dialog));
			fontDesc = pango_font_description_from_string (fontName);
			gtk_widget_modify_font (textView,fontDesc);
			pango_font_description_free (fontDesc);
			configFile = fopen(configFileName,"w+");
			if(configFile == NULL)
				g_print("error fopen\n");
			else{
				fprintf(configFile,"%s",fontName);
				fclose (configFile);
				}
			g_free (fontName);
			g_free(configFileName);
			gtk_widget_destroy (dialog);
			break;
		case GTK_RESPONSE_CANCEL:
			gtk_widget_destroy (dialog);
			break; 
	}
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

void textViewCut(GtkWidget *textView,gpointer data){
	GtkWidget *statusBar	= GTK_WIDGET(data);
	guint	   context_id   = gtk_statusbar_get_context_id (GTK_STATUSBAR(statusBar),"notifyMsgs");
	gtk_statusbar_remove_all (GTK_STATUSBAR(statusBar),context_id);
	gtk_statusbar_push (GTK_STATUSBAR(statusBar),context_id,"text has been cuted successfuly !");
	
}
void textViewCopy(GtkWidget *textView,gpointer data){
	GtkWidget *statusBar	= GTK_WIDGET(data);
	guint	   context_id   = gtk_statusbar_get_context_id (GTK_STATUSBAR(statusBar),"notifyMsgs");
	gtk_statusbar_remove_all (GTK_STATUSBAR(statusBar),context_id);
	gtk_statusbar_push (GTK_STATUSBAR(statusBar),context_id,"text has been copied successfuly !");
}
void textViewPaste(GtkWidget *textView,gpointer data){
	GtkWidget *statusBar	= GTK_WIDGET(data);
	guint	   context_id   = gtk_statusbar_get_context_id (GTK_STATUSBAR(statusBar),"notifyMsgs");
	gtk_statusbar_remove_all (GTK_STATUSBAR(statusBar),context_id);
	gtk_statusbar_push (GTK_STATUSBAR(statusBar),context_id,"text has been pasted successfuly !");
}
void textViewDelete(GtkWidget *textView,gpointer data){
	GtkWidget *statusBar	= GTK_WIDGET(data);
	guint	   context_id   = gtk_statusbar_get_context_id (GTK_STATUSBAR(statusBar),"notifyMsgs");
	gtk_statusbar_remove_all (GTK_STATUSBAR(statusBar),context_id);
	gtk_statusbar_push (GTK_STATUSBAR(statusBar),context_id,"text has been deleted successfuly !");
}


