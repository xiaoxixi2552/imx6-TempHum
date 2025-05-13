/****************************************************************************
** Meta object code from reading C++ file 'tempmodule.hpp'
**
** Created: Sun May 21 21:25:59 2017
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tempmodule.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tempmodule.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TempModule[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TempModule[] = {
    "TempModule\0\0onDeactivate()\0"
};

const QMetaObject TempModule::staticMetaObject = {
    { &Module::staticMetaObject, qt_meta_stringdata_TempModule,
      qt_meta_data_TempModule, 0 }
};

const QMetaObject *TempModule::metaObject() const
{
    return &staticMetaObject;
}

void *TempModule::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TempModule))
        return static_cast<void*>(const_cast< TempModule*>(this));
    return Module::qt_metacast(_clname);
}

int TempModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Module::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onDeactivate(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
