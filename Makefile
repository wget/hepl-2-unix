.SILENT:
# If we define in the current directory a file named clean or mrproper, this
# will break this makefile as these target do not have any dependencies, the
# target will always be more recent and will never be evaluated. The PHONY
# directive avoids this issue.
.PHONY: clean mrproper

CC		= g++
CFLAGS	= -W -Wall -march=x86-64 -mtune=generic -O2 -pipe -fPIC -I/usr/include/qt/QtCore -I/usr/include/qt/QtWidgets -I/usr/include/qt/ -I/usr/include -I.
LDFLAGS	= -I. -isystem /usr/include/qt -isystem /usr/include/qt/QtWidgets -isystem /usr/include/qt/QtGui -isystem /usr/include/qt/QtCore -I/usr/lib/qt/mkspecs/linux-g++ -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread


all: vehicle manager server path_finder

# Instead of repeating dependencies over and over again, make does support the
# following shortcuts. These also allow to avoid burden when we want to change
# the destination name of executables/targets for example.
#$@ : Target name;
#$< : First dependency;
#$? : More recent dependencies than the target;
#$^ : All the dependencies;
#$* : All wildcard character, same as * but syntax interpreted by make
vehicle: vehicle.o vehicle_main.o vehicle_moc.o screen.o
	echo "[+] Creating vehicle executable"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

vehicle.o: vehicle_ui.h
	echo "[+] Building vehicle.o"
	$(CC) -c $(CFLAGS) -o $@ vehicle.cpp

vehicle_ui.h: vehicle.ui
	echo "[+] Building vehicle_ui.h"
	uic -o vehicle_ui.h vehicle.ui

vehicle_main.o:
	echo "[+] Building vehicle_main.o"
	$(CC) -c $(CFLAGS) -o $@ vehicle_main.cpp

vehicle_moc.o: vehicle.h
	echo "[+] Building vehicle_moc.o"
	moc -o vehicle_moc.cpp vehicle.h
	$(CC) -c $(CFLAGS) -o $@ vehicle_moc.cpp

manager: manager.o manager_main.o manager_moc.o screen.o
	echo "[+] Creating manager executable"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

manager.o: manager_ui.h
	echo "[+] Building manager.o"
	$(CC) -c $(CFLAGS) -o $@ manager.cpp

manager_ui.h: manager.ui
	echo "[+] Building manager_ui.h"
	uic -o manager_ui.h manager.ui

manager_main.o:
	echo "[+] Building manager_main.o"
	$(CC) -c $(CFLAGS) -o $@ manager_main.cpp

manager_moc.o:
	echo "[+] Building manager_moc.o"
	moc -o manager_moc.cpp manager.h
	$(CC) -c $(CFLAGS) -o $@ manager_moc.cpp

screen.o:
	echo "[+] Building screen.o"
	$(CC) -c $(CFLAGS) screen.cpp 

server: screen.o
	echo "[+] Creating server executable"
	$(CC) $(CFLAGS) -o $@ server.cpp $^

path_finder: screen.o
	echo "[+] Creating path_finder executable"
	$(CC) $(CFLAGS) -o $@ path_finder.cpp $^

clean:
	rm -fv *.o

mrproper: clean
	rm -fv vehicle manager server path_finder *ui.h *moc.cpp
