/****************************************************************************
** Meta object code from reading C++ file 'merge_gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../merge_gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'merge_gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_merge_gui_t {
    QByteArrayData data[6];
    char stringdata[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_merge_gui_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_merge_gui_t qt_meta_stringdata_merge_gui = {
    {
QT_MOC_LITERAL(0, 0, 9), // "merge_gui"
QT_MOC_LITERAL(1, 10, 10), // "video_slot"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 10), // "audio_slot"
QT_MOC_LITERAL(4, 33, 2), // "ok"
QT_MOC_LITERAL(5, 36, 6) // "cancel"

    },
    "merge_gui\0video_slot\0\0audio_slot\0ok\0"
    "cancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_merge_gui[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void merge_gui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        merge_gui *_t = static_cast<merge_gui *>(_o);
        switch (_id) {
        case 0: _t->video_slot(); break;
        case 1: _t->audio_slot(); break;
        case 2: _t->ok(); break;
        case 3: _t->cancel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject merge_gui::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_merge_gui.data,
      qt_meta_data_merge_gui,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *merge_gui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *merge_gui::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_merge_gui.stringdata))
        return static_cast<void*>(const_cast< merge_gui*>(this));
    return QWidget::qt_metacast(_clname);
}

int merge_gui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
