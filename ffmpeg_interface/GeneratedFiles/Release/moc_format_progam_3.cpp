/****************************************************************************
** Meta object code from reading C++ file 'format_progam_3.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../format_progam_3.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'format_progam_3.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_format_progam_3_t {
    QByteArrayData data[17];
    char stringdata[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_format_progam_3_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_format_progam_3_t qt_meta_stringdata_format_progam_3 = {
    {
QT_MOC_LITERAL(0, 0, 15), // "format_progam_3"
QT_MOC_LITERAL(1, 16, 10), // "caption_ok"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 17), // "line_caption_slot"
QT_MOC_LITERAL(4, 46, 8), // "is_check"
QT_MOC_LITERAL(5, 55, 9), // "dealer_ok"
QT_MOC_LITERAL(6, 65, 21), // "handle_filter_changed"
QT_MOC_LITERAL(7, 87, 9), // "save_jpeg"
QT_MOC_LITERAL(8, 97, 17), // "start_edit_finish"
QT_MOC_LITERAL(9, 115, 15), // "end_edit_finish"
QT_MOC_LITERAL(10, 131, 12), // "suspend_play"
QT_MOC_LITERAL(11, 144, 9), // "slow_play"
QT_MOC_LITERAL(12, 154, 9), // "fast_play"
QT_MOC_LITERAL(13, 164, 13), // "slider_change"
QT_MOC_LITERAL(14, 178, 3), // "num"
QT_MOC_LITERAL(15, 182, 13), // "update_slider"
QT_MOC_LITERAL(16, 196, 6) // "breaks"

    },
    "format_progam_3\0caption_ok\0\0"
    "line_caption_slot\0is_check\0dealer_ok\0"
    "handle_filter_changed\0save_jpeg\0"
    "start_edit_finish\0end_edit_finish\0"
    "suspend_play\0slow_play\0fast_play\0"
    "slider_change\0num\0update_slider\0breaks"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_format_progam_3[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    1,   88,    2, 0x0a /* Public */,
       7,    0,   91,    2, 0x0a /* Public */,
       8,    0,   92,    2, 0x0a /* Public */,
       9,    0,   93,    2, 0x0a /* Public */,
      10,    0,   94,    2, 0x0a /* Public */,
      11,    0,   95,    2, 0x0a /* Public */,
      12,    0,   96,    2, 0x0a /* Public */,
      13,    1,   97,    2, 0x0a /* Public */,
      15,    0,  100,    2, 0x0a /* Public */,
      16,    0,  101,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void format_progam_3::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        format_progam_3 *_t = static_cast<format_progam_3 *>(_o);
        switch (_id) {
        case 0: _t->caption_ok(); break;
        case 1: _t->line_caption_slot(); break;
        case 2: _t->is_check(); break;
        case 3: _t->dealer_ok(); break;
        case 4: _t->handle_filter_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->save_jpeg(); break;
        case 6: _t->start_edit_finish(); break;
        case 7: _t->end_edit_finish(); break;
        case 8: _t->suspend_play(); break;
        case 9: _t->slow_play(); break;
        case 10: _t->fast_play(); break;
        case 11: _t->slider_change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->update_slider(); break;
        case 13: _t->breaks(); break;
        default: ;
        }
    }
}

const QMetaObject format_progam_3::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_format_progam_3.data,
      qt_meta_data_format_progam_3,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *format_progam_3::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *format_progam_3::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_format_progam_3.stringdata))
        return static_cast<void*>(const_cast< format_progam_3*>(this));
    return QWidget::qt_metacast(_clname);
}

int format_progam_3::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
