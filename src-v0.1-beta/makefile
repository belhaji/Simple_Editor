SimpleEditor 	: SimpleEditor.o main.o CallBack.o op.o
	gcc  -o simple_editor SimpleEditor.o main.o CallBack.o op.o settings.o `pkg-config --cflags --libs gtk+-2.0`

SimpleEditor.o 	: SimpleEditor.c
	gcc  -c SimpleEditor.c `pkg-config --cflags --libs gtk+-2.0`

main.o		: main.c
	gcc  -c main.c `pkg-config --cflags --libs gtk+-2.0`

settings.o	: settings.c
	gcc -c settings.c `pkg-config --cflags --libs gtk+-2.0`

CallBack.o  	: CallBack.c op.c
	gcc  -c CallBack.c `pkg-config --cflags --libs gtk+-2.0`

op.o		: op.c
	gcc  -c op.c `pkg-config --cflags --libs gtk+-2.0`

	
install		:
	mkdir -p /usr/share/simple_editor/
	cp -f icon.png /usr/share/simple_editor/
	cp -f simple_editor.desktop /usr/share/applications/
	mv -f simple_editor /usr/bin/
	echo -e '#!/bin/bash\nif [ `id -u` == 0 ]\n  then\n    rm -rf /usr/share/simple_editor /usr/bin/simple_editor /usr/bin/simple_editor_uninstall /usr/share/applications/simple_editor.desktop \n  echo "removed successfuly !"\nelse\n  echo "should be root to remove simple simple_editor"\nfi' > /usr/bin/simple_editor_uninstall
	chmod +x /usr/bin/simple_editor_uninstall

clean		:
	rm *.o 



