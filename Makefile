.SILENT:
# If we define in the current directory a file named clean or mrproper, this
# will break this makefile as these target do not have any dependencies, the
# target will always be more recent and will never be evaluated. The PHONY
# directive avoids this issue.
.PHONY: clean mrproper

CC		= g++
CFLAGS	= -W -Wall -march=x86-64 -mtune=generic -O2 -pipe -fPIC -I/usr/include/qt/QtCore -I/usr/include/qt/QtWidgets -I/usr/include/qt/ -I/usr/include -I.
LDFLAGS	= -I. -isystem /usr/include/qt -isystem /usr/include/qt/QtWidgets -isystem /usr/include/qt/QtGui -isystem /usr/include/qt/QtCore -I/usr/lib/qt/mkspecs/linux-g++ -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread


all: Vehicule Controle Serveur RechercheChemin

# Instead of repeating dependencies over and over again, make does support the
# following shortcuts. These also allow to avoid burden when we want to change
# the destination name of executables/targets for example.
#$@ : Target name;
#$< : First dependency;
#$? : More recent dependencies than the target;
#$^ : All the dependencies;
#$* : All wildcard character, same as * but syntax interpreted by make
Vehicule: mainVehicule.o vehicule.o moc_vehicule.o Ecran.o
	echo "[+] Creating Vehicule executable"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

mainVehicule.o:
	echo "[+] Building mainVehicule.o"
	$(CC) -c $(CFLAGS) -o $@ mainVehicule.cpp

vehicule.o:
	echo "[+] Building vehicule.o"
	$(CC) -c $(CFLAGS) -o $@ vehicule.cpp

moc_vehicule.o: vehicule.h
	echo "[+] Building moc_vehicule.o"
	moc -o moc_vehicule.cpp vehicule.h
	$(CC) -c $(CFLAGS) -o $@ moc_vehicule.cpp

Controle: controle.o mainControle.o moc_controle.o Ecran.o
	echo "[+] Creating Controle executable"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

controle.o:
	echo "[+] Building controle.o"
	$(CC) -c $(CFLAGS) -o $@ controle.cpp

mainControle.o:
	echo "[+] Building mainControle.o"
	$(CC) -c $(CFLAGS) -o $@ mainControle.cpp

moc_controle.o:
	echo "[+] Building moc_controle.o"
	moc -o moc_controle.cpp controle.h
	$(CC) -c $(CFLAGS) -o $@ moc_controle.cpp

Ecran.o:
	echo "[+] Building Ecran.o"
	$(CC) -c $(CFLAGS) Ecran.cpp 

Serveur: Ecran.o
	echo "[+] Creating Serveur executable"
	$(CC) $(CFLAGS) -o $@ Serveur.cpp $^

RechercheChemin: Ecran.o
	echo "[+] Creating RechercheChemin executable"
	$(CC) $(CFLAGS) -o $@ RechercheChemin.cpp $^

clean:
	rm -fv *.o

mrproper: clean
	rm -fv Vehicule Controle Serveur RechercheChemin
