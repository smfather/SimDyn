/****************************************************************************
** Meta object code from reading C++ file 'simdyn.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Include/simdyn.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simdyn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SimDyn_t {
    QByteArrayData data[6];
    char stringdata[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimDyn_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimDyn_t qt_meta_stringdata_SimDyn = {
    {
QT_MOC_LITERAL(0, 0, 6), // "SimDyn"
QT_MOC_LITERAL(1, 7, 8), // "onNewDoc"
QT_MOC_LITERAL(2, 16, 15), // "DocumentCommon*"
QT_MOC_LITERAL(3, 32, 0), // ""
QT_MOC_LITERAL(4, 33, 13), // "onCloseWindow"
QT_MOC_LITERAL(5, 47, 18) // "onSelectionChanged"

    },
    "SimDyn\0onNewDoc\0DocumentCommon*\0\0"
    "onCloseWindow\0onSelectionChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimDyn[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    3, 0x08 /* Private */,
       4,    0,   30,    3, 0x08 /* Private */,
       5,    0,   31,    3, 0x0a /* Public */,

 // slots: parameters
    0x80000000 | 2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SimDyn::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SimDyn *_t = static_cast<SimDyn *>(_o);
        switch (_id) {
        case 0: { DocumentCommon* _r = _t->onNewDoc();
            if (_a[0]) *reinterpret_cast< DocumentCommon**>(_a[0]) = _r; }  break;
        case 1: _t->onCloseWindow(); break;
        case 2: _t->onSelectionChanged(); break;
        default: ;
        }
    }
}

const QMetaObject SimDyn::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SimDyn.data,
      qt_meta_data_SimDyn,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SimDyn::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimDyn::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SimDyn.stringdata))
        return static_cast<void*>(const_cast< SimDyn*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SimDyn::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
