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




GtkWidget * createWindow(gchar *title,gint width,gint height,GtkWindowPosition pos)
{
	GtkWidget *icon = gtk_image_new_from_file ("/usr/share/simple_editor/icon.png");
	GtkWidget * window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW(window),width,height);
	gtk_window_set_position (GTK_WINDOW(window),pos);
	gtk_window_set_title (GTK_WINDOW(window),title);
	gtk_window_set_icon(GTK_WINDOW(window),gtk_image_get_pixbuf(GTK_IMAGE(icon)));
	return window ;
}



GtkWidget * createMenuBar(GtkWidget * textView,GtkWidget *mainWindow)
{
	GtkWidget *menuItem;
	GtkWidget *menuFile;
	GtkWidget *menuEdit;
	GtkWidget *menuHelp;
	GtkWidget *menuBar;


	menuBar			= gtk_menu_bar_new ();
	menuFile		= gtk_menu_new ();
	menuEdit		= gtk_menu_new ();
	menuHelp		= gtk_menu_new ();



	
	menuItem	= gtk_menu_item_new_with_label ("New");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuFile),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_new_clicked),(gpointer) textView);

	menuItem	= gtk_menu_item_new_with_label ("Open");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuFile),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_open_clicked ),(gpointer) textView);

	menuItem	= gtk_menu_item_new_with_label ("save");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuFile),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_save_clicked ),(gpointer) textView);

	menuItem	= gtk_menu_item_new_with_label ("Save as");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuFile),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_save_as_clicked ),(gpointer) textView);

	menuItem	= gtk_menu_item_new_with_label ("Quit");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuFile),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_quit_clicked),(gpointer) textView);

	menuItem	= gtk_menu_item_new_with_label ("File");
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(menuItem),menuFile);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuBar),menuItem);

	


	menuItem	= gtk_menu_item_new_with_label ("Copy");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_copy_clicked ),(gpointer) textView);

	menuItem	= gtk_menu_item_new_with_label ("Cut");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_cut_clicked ),(gpointer) textView);

	menuItem	= gtk_menu_item_new_with_label ("Paste");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_paste_clicked ),(gpointer) textView);

	menuItem	= gtk_menu_item_new_with_label ("Delete");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_delete_clicked ),(gpointer) textView);

	menuItem	= gtk_menu_item_new_with_label ("Select all");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_select_all_clicked ),(gpointer) textView);

	menuItem	= gtk_menu_item_new_with_label ("Deselect");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_deselect_clicked ),(gpointer) textView);

	menuItem	= gtk_menu_item_new_with_label ("Edit");
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(menuItem),menuEdit);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuBar),menuItem);


	

	menuItem	= gtk_menu_item_new_with_label ("About");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuHelp),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_about_clicked  ),(gpointer) mainWindow);

	menuItem	= gtk_menu_item_new_with_label ("help");
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(menuItem),menuHelp);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuBar),menuItem);


	
	return menuBar;

}



GtkWidget * createToolBar(GtkWidget * textView)
{
	GtkWidget *toolBar;
	GtkToolItem *btnNew,
				*btnOpen,
				*btnSave,
				*btnSaveAs,
				*btnCopy,
				*btnPaste,
				*btnCut,
				*btnDelete,
				*btnSelectAll,
				*separator;

	toolBar			= gtk_toolbar_new ();
	gtk_toolbar_set_tooltips(GTK_TOOLBAR(toolBar),TRUE);
	gtk_toolbar_set_style(GTK_TOOLBAR(toolBar),GTK_TOOLBAR_BOTH);
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(toolBar),GTK_ICON_SIZE_BUTTON);
	
	btnNew			= gtk_tool_button_new_from_stock (GTK_STOCK_NEW);
	btnOpen			= gtk_tool_button_new_from_stock (GTK_STOCK_OPEN);
	btnSave			= gtk_tool_button_new_from_stock (GTK_STOCK_SAVE);
	btnSaveAs		= gtk_tool_button_new_from_stock (GTK_STOCK_SAVE_AS);
	btnCopy			= gtk_tool_button_new_from_stock (GTK_STOCK_COPY);
	btnPaste		= gtk_tool_button_new_from_stock (GTK_STOCK_PASTE);
	btnCut			= gtk_tool_button_new_from_stock (GTK_STOCK_CUT);
	btnDelete		= gtk_tool_button_new_from_stock (GTK_STOCK_DELETE);
	btnSelectAll	= gtk_tool_button_new_from_stock (GTK_STOCK_SELECT_ALL);

	separator = gtk_separator_tool_item_new ();
	
	g_signal_connect(G_OBJECT(btnNew),"clicked",G_CALLBACK(menu_item_new_clicked),(gpointer) textView);
	g_signal_connect(G_OBJECT(btnOpen),"clicked",G_CALLBACK(menu_item_open_clicked),(gpointer) textView);
	g_signal_connect(G_OBJECT(btnSave),"clicked",G_CALLBACK(menu_item_save_clicked),(gpointer) textView);
	g_signal_connect(G_OBJECT(btnSaveAs),"clicked",G_CALLBACK(menu_item_save_as_clicked),(gpointer) textView);
	g_signal_connect(G_OBJECT(btnCopy),"clicked",G_CALLBACK(menu_item_copy_clicked),(gpointer) textView);
	g_signal_connect(G_OBJECT(btnPaste),"clicked",G_CALLBACK(menu_item_paste_clicked),(gpointer) textView);
	g_signal_connect(G_OBJECT(btnCut),"clicked",G_CALLBACK(menu_item_cut_clicked),(gpointer) textView);
	g_signal_connect(G_OBJECT(btnDelete),"clicked",G_CALLBACK(menu_item_delete_clicked),(gpointer) textView);
	g_signal_connect(G_OBJECT(btnSelectAll),"clicked",G_CALLBACK(menu_item_select_all_clicked),(gpointer) textView);

	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnNew,0);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnOpen,1);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnSave,2);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnSaveAs,3);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),separator,4);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnCut,5);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnCopy,6);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnPaste,7);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnDelete,8);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnSelectAll,9);
	

	                 
	return toolBar;
}



GtkWidget * createTextView(GtkWidget * statusBar){
	GtkWidget * textView;
	textView	= gtk_text_view_new ();
	gtk_text_view_set_accepts_tab (GTK_TEXT_VIEW(textView),TRUE);
	gtk_text_view_set_left_margin (GTK_TEXT_VIEW(textView),5);
	gtk_text_view_set_right_margin(GTK_TEXT_VIEW(textView),5);

	
	g_signal_connect(G_OBJECT(textView),"cut-clipboard",G_CALLBACK(textViewCut),(gpointer) statusBar);
	g_signal_connect(G_OBJECT(textView),"copy-clipboard",G_CALLBACK(textViewCopy),(gpointer) statusBar);
	g_signal_connect(G_OBJECT(textView),"paste-clipboard",G_CALLBACK(textViewPaste),(gpointer) statusBar);
	g_signal_connect(G_OBJECT(textView),"delete-from-cursor",G_CALLBACK(textViewDelete),(gpointer) statusBar);
	
	return textView;
}


GtkWidget * createStatusBar(void){
	GtkWidget *statusBar ;
	statusBar   = gtk_statusbar_new ();
	gtk_statusbar_set_has_resize_grip(GTK_STATUSBAR(statusBar),TRUE);

	
	return statusBar;
}

























