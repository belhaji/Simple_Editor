/***************************************************************************
 *            op.c
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

#include <gtk/gtk.h>
#include <string.h>
#include "CallBack.h"

void newFile(GtkWidget *textView)
{
	GtkTextIter iStart,iEnd;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	gtk_text_buffer_get_bounds(buffer,&iStart,&iEnd);
	gchar * text = gtk_text_buffer_get_text(buffer,&iStart,&iEnd,FALSE);
	if(docFile.isSaved == FALSE && strcmp("",text)) 
	{	
		GtkWidget * msgDialog;
		msgDialog = gtk_message_dialog_new(NULL,
		                                   GTK_DIALOG_MODAL,
		                                   GTK_MESSAGE_QUESTION,
		                                   GTK_BUTTONS_YES_NO,
	                          			   "Do you wanna save your file ?",
		                                   NULL);
		switch (gtk_dialog_run (GTK_DIALOG(msgDialog))) 
		{   
			
			case GTK_RESPONSE_YES:
				if(docFile.name == NULL)
				{   
					if (saveAs(textView))
					{
						gtk_text_buffer_delete(buffer,&iStart,&iEnd);
					}
				}	
				else
				{
					save(textView);
					gtk_text_buffer_delete(buffer,&iStart,&iEnd);
					
				}
				break;
				
			case GTK_RESPONSE_NO:
				gtk_text_buffer_delete(buffer,&iStart,&iEnd);
				break;

		}
		
		gtk_widget_destroy (msgDialog);
	}else{
		
		gtk_text_buffer_delete(buffer,&iStart,&iEnd);
	}
		
	docFile.isSaved		= FALSE;
	docFile.name		= NULL;
	docFile.isOnDisk	= FALSE;
}


void openFile(GtkWidget *textView)
{

	if(docFile.isSaved == FALSE && docFile.isOnDisk == TRUE ) 
	{	
		GtkWidget * msgDialog;
		msgDialog = gtk_message_dialog_new(NULL,
		                                   GTK_DIALOG_MODAL,
		                                   GTK_MESSAGE_QUESTION,
		                                   GTK_BUTTONS_YES_NO,
	                          			   "Do you wanna save your file ?",
		                                   NULL);
		switch (gtk_dialog_run (GTK_DIALOG(msgDialog))) 
		{   
			
			case GTK_RESPONSE_YES:
				if(docFile.name == NULL)
				{   
					saveAs(textView);
				}	
				else
				{
					save(textView);
				}
		}
		
		gtk_widget_destroy (msgDialog);
	}
	gchar *fileName;
	gchar *text = NULL;
	GError *error;
	gsize  lenText;
	GtkWidget *dialog;
	GtkFileFilter *filter;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textView));
	filter = gtk_file_filter_new ();
	gtk_file_filter_set_name (filter,"Text Files");
	gtk_file_filter_add_pattern (filter,"*.*");
	dialog = gtk_file_chooser_dialog_new("Choose a file ..",
	                                     NULL,
	                                     GTK_FILE_CHOOSER_ACTION_OPEN,
	                                     GTK_STOCK_OPEN,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
	                                     NULL
	                                     );
	gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(dialog),TRUE);
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(dialog),g_get_home_dir ());
	switch (gtk_dialog_run (GTK_DIALOG(dialog)))
	{
		case GTK_RESPONSE_OK:
			fileName		= gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(dialog));
			docFile.name	= fileName;
			g_file_get_contents(fileName,&text,&lenText,&error);
			if(text == NULL)
			{
				g_print("Error: %s ",error->message);
				g_free (error);
			}
			gtk_text_buffer_set_text (buffer,text,(gint)lenText);

			docFile.isSaved		= TRUE;
			docFile.isOnDisk	= TRUE;
			g_free (text);
		default:
			gtk_widget_destroy (dialog);

	}
		

}


gboolean saveAs(GtkWidget *textView)
{
	GtkWidget *dialog;
	GtkFileFilter *filter;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textView));
	filter = gtk_file_filter_new ();
	gtk_file_filter_set_name (filter,"Text Files");
	gtk_file_filter_add_pattern (filter,"*.*");
	dialog = gtk_file_chooser_dialog_new("Save the file ..",
	                                     NULL,
	                                     GTK_FILE_CHOOSER_ACTION_SAVE,
	                                     GTK_STOCK_SAVE,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
	                                     NULL);

	gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(dialog),TRUE);
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(dialog),g_get_home_dir ());
	switch (gtk_dialog_run (GTK_DIALOG(dialog)))
	{
		case GTK_RESPONSE_OK:
			docFile.name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			save(textView);
			docFile.isSaved	 = TRUE;
			docFile.isOnDisk = TRUE;
			break;
			
	}
	gtk_widget_destroy (dialog);
}


void save(GtkWidget *textView)
{
	GtkTextIter iStart,iEnd;
	gchar *text = NULL;
	gsize  lenText;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textView));

	gtk_text_buffer_get_start_iter (buffer,&iStart);
	gtk_text_buffer_get_end_iter (buffer,&iEnd);
	text		= gtk_text_buffer_get_text (buffer,&iStart,&iEnd,TRUE);
	lenText		= (gsize) strlen(text);
	if(!g_file_set_contents (docFile.name,text,(gssize) lenText,NULL))
	{
		g_print("Error: cannot save the file\n");

	}
	g_free (text);
	docFile.isSaved	 = TRUE;
	docFile.isOnDisk = TRUE;	
}

void quit(GtkWidget * textView)
{
	GtkTextIter iStart,iEnd;
	gchar *text = NULL;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textView));
	gtk_text_buffer_get_start_iter (buffer,&iStart);
	gtk_text_buffer_get_end_iter (buffer,&iEnd);
	text		= gtk_text_buffer_get_text (buffer,&iStart,&iEnd,TRUE);

	if(docFile.isSaved == FALSE && strlen(text) != 0 )  
	{
		GtkWidget * msgDialog;
		msgDialog = gtk_message_dialog_new(NULL,
		                                   GTK_DIALOG_MODAL,
		                                   GTK_MESSAGE_QUESTION,
		                                   GTK_BUTTONS_YES_NO,
		                                   "Do you manna save your file ?",
		                                   NULL);

		switch (gtk_dialog_run (GTK_DIALOG(msgDialog)))
		{
			case GTK_RESPONSE_YES:
				if(docFile.name == NULL)
			{
					if(saveAs(textView))
					{
						gtk_main_quit ();
					}else{
						gtk_widget_destroy(msgDialog);
					}
				}
				else
			{   
				save(textView);
				gtk_widget_destroy(msgDialog);
				gtk_main_quit ();
			}
				break;
			case GTK_RESPONSE_NO:
				gtk_widget_destroy(msgDialog);
				gtk_main_quit ();


		}
	}else{
		gtk_main_quit();
	}
}


void applySettings(Settings *config,GtkWidget *textView)
{
	PangoFontDescription *fontDesc;
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(textView),config->wrap_mode);
	gtk_text_view_set_justification (GTK_TEXT_VIEW(textView),config->justification);
	gtk_text_view_set_left_margin (GTK_TEXT_VIEW(textView),config->left_margin);
	gtk_text_view_set_right_margin (GTK_TEXT_VIEW(textView),config->right_margin);
	
	fontDesc = pango_font_description_from_string (config->font);
	gtk_widget_modify_font (textView,fontDesc);
	pango_font_description_free (fontDesc);
}

void loadSettings(Settings *config)
{
	GKeyFile *file = g_key_file_new();
	gchar *configFileName = g_malloc(sizeof(gchar)*50);
	sprintf(configFileName,"%s/.simple_editor/se.rc",g_get_home_dir ());
	if (!g_key_file_load_from_file(file,configFileName,G_KEY_FILE_NONE,NULL))
	{
		gchar *configFileDir = g_malloc(sizeof(gchar)*50);
		gchar *defaultConf = "[settings]\n"
							 "wrapMode=none\n"
							 "justification=left\n"
						     "leftMargin=5\n"
							 "rightMargin=5\n"
							 "font=Sans 13\n";
		sprintf(configFileDir,"%s/.simple_editor/",g_get_home_dir ());
		
		g_mkdir (configFileDir,-1);
		g_file_set_contents (configFileName,defaultConf,85,NULL);
	}
	g_key_file_load_from_file(file,configFileName,G_KEY_FILE_NONE,NULL);
	if(!g_strcmp0(g_key_file_get_string(file,"settings","wrapMode",NULL),"none"))
	   config->wrap_mode = GTK_WRAP_NONE;
	else
	   config->wrap_mode = GTK_WRAP_WORD;
	if(!g_strcmp0(g_key_file_get_string(file,"settings","justification",NULL),"left"))
	   config->justification = GTK_JUSTIFY_LEFT;
	else if(!g_strcmp0(g_key_file_get_string(file,"settings","justification",NULL),"right"))
	   config->justification = GTK_JUSTIFY_RIGHT;
	else
	   config->justification = GTK_JUSTIFY_CENTER;
	config->left_margin	 =  g_key_file_get_integer (file,"settings","leftMargin",NULL);	
	config->right_margin =	g_key_file_get_integer (file,"settings","rightMargin",NULL);
	config->font		 =   g_key_file_get_string(file,"settings","font",NULL);
	
}


void saveSettings(Settings *config)
{
	GKeyFile *file = g_key_file_new();
	gchar *configFileName = g_malloc(sizeof(gchar)*50);
	sprintf(configFileName,"%s/.simple_editor/se.rc",g_get_home_dir ());
	if (g_key_file_load_from_file(file,configFileName,G_KEY_FILE_NONE,NULL))
	{
		if(config->wrap_mode == GTK_WRAP_NONE)
			g_key_file_set_string (file,"settings","wrapMode","none");
		else 
			g_key_file_set_string (file,"settings","wrapMode","word");
		if(config->justification == GTK_JUSTIFY_LEFT)
			g_key_file_set_string (file,"settings","justification","left");
		else if(config->justification == GTK_JUSTIFY_RIGHT)
			g_key_file_set_string (file,"settings","justification","right");
		else
			g_key_file_set_string (file,"settings","justification","center");

		g_key_file_set_string (file,"settings","font",config->font);
		g_key_file_set_integer (file,"settings","leftMargin",config->left_margin);	
		g_key_file_set_integer (file,"settings","rightMargin",config->right_margin);
		g_key_file_save_to_file (file,configFileName,NULL);
		g_key_file_free (file);
	}
		
}






