/****************************************************************************
** Meta object code from reading C++ file 'combysocket.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../combysocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'combysocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_comBySocket[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      22,   12,   12,   12, 0x0a,
      31,   12,   12,   12, 0x0a,
      41,   12,   12,   12, 0x0a,
      57,   12,   12,   12, 0x0a,
      81,   76,   12,   12, 0x0a,
      96,   12,   12,   12, 0x0a,
     106,   12,   12,   12, 0x0a,
     117,   12,   12,   12, 0x0a,
     125,   12,   12,   12, 0x0a,
     137,   12,   12,   12, 0x0a,
     158,  152,   12,   12, 0x0a,
     179,   12,   12,   12, 0x0a,
     208,  196,   12,   12, 0x0a,
     272,  259,  254,   12, 0x0a,
     307,  302,  254,   12, 0x0a,
     356,  348,  340,   12, 0x0a,
     387,  381,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_comBySocket[] = {
    "comBySocket\0\0setCom()\0getCom()\0sendCom()\0"
    "connectServer()\0disconnectServer()\0"
    "type\0doProcess(int)\0inClear()\0outClear()\0"
    "blain()\0connected()\0disconnected()\0"
    "bytes\0bytesWritten(qint64)\0readFromServer()\0"
    "socketError\0displayTcpError(QAbstractSocket::SocketError)\0"
    "bool\0target,event\0eventFilter(QObject*,QEvent*)\0"
    "vbuf\0sendData(vector<unsigned char>&)\0"
    "QString\0subRead\0backDataConvent(QString)\0"
    "color\0setForntColor(int)\0"
};

void comBySocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        comBySocket *_t = static_cast<comBySocket *>(_o);
        switch (_id) {
        case 0: _t->setCom(); break;
        case 1: _t->getCom(); break;
        case 2: _t->sendCom(); break;
        case 3: _t->connectServer(); break;
        case 4: _t->disconnectServer(); break;
        case 5: _t->doProcess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->inClear(); break;
        case 7: _t->outClear(); break;
        case 8: _t->blain(); break;
        case 9: _t->connected(); break;
        case 10: _t->disconnected(); break;
        case 11: _t->bytesWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 12: _t->readFromServer(); break;
        case 13: _t->displayTcpError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 14: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: { bool _r = _t->sendData((*reinterpret_cast< vector<unsigned char>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 16: { QString _r = _t->backDataConvent((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: _t->setForntColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData comBySocket::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject comBySocket::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_comBySocket,
      qt_meta_data_comBySocket, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &comBySocket::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *comBySocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *comBySocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_comBySocket))
        return static_cast<void*>(const_cast< comBySocket*>(this));
    return QWidget::qt_metacast(_clname);
}

int comBySocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
