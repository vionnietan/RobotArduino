/****************************************************************************
** Meta object code from reading C++ file 'qfirmata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/qfirmata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qfirmata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QFirmata_t {
    QByteArrayData data[17];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QFirmata_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QFirmata_t qt_meta_stringdata_QFirmata = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QFirmata"
QT_MOC_LITERAL(1, 9, 17), // "digitalPinChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 3), // "pin"
QT_MOC_LITERAL(4, 32, 16), // "analogPinChanged"
QT_MOC_LITERAL(5, 49, 13), // "sysExReceived"
QT_MOC_LITERAL(6, 63, 22), // "QVector<unsigned char>"
QT_MOC_LITERAL(7, 86, 7), // "message"
QT_MOC_LITERAL(8, 94, 23), // "protocolVersionReceived"
QT_MOC_LITERAL(9, 118, 12), // "majorVersion"
QT_MOC_LITERAL(10, 131, 12), // "minorVersion"
QT_MOC_LITERAL(11, 144, 20), // "firmwareNameReceived"
QT_MOC_LITERAL(12, 165, 12), // "firmwareName"
QT_MOC_LITERAL(13, 178, 23), // "firmwareVersionReceived"
QT_MOC_LITERAL(14, 202, 11), // "initialized"
QT_MOC_LITERAL(15, 214, 14), // "stringReceived"
QT_MOC_LITERAL(16, 229, 8) // "readData"

    },
    "QFirmata\0digitalPinChanged\0\0pin\0"
    "analogPinChanged\0sysExReceived\0"
    "QVector<unsigned char>\0message\0"
    "protocolVersionReceived\0majorVersion\0"
    "minorVersion\0firmwareNameReceived\0"
    "firmwareName\0firmwareVersionReceived\0"
    "initialized\0stringReceived\0readData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QFirmata[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       5,    1,   65,    2, 0x06 /* Public */,
       8,    2,   68,    2, 0x06 /* Public */,
      11,    1,   73,    2, 0x06 /* Public */,
      13,    2,   76,    2, 0x06 /* Public */,
      14,    3,   81,    2, 0x06 /* Public */,
      15,    1,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,    9,   10,   12,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void QFirmata::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QFirmata *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->digitalPinChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->analogPinChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->sysExReceived((*reinterpret_cast< const QVector<unsigned char>(*)>(_a[1]))); break;
        case 3: _t->protocolVersionReceived((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 4: _t->firmwareNameReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->firmwareVersionReceived((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 6: _t->initialized((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: _t->stringReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->readData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<unsigned char> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QFirmata::*)(const int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QFirmata::digitalPinChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QFirmata::*)(const int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QFirmata::analogPinChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QFirmata::*)(const QVector<unsigned char> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QFirmata::sysExReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QFirmata::*)(const int , const int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QFirmata::protocolVersionReceived)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QFirmata::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QFirmata::firmwareNameReceived)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QFirmata::*)(const int , const int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QFirmata::firmwareVersionReceived)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QFirmata::*)(const int , const int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QFirmata::initialized)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (QFirmata::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QFirmata::stringReceived)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QFirmata::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_QFirmata.data,
    qt_meta_data_QFirmata,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QFirmata::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QFirmata::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QFirmata.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QFirmata::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QFirmata::digitalPinChanged(const int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QFirmata::analogPinChanged(const int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QFirmata::sysExReceived(const QVector<unsigned char> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QFirmata::protocolVersionReceived(const int _t1, const int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QFirmata::firmwareNameReceived(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QFirmata::firmwareVersionReceived(const int _t1, const int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QFirmata::initialized(const int _t1, const int _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QFirmata::stringReceived(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
