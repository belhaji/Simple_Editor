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

	if(docFile.name != NULL && docFile.isOnDisk == TRUE)
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



void menu_item_settings_clicked(GtkWidget *wid,gpointer data){

	loadSettings (&config);
	
	GtkWidget   *dialog,
				*fontButton,
				*labelFontButton,
				*labelWrap,
				*radioWrapNone,
				*radioWrapWord,
				*labelJustify,
				*radioJustifyLeft,
				*radioJustifyRight,
				*radioJustifyCenter,
				*labelMarginLeft,
				*spinLeftMargin,
				*labelMarginRight,
				*spinRightMargin,
				*table,
				*area,
				*textView;
	textView = GTK_WIDGET(data);
	GSList  *groupWrap,
			*groupJustify;
	gint response;
	dialog = gtk_dialog_new_with_buttons ("Settings",
                                                 NULL,
                                                 GTK_DIALOG_MODAL,
                                                 GTK_STOCK_OK,
                                                 GTK_RESPONSE_OK,
	                                  			 GTK_STOCK_APPLY,
	                                  			 GTK_RESPONSE_APPLY,
                                                 GTK_STOCK_CANCEL,
                                                 GTK_RESPONSE_CANCEL,
                                                 NULL);
	
	area				=   gtk_dialog_get_content_area (GTK_DIALOG(dialog));
	table				=   gtk_table_new (7,4,TRUE);
	labelWrap			=   gtk_label_new("Wrap text :");
	labelJustify		=   gtk_label_new("justification :");
	labelMarginLeft		=   gtk_label_new("margin left :");
	labelMarginRight	=   gtk_label_new("margin right :");
	labelFontButton		=   gtk_label_new("Font :");
	radioWrapNone		=   gtk_radio_button_new_with_label (NULL,"wrap none");
	groupWrap			=   gtk_radio_button_get_group (GTK_RADIO_BUTTON(radioWrapNone));
	radioWrapWord		=   gtk_radio_button_new_with_label (groupWrap,"wrap word");
	radioJustifyCenter  =   gtk_radio_button_new_with_label (NULL,"justify center");
	groupJustify		=   gtk_radio_button_get_group (GTK_RADIO_BUTTON(radioJustifyCenter));
	radioJustifyLeft	=   gtk_radio_button_new_with_label (groupJustify,"justify left");
	groupJustify		=   gtk_radio_button_get_group (GTK_RADIO_BUTTON(radioJustifyLeft));
	radioJustifyRight   =   gtk_radio_button_new_with_label (groupJustify,"justify right");
	spinLeftMargin		=   gtk_spin_button_new_with_range (0,50,5);
	spinRightMargin		=   gtk_spin_button_new_with_range (0,50,5);
	fontButton			=   gtk_font_button_new_with_font (config.font);
	
	if(config.wrap_mode == GTK_WRAP_NONE)
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radioWrapNone),TRUE);
	else if(config.wrap_mode == GTK_WRAP_WORD)
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radioWrapWord),TRUE);
	if(config.justification == GTK_JUSTIFY_LEFT)
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radioJustifyLeft),TRUE);
	else if(config.justification == GTK_JUSTIFY_RIGHT)
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radioJustifyRight),TRUE);
	else if(config.justification == GTK_JUSTIFY_CENTER)
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(radioJustifyCenter),TRUE);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(spinLeftMargin),(gdouble)config.left_margin);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(spinRightMargin),(gdouble)config.right_margin);
	gtk_font_button_set_font_name (GTK_FONT_BUTTON(fontButton),config.font);
	gtk_table_attach_defaults (GTK_TABLE(table),labelWrap,0,1,0,1);
	gtk_table_attach_defaults (GTK_TABLE(table),radioWrapNone,1,2,1,2);
	gtk_table_attach_defaults (GTK_TABLE(table),radioWrapWord,2,3,1,2);
	
	gtk_table_attach_defaults (GTK_TABLE(table),labelJustify,0,1,2,3);
	gtk_table_attach_defaults (GTK_TABLE(table),radioJustifyLeft,1,2,3,4);
	gtk_table_attach_defaults (GTK_TABLE(table),radioJustifyCenter,2,3,3,4);
	gtk_table_attach_defaults (GTK_TABLE(table),radioJustifyRight,3,4,3,4);

	gtk_table_attach_defaults (GTK_TABLE(table),labelMarginLeft,0,1,4,5);
	gtk_table_attach_defaults (GTK_TABLE(table),spinLeftMargin,1,2,4,5);
	gtk_table_attach_defaults (GTK_TABLE(table),labelMarginRight,0,1,5,6);
	gtk_table_attach_defaults (GTK_TABLE(table),spinRightMargin,1,2,5,6);

	gtk_table_attach_defaults (GTK_TABLE(table),labelFontButton,0,1,6,7);
	gtk_table_attach_defaults (GTK_TABLE(table),fontButton,2,4,6,7);

	
	gint i;
	for(i=1;i<7;i++)
		gtk_table_set_row_spacing (GTK_TABLE(table),i,5);
	gtk_table_set_homogeneous (GTK_TABLE(table),TRUE);
	gtk_box_pack_start (GTK_BOX(area),table,FALSE,FALSE,0);
	gtk_widget_show_all (table);	
	
	do{
		response = gtk_dialog_run (GTK_DIALOG(dialog));
		switch(response){
		case GTK_RESPONSE_APPLY:
		case GTK_RESPONSE_OK:
			if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radioWrapNone)))
					config.wrap_mode = GTK_WRAP_NONE;
			else if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radioWrapWord)))
					config.wrap_mode = GTK_WRAP_WORD;
			if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radioJustifyLeft)))
					config.justification = GTK_JUSTIFY_LEFT;
			else if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radioJustifyCenter)))
					config.justification = GTK_JUSTIFY_CENTER;
			else if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radioJustifyRight)))
					config.justification = GTK_JUSTIFY_RIGHT;
			config.left_margin  = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinLeftMargin));
			config.right_margin = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinRightMargin));
			config.font			= g_malloc(sizeof(gchar)*20);
			sprintf(config.font,"%s",gtk_font_button_get_font_name (GTK_FONT_BUTTON(fontButton)));
			applySettings (&config,textView);
			saveSettings (&config);
			if(response == GTK_RESPONSE_OK)
				gtk_widget_destroy (dialog);
			break;
		case GTK_RESPONSE_CANCEL:
			gtk_widget_destroy (dialog);
	}	
	}while(response == GTK_RESPONSE_APPLY);

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


