/****************************************************************************
** Meta object code from reading C++ file 'toolbox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../toolbox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'toolbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_toolbox_t {
    QByteArrayData data[13];
    char stringdata[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_toolbox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_toolbox_t qt_meta_stringdata_toolbox = {
    {
QT_MOC_LITERAL(0, 0, 7), // "toolbox"
QT_MOC_LITERAL(1, 8, 15), // "transform_audio"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "transform_video"
QT_MOC_LITERAL(4, 41, 17), // "transform_picture"
QT_MOC_LITERAL(5, 59, 20), // "init_map_button_list"
QT_MOC_LITERAL(6, 80, 14), // "separate_video"
QT_MOC_LITERAL(7, 95, 11), // "merge_video"
QT_MOC_LITERAL(8, 107, 12), // "merge_audio_"
QT_MOC_LITERAL(9, 120, 11), // "merge_music"
QT_MOC_LITERAL(10, 132, 9), // "cut_video"
QT_MOC_LITERAL(11, 142, 12), // "merge_videos"
QT_MOC_LITERAL(12, 155, 10) // "cut_video_"

    },
    "toolbox\0transform_audio\0\0transform_video\0"
    "transform_picture\0init_map_button_list\0"
    "separate_video\0merge_video\0merge_audio_\0"
    "merge_music\0cut_video\0merge_videos\0"
    "cut_video_"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_toolbox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void toolbox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        toolbox *_t = static_cast<toolbox *>(_o);
        switch (_id) {
        case 0: _t->transform_audio(); break;
        case 1: _t->transform_video(); break;
        case 2: _t->transform_picture(); break;
        case 3: _t->init_map_button_list(); break;
        case 4: _t->separate_video(); break;
        case 5: _t->merge_video(); break;
        case 6: _t->merge_audio_(); break;
        case 7: _t->merge_music(); break;
        case 8: _t->cut_video(); break;
        case 9: _t->merge_videos(); break;
        case 10: _t->cut_video_(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject toolbox::staticMetaObject = {
    { &QToolBox::staticMetaObject, qt_meta_stringdata_toolbox.data,
      qt_meta_data_toolbox,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *toolbox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *toolbox::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_toolbox.stringdata))
        return static_cast<void*>(const_cast< toolbox*>(this));
    return QToolBox::qt_metacast(_clname);
}

int toolbox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
