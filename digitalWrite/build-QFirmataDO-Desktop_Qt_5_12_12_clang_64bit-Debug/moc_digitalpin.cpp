/****************************************************************************
** Meta object code from reading C++ file 'digitalpin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QFirmataDO/digitalpin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'digitalpin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DigitalPin_t {
    QByteArrayData data[11];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DigitalPin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DigitalPin_t qt_meta_stringdata_DigitalPin = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DigitalPin"
QT_MOC_LITERAL(1, 11, 14), // "pinModeChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "pin"
QT_MOC_LITERAL(4, 31, 4), // "mode"
QT_MOC_LITERAL(5, 36, 12), // "valueChanged"
QT_MOC_LITERAL(6, 49, 5), // "value"
QT_MOC_LITERAL(7, 55, 3), // "pwm"
QT_MOC_LITERAL(8, 59, 16), // "onPinModeChanged"
QT_MOC_LITERAL(9, 76, 14), // "onValueChanged"
QT_MOC_LITERAL(10, 91, 7) // "setMode"

    },
    "DigitalPin\0pinModeChanged\0\0pin\0mode\0"
    "valueChanged\0value\0pwm\0onPinModeChanged\0"
    "onValueChanged\0setMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DigitalPin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       5,    3,   49,    2, 0x06 /* Public */,
       5,    2,   56,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   61,    2, 0x08 /* Private */,
       9,    1,   64,    2, 0x08 /* Private */,
      10,    1,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::Bool,    3,    6,    7,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,    3,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void DigitalPin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DigitalPin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pinModeChanged((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->valueChanged((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->valueChanged((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 3: _t->onPinModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DigitalPin::*)(unsigned int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DigitalPin::pinModeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DigitalPin::*)(unsigned int , unsigned int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DigitalPin::valueChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DigitalPin::staticMetaObject = { {
    &Pin::staticMetaObject,
    qt_meta_stringdata_DigitalPin.data,
    qt_meta_data_DigitalPin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DigitalPin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DigitalPin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DigitalPin.stringdata0))
        return static_cast<void*>(this);
    return Pin::qt_metacast(_clname);
}

int DigitalPin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Pin::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void DigitalPin::pinModeChanged(unsigned int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DigitalPin::valueChanged(unsigned int _t1, unsigned int _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
