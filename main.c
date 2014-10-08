
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

#include "SimpleEditor.h"
#include "CallBack.h"
#include "op.h"

Document docFile;


int main(int argc,char *argv[])
{

	GtkWidget *mainWindow;
	GtkWidget *mainVBox;
	GtkWidget *menuBar;
	GtkWidget *scrolledWindow;
	GtkWidget *textView;


	gtk_init (&argc,&argv);

	mainWindow		= createWindow ("SimpleEditor",600,400,GTK_WIN_POS_CENTER);
	mainVBox		= gtk_vbox_new (FALSE,0);
	textView		= gtk_text_view_new ();
	scrolledWindow  = gtk_scrolled_window_new (NULL,NULL);
	menuBar			= createMenuBar (textView,mainWindow);


	g_signal_connect(G_OBJECT(mainWindow),"delete-event",G_CALLBACK(mainWindowDeleteEvent),(gpointer)textView);

	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolledWindow),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

	gtk_text_view_set_accepts_tab (GTK_TEXT_VIEW(textView),TRUE);
	gtk_text_view_set_left_margin (GTK_TEXT_VIEW(textView),5);
	gtk_text_view_set_right_margin(GTK_TEXT_VIEW(textView),5);
	


	
	gtk_container_add (GTK_CONTAINER(mainWindow),mainVBox);
	gtk_box_pack_start (GTK_BOX(mainVBox),menuBar,FALSE,FALSE,0);
	gtk_box_pack_start (GTK_BOX(mainVBox),scrolledWindow,TRUE,TRUE,0);
	gtk_container_add (GTK_CONTAINER(scrolledWindow),textView);

	gtk_widget_show_all(mainWindow);
	gtk_main ();
	return 0;
}











































