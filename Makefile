.SILENT:
# If we define in the current directory a file named clean or mrproper, this
# will break this makefile as these target do not have any dependencies, the
# target will always be more recent and will never be evaluated. The PHONY
# directive avoids this issue.
.PHONY: clean mrproper

CC		= g++
CFLAGS	= -W -Wall -march=x86-64 -mtune=generic -O2 -pipe -fPIC -I/usr/include/qt/QtCore -I/usr/include/qt/QtWidgets -I/usr/include/qt/ -I/usr/include -I.
LDFLAGS	= -I. -isystem /usr/include/qt -isystem /usr/include/qt/QtWidgets -isystem /usr/include/qt/QtGui -isystem /usr/include/qt/QtCore -I/usr/lib/qt/mkspecs/linux-g++ -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread


all: Vehicle Manager Server PathFinder

# Instead of repeating dependencies over and over again, make does support the
# following shortcuts. These also allow to avoid burden when we want to change
# the destination name of executables/targets for example.
#$@ : Target name;
#$< : First dependency;
#$? : More recent dependencies than the target;
#$^ : All the dependencies;
#$* : All wildcard character, same as * but syntax interpreted by make
Vehicle: mainVehicle.o vehicule.o moc_vehicle.o Screen.o
	echo "[+] Creating Vehicle executable"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

mainVehicle.o:
	echo "[+] Building mainVehicle.o"
	$(CC) -c $(CFLAGS) -o $@ mainVehicle.cpp

vehicule.o:
	echo "[+] Building vehicule.o"
	$(CC) -c $(CFLAGS) -o $@ vehicule.cpp

moc_vehicle.o: vehicule.h
	echo "[+] Building moc_vehicle.o"
	moc -o moc_vehicle.cpp vehicule.h
	$(CC) -c $(CFLAGS) -o $@ moc_vehicle.cpp

Manager: manager.o mainManager.o moc_manager.o Screen.o
	echo "[+] Creating Manager executable"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

manager.o:
	echo "[+] Building manager.o"
	$(CC) -c $(CFLAGS) -o $@ manager.cpp

mainManager.o:
	echo "[+] Building mainManager.o"
	$(CC) -c $(CFLAGS) -o $@ mainManager.cpp

moc_manager.o:
	echo "[+] Building moc_manager.o"
	moc -o moc_manager.cpp manager.h
	$(CC) -c $(CFLAGS) -o $@ moc_manager.cpp

Screen.o:
	echo "[+] Building Screen.o"
	$(CC) -c $(CFLAGS) Screen.cpp 

Server: Screen.o
	echo "[+] Creating Server executable"
	$(CC) $(CFLAGS) -o $@ Server.cpp $^

PathFinder: Screen.o
	echo "[+] Creating PathFinder executable"
	$(CC) $(CFLAGS) -o $@ PathFinder.cpp $^

clean:
	rm -fv *.o

mrproper: clean
	rm -fv Vehicle Manager Server PathFinder
