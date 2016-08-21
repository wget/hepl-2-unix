/****************************************************************************
** Meta object code from reading C++ file 'controle.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "controle.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Controle[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      42,    9,    9,    9, 0x08,
      70,    9,    9,    9, 0x08,
     102,    9,    9,    9, 0x08,
     134,  131,    9,    9, 0x08,
     172,  166,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Controle[] = {
    "Controle\0\0on_BouttonEnregistrer_clicked()\0"
    "on_BouttonFacture_clicked()\0"
    "on_BouttonTransmettre_clicked()\0"
    "on_BouttonTerminer_clicked()\0,,\0"
    "TraceTroncon(QPainter*,int,int)\0event\0"
    "paintEvent(QPaintEvent*)\0"
};

void Controle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Controle *_t = static_cast<Controle *>(_o);
        switch (_id) {
        case 0: _t->on_BouttonEnregistrer_clicked(); break;
        case 1: _t->on_BouttonFacture_clicked(); break;
        case 2: _t->on_BouttonTransmettre_clicked(); break;
        case 3: _t->on_BouttonTerminer_clicked(); break;
        case 4: _t->TraceTroncon((*reinterpret_cast< QPainter*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Controle::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Controle::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Controle,
      qt_meta_data_Controle, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Controle::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Controle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Controle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Controle))
        return static_cast<void*>(const_cast< Controle*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Controle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
