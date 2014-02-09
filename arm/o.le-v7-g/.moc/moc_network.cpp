/****************************************************************************
** Meta object code from reading C++ file 'network.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/network.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NetworkBus[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
      11,   39, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   29,   11,   11, 0x0a,
      87,   69,   11,   11, 0x0a,
     130,  122,   11,   11, 0x0a,
     156,  150,   11,   11, 0x0a,

 // properties: name, type, flags
     183,  175, 0x0a495001,
     195,  175, 0x0a495001,
     205,  175, 0x0a495001,
     216,  175, 0x0a495001,
     225,  175, 0x0a495001,
     239,  175, 0x0a495001,
     251,  175, 0x0a495001,
     261,  257, 0x02495001,
     268,  257, 0x02495001,
     272,  175, 0x0a495001,
     287,  175, 0x0a495001,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,

       0        // eod
};

static const char qt_meta_stringdata_NetworkBus[] = {
    "NetworkBus\0\0buslineChanged()\0reply\0"
    "onBusLineFinished(QNetworkReply*)\0"
    "city_id,line_name\0get_lines_by_city(QString,QString)\0"
    "newCity\0changeCity(QString)\0m_dir\0"
    "changeBusLine(int)\0QString\0buslineText\0"
    "line_name\0begin_time\0end_time\0"
    "start_station\0end_station\0price\0int\0"
    "isOpen\0dir\0to_station_one\0to_station_two\0"
};

void NetworkBus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NetworkBus *_t = static_cast<NetworkBus *>(_o);
        switch (_id) {
        case 0: _t->buslineChanged(); break;
        case 1: _t->onBusLineFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->get_lines_by_city((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->changeCity((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->changeBusLine((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NetworkBus::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NetworkBus::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NetworkBus,
      qt_meta_data_NetworkBus, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NetworkBus::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NetworkBus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NetworkBus::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkBus))
        return static_cast<void*>(const_cast< NetworkBus*>(this));
    return QObject::qt_metacast(_clname);
}

int NetworkBus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = buslineText(); break;
        case 1: *reinterpret_cast< QString*>(_v) = line_name(); break;
        case 2: *reinterpret_cast< QString*>(_v) = begin_time(); break;
        case 3: *reinterpret_cast< QString*>(_v) = end_time(); break;
        case 4: *reinterpret_cast< QString*>(_v) = start_station(); break;
        case 5: *reinterpret_cast< QString*>(_v) = end_station(); break;
        case 6: *reinterpret_cast< QString*>(_v) = price(); break;
        case 7: *reinterpret_cast< int*>(_v) = isOpen(); break;
        case 8: *reinterpret_cast< int*>(_v) = dir(); break;
        case 9: *reinterpret_cast< QString*>(_v) = to_station_one(); break;
        case 10: *reinterpret_cast< QString*>(_v) = to_station_two(); break;
        }
        _id -= 11;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 11;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 11;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void NetworkBus::buslineChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
