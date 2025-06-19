/****************************************************************************
** Meta object code from reading C++ file 'ausgabetabelle.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ausgabetabelle.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ausgabetabelle.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_ausgabetabelle_t {
    uint offsetsAndSizes[14];
    char stringdata0[15];
    char stringdata1[26];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[17];
    char stringdata5[5];
    char stringdata6[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ausgabetabelle_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ausgabetabelle_t qt_meta_stringdata_ausgabetabelle = {
    {
        QT_MOC_LITERAL(0, 14),  // "ausgabetabelle"
        QT_MOC_LITERAL(15, 25),  // "loescheAusgewaehlteZeilen"
        QT_MOC_LITERAL(41, 0),  // ""
        QT_MOC_LITERAL(42, 18),  // "oeffneNeuesFenster"
        QT_MOC_LITERAL(61, 16),  // "fuegePersonHinzu"
        QT_MOC_LITERAL(78, 4),  // "name"
        QT_MOC_LITERAL(83, 5)   // "alter"
    },
    "ausgabetabelle",
    "loescheAusgewaehlteZeilen",
    "",
    "oeffneNeuesFenster",
    "fuegePersonHinzu",
    "name",
    "alter"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ausgabetabelle[] = {

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
       3,    0,   33,    2, 0x08,    2 /* Private */,
       4,    2,   34,    2, 0x08,    3 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    5,    6,

       0        // eod
};

Q_CONSTINIT const QMetaObject ausgabetabelle::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ausgabetabelle.offsetsAndSizes,
    qt_meta_data_ausgabetabelle,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ausgabetabelle_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ausgabetabelle, std::true_type>,
        // method 'loescheAusgewaehlteZeilen'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'oeffneNeuesFenster'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fuegePersonHinzu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void ausgabetabelle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ausgabetabelle *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->loescheAusgewaehlteZeilen(); break;
        case 1: _t->oeffneNeuesFenster(); break;
        case 2: _t->fuegePersonHinzu((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *ausgabetabelle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ausgabetabelle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ausgabetabelle.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ausgabetabelle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
