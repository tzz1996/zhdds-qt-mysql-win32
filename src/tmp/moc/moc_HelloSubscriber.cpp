/****************************************************************************
** Meta object code from reading C++ file 'HelloSubscriber.h'
**
** Created: Mon May 3 00:38:15 2021
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../HelloSubscriber.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HelloSubscriber.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HelloListener[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   15,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_HelloListener[] = {
    "HelloListener\0\0dataSeq\0send_msg(HelloWorldSeq)\0"
};

void HelloListener::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HelloListener *_t = static_cast<HelloListener *>(_o);
        switch (_id) {
        case 0: _t->send_msg((*reinterpret_cast< HelloWorldSeq(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData HelloListener::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject HelloListener::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HelloListener,
      qt_meta_data_HelloListener, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HelloListener::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HelloListener::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HelloListener::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HelloListener))
        return static_cast<void*>(const_cast< HelloListener*>(this));
    if (!strcmp(_clname, "DDSDataReaderListener"))
        return static_cast< DDSDataReaderListener*>(const_cast< HelloListener*>(this));
    return QObject::qt_metacast(_clname);
}

int HelloListener::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void HelloListener::send_msg(HelloWorldSeq _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
