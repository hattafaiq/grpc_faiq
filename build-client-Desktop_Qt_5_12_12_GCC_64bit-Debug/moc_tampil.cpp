/****************************************************************************
** Meta object code from reading C++ file 'tampil.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../client/tampil.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tampil.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Tampil_t {
    QByteArrayData data[16];
    char stringdata0[259];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tampil_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tampil_t qt_meta_stringdata_Tampil = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Tampil"
QT_MOC_LITERAL(1, 7, 19), // "on_treeView_clicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 40, 5), // "index"
QT_MOC_LITERAL(5, 46, 20), // "on_treeView_expanded"
QT_MOC_LITERAL(6, 67, 21), // "on_treeView_activated"
QT_MOC_LITERAL(7, 89, 16), // "highlightChecked"
QT_MOC_LITERAL(8, 106, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(9, 123, 4), // "item"
QT_MOC_LITERAL(10, 128, 20), // "on_tableView_clicked"
QT_MOC_LITERAL(11, 149, 22), // "on_tableView_2_pressed"
QT_MOC_LITERAL(12, 172, 21), // "on_PB_connect_clicked"
QT_MOC_LITERAL(13, 194, 19), // "on_PB_kirim_clicked"
QT_MOC_LITERAL(14, 214, 21), // "on_PB_compare_clicked"
QT_MOC_LITERAL(15, 236, 22) // "on_PB_synchron_clicked"

    },
    "Tampil\0on_treeView_clicked\0\0QModelIndex\0"
    "index\0on_treeView_expanded\0"
    "on_treeView_activated\0highlightChecked\0"
    "QListWidgetItem*\0item\0on_tableView_clicked\0"
    "on_tableView_2_pressed\0on_PB_connect_clicked\0"
    "on_PB_kirim_clicked\0on_PB_compare_clicked\0"
    "on_PB_synchron_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tampil[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       5,    1,   67,    2, 0x0a /* Public */,
       6,    1,   70,    2, 0x0a /* Public */,
       7,    1,   73,    2, 0x0a /* Public */,
      10,    1,   76,    2, 0x08 /* Private */,
      11,    1,   79,    2, 0x08 /* Private */,
      12,    0,   82,    2, 0x08 /* Private */,
      13,    0,   83,    2, 0x08 /* Private */,
      14,    0,   84,    2, 0x08 /* Private */,
      15,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Tampil::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Tampil *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_treeView_clicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->on_treeView_expanded((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->on_treeView_activated((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: _t->highlightChecked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->on_tableView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->on_tableView_2_pressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->on_PB_connect_clicked(); break;
        case 7: _t->on_PB_kirim_clicked(); break;
        case 8: _t->on_PB_compare_clicked(); break;
        case 9: _t->on_PB_synchron_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Tampil::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_Tampil.data,
    qt_meta_data_Tampil,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Tampil::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tampil::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Tampil.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Tampil::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
