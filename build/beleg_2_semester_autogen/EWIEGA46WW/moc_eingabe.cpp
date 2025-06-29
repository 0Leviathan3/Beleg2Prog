/****************************************************************************
** Meta object code from reading C++ file 'eingabe.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../eingabe.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eingabe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_eingabe_t {
    uint offsetsAndSizes[18];
    char stringdata0[8];
    char stringdata1[26];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[6];
    char stringdata5[7];
    char stringdata6[3];
    char stringdata7[4];
    char stringdata8[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_eingabe_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_eingabe_t qt_meta_stringdata_eingabe = {
    {
        QT_MOC_LITERAL(0, 7),  // "eingabe"
        QT_MOC_LITERAL(8, 25),  // "loescheAusgewaehlteZeilen"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 16),  // "fuegeMediumHinzu"
        QT_MOC_LITERAL(52, 5),  // "titel"
        QT_MOC_LITERAL(58, 6),  // "person"
        QT_MOC_LITERAL(65, 2),  // "id"
        QT_MOC_LITERAL(68, 3),  // "typ"
        QT_MOC_LITERAL(72, 15)   // "speichereMedien"
    },
    "eingabe",
    "loescheAusgewaehlteZeilen",
    "",
    "fuegeMediumHinzu",
    "titel",
    "person",
    "id",
    "typ",
    "speichereMedien"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_eingabe[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x08,    1 /* Private */,
       3,    4,   33,    2, 0x08,    2 /* Private */,
       8,    0,   42,    2, 0x08,    7 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,    5,    6,    7,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject eingabe::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_eingabe.offsetsAndSizes,
    qt_meta_data_eingabe,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_eingabe_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<eingabe, std::true_type>,
        // method 'loescheAusgewaehlteZeilen'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fuegeMediumHinzu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'speichereMedien'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void eingabe::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<eingabe *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->loescheAusgewaehlteZeilen(); break;
        case 1: _t->fuegeMediumHinzu((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 2: _t->speichereMedien(); break;
        default: ;
        }
    }
}

const QMetaObject *eingabe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *eingabe::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_eingabe.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int eingabe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
