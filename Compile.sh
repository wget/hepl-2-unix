#/usr/bin/bash

# CFLAGS="-W -Wall -march=x86-64 -mtune=generic -O2 -pipe -fPIC -I/usr/include/qt/QtCore -I/usr/include/qt/QtWidgets -I/usr/include/qt/ -I. -I/usr/include"

echo "Ecran"
g++ -c $FLAGS Ecran.cpp 

echo "mainVehicule"
g++ -c $CFLAGS -o mainVehicule.o mainVehicule.cpp
echo "vehicule"
g++ -c $CFLAGS -o vehicule.o vehicule.cpp

# update moc
echo "update moc"
moc -o moc_vehicule.cpp vehicule.h
echo "moc_vehicule"
g++ -c $CFLAGS -o moc_vehicule.o moc_vehicule.cpp

echo "echo linking"
g++ $CFLAGS $LDFLAGS -o Vehicule mainVehicule.o  vehicule.o  moc_vehicule.o Ecran.o

echo "controle"
g++ -c $CFLAGS -o controle.o controle.cpp
g++ -c $CFLAGS -o mainControle.o mainControle.cpp

echo "update moc"
moc -o moc_controle.cpp controle.h
g++ -c $CFLAGS -o moc_controle.o moc_controle.cpp
g++ $CFLAGS $LDFLAGS -o Controle controle.o  mainControle.o  moc_controle.o Ecran.o

echo "serveur"
g++ $CFLAGS -o Serveur Serveur.cpp Ecran.o
echo "recherche chemin"
g++ $CFLAGS -o RechercheChemin RechercheChemin.cpp Ecran.o

exit


