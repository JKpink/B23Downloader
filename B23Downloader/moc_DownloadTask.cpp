/****************************************************************************
** Meta object code from reading C++ file 'DownloadTask.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DownloadTask.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DownloadTask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN20AbstractDownloadTaskE_t {};
} // unnamed namespace

template <> constexpr inline auto AbstractDownloadTask::qt_create_metaobjectdata<qt_meta_tag_ZN20AbstractDownloadTaskE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AbstractDownloadTask",
        "downloadFinished",
        "",
        "errorOccurred",
        "errorString",
        "getUrlInfoFinished"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'downloadFinished'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 },
        }}),
        // Signal 'getUrlInfoFinished'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AbstractDownloadTask, qt_meta_tag_ZN20AbstractDownloadTaskE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AbstractDownloadTask::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20AbstractDownloadTaskE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20AbstractDownloadTaskE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20AbstractDownloadTaskE_t>.metaTypes,
    nullptr
} };

void AbstractDownloadTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AbstractDownloadTask *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->downloadFinished(); break;
        case 1: _t->errorOccurred((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->getUrlInfoFinished(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AbstractDownloadTask::*)()>(_a, &AbstractDownloadTask::downloadFinished, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (AbstractDownloadTask::*)(const QString & )>(_a, &AbstractDownloadTask::errorOccurred, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (AbstractDownloadTask::*)()>(_a, &AbstractDownloadTask::getUrlInfoFinished, 2))
            return;
    }
}

const QMetaObject *AbstractDownloadTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractDownloadTask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20AbstractDownloadTaskE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AbstractDownloadTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void AbstractDownloadTask::downloadFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AbstractDownloadTask::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void AbstractDownloadTask::getUrlInfoFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
namespace {
struct qt_meta_tag_ZN25AbstractVideoDownloadTaskE_t {};
} // unnamed namespace

template <> constexpr inline auto AbstractVideoDownloadTask::qt_create_metaobjectdata<qt_meta_tag_ZN25AbstractVideoDownloadTaskE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AbstractVideoDownloadTask"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AbstractVideoDownloadTask, qt_meta_tag_ZN25AbstractVideoDownloadTaskE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AbstractVideoDownloadTask::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractDownloadTask::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN25AbstractVideoDownloadTaskE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN25AbstractVideoDownloadTaskE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN25AbstractVideoDownloadTaskE_t>.metaTypes,
    nullptr
} };

void AbstractVideoDownloadTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AbstractVideoDownloadTask *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *AbstractVideoDownloadTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractVideoDownloadTask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN25AbstractVideoDownloadTaskE_t>.strings))
        return static_cast<void*>(this);
    return AbstractDownloadTask::qt_metacast(_clname);
}

int AbstractVideoDownloadTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractDownloadTask::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN16LiveDownloadTaskE_t {};
} // unnamed namespace

template <> constexpr inline auto LiveDownloadTask::qt_create_metaobjectdata<qt_meta_tag_ZN16LiveDownloadTaskE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "LiveDownloadTask"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<LiveDownloadTask, qt_meta_tag_ZN16LiveDownloadTaskE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject LiveDownloadTask::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractVideoDownloadTask::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16LiveDownloadTaskE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16LiveDownloadTaskE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16LiveDownloadTaskE_t>.metaTypes,
    nullptr
} };

void LiveDownloadTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LiveDownloadTask *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *LiveDownloadTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LiveDownloadTask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16LiveDownloadTaskE_t>.strings))
        return static_cast<void*>(this);
    return AbstractVideoDownloadTask::qt_metacast(_clname);
}

int LiveDownloadTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractVideoDownloadTask::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN17VideoDownloadTaskE_t {};
} // unnamed namespace

template <> constexpr inline auto VideoDownloadTask::qt_create_metaobjectdata<qt_meta_tag_ZN17VideoDownloadTaskE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "VideoDownloadTask"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<VideoDownloadTask, qt_meta_tag_ZN17VideoDownloadTaskE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject VideoDownloadTask::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractVideoDownloadTask::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17VideoDownloadTaskE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17VideoDownloadTaskE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17VideoDownloadTaskE_t>.metaTypes,
    nullptr
} };

void VideoDownloadTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<VideoDownloadTask *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *VideoDownloadTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoDownloadTask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17VideoDownloadTaskE_t>.strings))
        return static_cast<void*>(this);
    return AbstractVideoDownloadTask::qt_metacast(_clname);
}

int VideoDownloadTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractVideoDownloadTask::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN15PgcDownloadTaskE_t {};
} // unnamed namespace

template <> constexpr inline auto PgcDownloadTask::qt_create_metaobjectdata<qt_meta_tag_ZN15PgcDownloadTaskE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PgcDownloadTask"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PgcDownloadTask, qt_meta_tag_ZN15PgcDownloadTaskE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PgcDownloadTask::staticMetaObject = { {
    QMetaObject::SuperData::link<VideoDownloadTask::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PgcDownloadTaskE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PgcDownloadTaskE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15PgcDownloadTaskE_t>.metaTypes,
    nullptr
} };

void PgcDownloadTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PgcDownloadTask *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PgcDownloadTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PgcDownloadTask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PgcDownloadTaskE_t>.strings))
        return static_cast<void*>(this);
    return VideoDownloadTask::qt_metacast(_clname);
}

int PgcDownloadTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VideoDownloadTask::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN16PugvDownloadTaskE_t {};
} // unnamed namespace

template <> constexpr inline auto PugvDownloadTask::qt_create_metaobjectdata<qt_meta_tag_ZN16PugvDownloadTaskE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PugvDownloadTask"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PugvDownloadTask, qt_meta_tag_ZN16PugvDownloadTaskE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PugvDownloadTask::staticMetaObject = { {
    QMetaObject::SuperData::link<VideoDownloadTask::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16PugvDownloadTaskE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16PugvDownloadTaskE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16PugvDownloadTaskE_t>.metaTypes,
    nullptr
} };

void PugvDownloadTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PugvDownloadTask *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *PugvDownloadTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PugvDownloadTask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16PugvDownloadTaskE_t>.strings))
        return static_cast<void*>(this);
    return VideoDownloadTask::qt_metacast(_clname);
}

int PugvDownloadTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VideoDownloadTask::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN15UgcDownloadTaskE_t {};
} // unnamed namespace

template <> constexpr inline auto UgcDownloadTask::qt_create_metaobjectdata<qt_meta_tag_ZN15UgcDownloadTaskE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "UgcDownloadTask"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<UgcDownloadTask, qt_meta_tag_ZN15UgcDownloadTaskE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject UgcDownloadTask::staticMetaObject = { {
    QMetaObject::SuperData::link<VideoDownloadTask::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15UgcDownloadTaskE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15UgcDownloadTaskE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15UgcDownloadTaskE_t>.metaTypes,
    nullptr
} };

void UgcDownloadTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<UgcDownloadTask *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *UgcDownloadTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UgcDownloadTask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15UgcDownloadTaskE_t>.strings))
        return static_cast<void*>(this);
    return VideoDownloadTask::qt_metacast(_clname);
}

int UgcDownloadTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VideoDownloadTask::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN17ComicDownloadTaskE_t {};
} // unnamed namespace

template <> constexpr inline auto ComicDownloadTask::qt_create_metaobjectdata<qt_meta_tag_ZN17ComicDownloadTaskE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ComicDownloadTask",
        "getImgInfoFinished",
        "",
        "getImgTokenFinished",
        "onImgReadyRead",
        "downloadImgFinished"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'getImgInfoFinished'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'getImgTokenFinished'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onImgReadyRead'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'downloadImgFinished'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ComicDownloadTask, qt_meta_tag_ZN17ComicDownloadTaskE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ComicDownloadTask::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractDownloadTask::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17ComicDownloadTaskE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17ComicDownloadTaskE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17ComicDownloadTaskE_t>.metaTypes,
    nullptr
} };

void ComicDownloadTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ComicDownloadTask *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->getImgInfoFinished(); break;
        case 1: _t->getImgTokenFinished(); break;
        case 2: _t->onImgReadyRead(); break;
        case 3: _t->downloadImgFinished(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *ComicDownloadTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComicDownloadTask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17ComicDownloadTaskE_t>.strings))
        return static_cast<void*>(this);
    return AbstractDownloadTask::qt_metacast(_clname);
}

int ComicDownloadTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractDownloadTask::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
