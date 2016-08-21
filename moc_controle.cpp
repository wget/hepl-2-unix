/****************************************************************************
** Meta object code from reading C++ file 'controle.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "controle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Controle_t {
    QByteArrayData data[11];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Controle_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Controle_t qt_meta_stringdata_Controle = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Controle"
QT_MOC_LITERAL(1, 9, 29), // "on_BouttonEnregistrer_clicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 25), // "on_BouttonFacture_clicked"
QT_MOC_LITERAL(4, 66, 29), // "on_BouttonTransmettre_clicked"
QT_MOC_LITERAL(5, 96, 26), // "on_BouttonTerminer_clicked"
QT_MOC_LITERAL(6, 123, 12), // "TraceTroncon"
QT_MOC_LITERAL(7, 136, 9), // "QPainter*"
QT_MOC_LITERAL(8, 146, 10), // "paintEvent"
QT_MOC_LITERAL(9, 157, 12), // "QPaintEvent*"
QT_MOC_LITERAL(10, 170, 5) // "event"

    },
    "Controle\0on_BouttonEnregistrer_clicked\0"
    "\0on_BouttonFacture_clicked\0"
    "on_BouttonTransmettre_clicked\0"
    "on_BouttonTerminer_clicked\0TraceTroncon\0"
    "QPainter*\0paintEvent\0QPaintEvent*\0"
    "event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Controle[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    3,   48,    2, 0x08 /* Private */,
       8,    1,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void Controle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Controle *_t = static_cast<Controle *>(_o);
        Q_UNUSED(_t)
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

const QMetaObject Controle::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Controle.data,
      qt_meta_data_Controle,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Controle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Controle::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Controle.stringdata0))
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
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
