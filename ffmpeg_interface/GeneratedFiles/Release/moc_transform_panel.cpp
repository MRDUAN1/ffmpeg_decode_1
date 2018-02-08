/****************************************************************************
** Meta object code from reading C++ file 'transform_panel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../transform_panel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transform_panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_transform_panel_t {
    QByteArrayData data[13];
    char stringdata[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_transform_panel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_transform_panel_t qt_meta_stringdata_transform_panel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "transform_panel"
QT_MOC_LITERAL(1, 16, 7), // "ok_emit"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "combox_index"
QT_MOC_LITERAL(4, 38, 13), // "add_file_slot"
QT_MOC_LITERAL(5, 52, 15), // "clear_list_slot"
QT_MOC_LITERAL(6, 68, 13), // "ok_start_slot"
QT_MOC_LITERAL(7, 82, 16), // "out_setting_slot"
QT_MOC_LITERAL(8, 99, 11), // "change_slot"
QT_MOC_LITERAL(9, 111, 13), // "cut_part_slot"
QT_MOC_LITERAL(10, 125, 16), // "remove_list_slot"
QT_MOC_LITERAL(11, 142, 15), // "add_folder_slot"
QT_MOC_LITERAL(12, 158, 9) // "if_select"

    },
    "transform_panel\0ok_emit\0\0combox_index\0"
    "add_file_slot\0clear_list_slot\0"
    "ok_start_slot\0out_setting_slot\0"
    "change_slot\0cut_part_slot\0remove_list_slot\0"
    "add_folder_slot\0if_select"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_transform_panel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   70,    2, 0x0a /* Public */,
       4,    0,   73,    2, 0x0a /* Public */,
       5,    0,   74,    2, 0x0a /* Public */,
       6,    0,   75,    2, 0x0a /* Public */,
       7,    0,   76,    2, 0x0a /* Public */,
       8,    0,   77,    2, 0x0a /* Public */,
       9,    0,   78,    2, 0x0a /* Public */,
      10,    0,   79,    2, 0x0a /* Public */,
      11,    0,   80,    2, 0x0a /* Public */,
      12,    2,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

       0        // eod
};

void transform_panel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        transform_panel *_t = static_cast<transform_panel *>(_o);
        switch (_id) {
        case 0: _t->ok_emit(); break;
        case 1: _t->combox_index((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->add_file_slot(); break;
        case 3: _t->clear_list_slot(); break;
        case 4: _t->ok_start_slot(); break;
        case 5: _t->out_setting_slot(); break;
        case 6: _t->change_slot(); break;
        case 7: _t->cut_part_slot(); break;
        case 8: _t->remove_list_slot(); break;
        case 9: _t->add_folder_slot(); break;
        case 10: _t->if_select((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (transform_panel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&transform_panel::ok_emit)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject transform_panel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_transform_panel.data,
      qt_meta_data_transform_panel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *transform_panel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *transform_panel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_transform_panel.stringdata))
        return static_cast<void*>(const_cast< transform_panel*>(this));
    return QWidget::qt_metacast(_clname);
}

int transform_panel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void transform_panel::ok_emit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
