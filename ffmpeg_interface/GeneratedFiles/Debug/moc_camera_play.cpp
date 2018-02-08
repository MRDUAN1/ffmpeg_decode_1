/****************************************************************************
** Meta object code from reading C++ file 'camera_play.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../camera_play.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camera_play.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_camera_play_t {
    QByteArrayData data[6];
    char stringdata[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_camera_play_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_camera_play_t qt_meta_stringdata_camera_play = {
    {
QT_MOC_LITERAL(0, 0, 11), // "camera_play"
QT_MOC_LITERAL(1, 12, 9), // "cam_clear"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 14), // "choice_picture"
QT_MOC_LITERAL(4, 38, 21), // "handle_filter_changed"
QT_MOC_LITERAL(5, 60, 2) // "ok"

    },
    "camera_play\0cam_clear\0\0choice_picture\0"
    "handle_filter_changed\0ok"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_camera_play[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       5,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void camera_play::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        camera_play *_t = static_cast<camera_play *>(_o);
        switch (_id) {
        case 0: _t->cam_clear(); break;
        case 1: _t->choice_picture(); break;
        case 2: _t->handle_filter_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->ok(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (camera_play::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&camera_play::cam_clear)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject camera_play::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_camera_play.data,
      qt_meta_data_camera_play,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *camera_play::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *camera_play::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_camera_play.stringdata))
        return static_cast<void*>(const_cast< camera_play*>(this));
    return QWidget::qt_metacast(_clname);
}

int camera_play::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void camera_play::cam_clear()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
