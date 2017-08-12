/****************************************************************************
** Meta object code from reading C++ file 'spotmenu.h'
**
** Created: Sun Apr 30 20:02:34 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "spotmenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spotmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GPIOThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_GPIOThread[] = {
    "GPIOThread\0\0signalGPIO()\0"
};

const QMetaObject GPIOThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_GPIOThread,
      qt_meta_data_GPIOThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GPIOThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GPIOThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GPIOThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GPIOThread))
        return static_cast<void*>(const_cast< GPIOThread*>(this));
    return QThread::qt_metacast(_clname);
}

int GPIOThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalGPIO(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void GPIOThread::signalGPIO()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_UsartThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      25,   12,   12,   12, 0x05,
      41,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_UsartThread[] = {
    "UsartThread\0\0signalSPI()\0signalWelding()\0"
    "signalFinishWelding()\0"
};

const QMetaObject UsartThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_UsartThread,
      qt_meta_data_UsartThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UsartThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UsartThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UsartThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UsartThread))
        return static_cast<void*>(const_cast< UsartThread*>(this));
    return QThread::qt_metacast(_clname);
}

int UsartThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalSPI(); break;
        case 1: signalWelding(); break;
        case 2: signalFinishWelding(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void UsartThread::signalSPI()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void UsartThread::signalWelding()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void UsartThread::signalFinishWelding()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
static const uint qt_meta_data_CalcThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CalcThread[] = {
    "CalcThread\0\0signalPlot()\0"
};

const QMetaObject CalcThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CalcThread,
      qt_meta_data_CalcThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CalcThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CalcThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CalcThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CalcThread))
        return static_cast<void*>(const_cast< CalcThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CalcThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalPlot(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CalcThread::signalPlot()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_FileThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_FileThread[] = {
    "FileThread\0"
};

const QMetaObject FileThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FileThread,
      qt_meta_data_FileThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FileThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FileThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FileThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileThread))
        return static_cast<void*>(const_cast< FileThread*>(this));
    return QThread::qt_metacast(_clname);
}

int FileThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_spotmenu[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,    9,    9,    9, 0x0a,
      51,    9,    9,    9, 0x0a,
      67,    9,    9,    9, 0x0a,
      85,    9,    9,    9, 0x0a,
     102,    9,    9,    9, 0x0a,
     122,    9,    9,    9, 0x0a,
     148,    9,    9,    9, 0x0a,
     196,  179,    9,    9, 0x0a,
     227,    9,    9,    9, 0x08,
     255,    9,    9,    9, 0x08,
     288,    9,    9,    9, 0x08,
     312,    9,    9,    9, 0x08,
     338,    9,    9,    9, 0x08,
     372,    9,    9,    9, 0x08,
     404,    9,    9,    9, 0x08,
     429,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_spotmenu[] = {
    "spotmenu\0\0signalRealTime_update()\0"
    "get_signalGPIO()\0get_signalSPI()\0"
    "get_signalTimer()\0get_signalPlot()\0"
    "get_signalWelding()\0get_signalFinishWelding()\0"
    "get_signalShowConnect_Status()\0"
    "socketDescriptor\0get_signalCreateTcpThread(int)\0"
    "on_actionAuthor_triggered()\0"
    "on_actionReadHistory_triggered()\0"
    "on_PlotButton_clicked()\0"
    "on_actionAuto_triggered()\0"
    "on_actionNetWork_Only_triggered()\0"
    "on_actionLocal_Only_triggered()\0"
    "on_actionUsb_triggered()\0"
    "on_actionSD_triggered()\0"
};

const QMetaObject spotmenu::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_spotmenu,
      qt_meta_data_spotmenu, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &spotmenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *spotmenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *spotmenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_spotmenu))
        return static_cast<void*>(const_cast< spotmenu*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int spotmenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalRealTime_update(); break;
        case 1: get_signalGPIO(); break;
        case 2: get_signalSPI(); break;
        case 3: get_signalTimer(); break;
        case 4: get_signalPlot(); break;
        case 5: get_signalWelding(); break;
        case 6: get_signalFinishWelding(); break;
        case 7: get_signalShowConnect_Status(); break;
        case 8: get_signalCreateTcpThread((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: on_actionAuthor_triggered(); break;
        case 10: on_actionReadHistory_triggered(); break;
        case 11: on_PlotButton_clicked(); break;
        case 12: on_actionAuto_triggered(); break;
        case 13: on_actionNetWork_Only_triggered(); break;
        case 14: on_actionLocal_Only_triggered(); break;
        case 15: on_actionUsb_triggered(); break;
        case 16: on_actionSD_triggered(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void spotmenu::signalRealTime_update()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
