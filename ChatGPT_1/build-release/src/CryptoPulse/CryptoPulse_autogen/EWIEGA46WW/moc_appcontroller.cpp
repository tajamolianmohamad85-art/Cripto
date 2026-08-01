/****************************************************************************
** Meta object code from reading C++ file 'appcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/CryptoPulse/appcontroller.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appcontroller.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13AppControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto AppController::qt_create_metaobjectdata<qt_meta_tag_ZN13AppControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AppController",
        "QML.Element",
        "auto",
        "connectionStateChanged",
        "",
        "lastUpdatedChanged",
        "noticeChanged",
        "selectedCoinChanged",
        "chartPointsChanged",
        "chartRangeChanged",
        "chartLabelsChanged",
        "chartLoadingChanged",
        "chartErrorChanged",
        "addCoin",
        "input",
        "removeCoin",
        "symbol",
        "selectCoin",
        "retryConnections",
        "dismissNotice",
        "formatPrice",
        "value",
        "formatChange",
        "watchlistModel",
        "QAbstractItemModel*",
        "connectionState",
        "ConnectionState",
        "connectionText",
        "lastUpdated",
        "notice",
        "noticeIsError",
        "selectedSymbol",
        "selectedName",
        "selectedPrice",
        "selectedChange",
        "selectedHasPrice",
        "chartPoints",
        "QVariantList",
        "chartMinimum",
        "chartMaximum",
        "chartStartLabel",
        "chartMiddleLabel",
        "chartEndLabel",
        "chartLoading",
        "chartError",
        "Starting",
        "Connecting",
        "Live",
        "Reconnecting",
        "Offline"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'connectionStateChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lastUpdatedChanged'
        QtMocHelpers::SignalData<void()>(5, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'noticeChanged'
        QtMocHelpers::SignalData<void()>(6, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'selectedCoinChanged'
        QtMocHelpers::SignalData<void()>(7, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'chartPointsChanged'
        QtMocHelpers::SignalData<void()>(8, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'chartRangeChanged'
        QtMocHelpers::SignalData<void()>(9, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'chartLabelsChanged'
        QtMocHelpers::SignalData<void()>(10, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'chartLoadingChanged'
        QtMocHelpers::SignalData<void()>(11, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'chartErrorChanged'
        QtMocHelpers::SignalData<void()>(12, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'addCoin'
        QtMocHelpers::MethodData<bool(const QString &)>(13, 4, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 14 },
        }}),
        // Method 'removeCoin'
        QtMocHelpers::MethodData<void(const QString &)>(15, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 16 },
        }}),
        // Method 'selectCoin'
        QtMocHelpers::MethodData<void(const QString &)>(17, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 16 },
        }}),
        // Method 'retryConnections'
        QtMocHelpers::MethodData<void()>(18, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'dismissNotice'
        QtMocHelpers::MethodData<void()>(19, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'formatPrice'
        QtMocHelpers::MethodData<QString(double) const>(20, 4, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Double, 21 },
        }}),
        // Method 'formatChange'
        QtMocHelpers::MethodData<QString(double) const>(22, 4, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Double, 21 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'watchlistModel'
        QtMocHelpers::PropertyData<QAbstractItemModel*>(23, 0x80000000 | 24, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'connectionState'
        QtMocHelpers::PropertyData<enum ConnectionState>(25, 0x80000000 | 26, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'connectionText'
        QtMocHelpers::PropertyData<QString>(27, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'lastUpdated'
        QtMocHelpers::PropertyData<QDateTime>(28, QMetaType::QDateTime, QMC::DefaultPropertyFlags, 1),
        // property 'notice'
        QtMocHelpers::PropertyData<QString>(29, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'noticeIsError'
        QtMocHelpers::PropertyData<bool>(30, QMetaType::Bool, QMC::DefaultPropertyFlags, 2),
        // property 'selectedSymbol'
        QtMocHelpers::PropertyData<QString>(31, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'selectedName'
        QtMocHelpers::PropertyData<QString>(32, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'selectedPrice'
        QtMocHelpers::PropertyData<double>(33, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
        // property 'selectedChange'
        QtMocHelpers::PropertyData<double>(34, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
        // property 'selectedHasPrice'
        QtMocHelpers::PropertyData<bool>(35, QMetaType::Bool, QMC::DefaultPropertyFlags, 3),
        // property 'chartPoints'
        QtMocHelpers::PropertyData<QVariantList>(36, 0x80000000 | 37, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 4),
        // property 'chartMinimum'
        QtMocHelpers::PropertyData<double>(38, QMetaType::Double, QMC::DefaultPropertyFlags, 5),
        // property 'chartMaximum'
        QtMocHelpers::PropertyData<double>(39, QMetaType::Double, QMC::DefaultPropertyFlags, 5),
        // property 'chartStartLabel'
        QtMocHelpers::PropertyData<QString>(40, QMetaType::QString, QMC::DefaultPropertyFlags, 6),
        // property 'chartMiddleLabel'
        QtMocHelpers::PropertyData<QString>(41, QMetaType::QString, QMC::DefaultPropertyFlags, 6),
        // property 'chartEndLabel'
        QtMocHelpers::PropertyData<QString>(42, QMetaType::QString, QMC::DefaultPropertyFlags, 6),
        // property 'chartLoading'
        QtMocHelpers::PropertyData<bool>(43, QMetaType::Bool, QMC::DefaultPropertyFlags, 7),
        // property 'chartError'
        QtMocHelpers::PropertyData<QString>(44, QMetaType::QString, QMC::DefaultPropertyFlags, 8),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'ConnectionState'
        QtMocHelpers::EnumData<enum ConnectionState>(26, 26, QMC::EnumFlags{}).add({
            {   45, ConnectionState::Starting },
            {   46, ConnectionState::Connecting },
            {   47, ConnectionState::Live },
            {   48, ConnectionState::Reconnecting },
            {   49, ConnectionState::Offline },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<AppController, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject AppController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13AppControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13AppControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13AppControllerE_t>.metaTypes,
    nullptr
} };

void AppController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AppController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->connectionStateChanged(); break;
        case 1: _t->lastUpdatedChanged(); break;
        case 2: _t->noticeChanged(); break;
        case 3: _t->selectedCoinChanged(); break;
        case 4: _t->chartPointsChanged(); break;
        case 5: _t->chartRangeChanged(); break;
        case 6: _t->chartLabelsChanged(); break;
        case 7: _t->chartLoadingChanged(); break;
        case 8: _t->chartErrorChanged(); break;
        case 9: { bool _r = _t->addCoin((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->removeCoin((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->selectCoin((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->retryConnections(); break;
        case 13: _t->dismissNotice(); break;
        case 14: { QString _r = _t->formatPrice((*reinterpret_cast<std::add_pointer_t<double>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 15: { QString _r = _t->formatChange((*reinterpret_cast<std::add_pointer_t<double>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::connectionStateChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::lastUpdatedChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::noticeChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::selectedCoinChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::chartPointsChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::chartRangeChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::chartLabelsChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::chartLoadingChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::chartErrorChanged, 8))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractItemModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QAbstractItemModel**>(_v) = _t->watchlistModel(); break;
        case 1: *reinterpret_cast<enum ConnectionState*>(_v) = _t->connectionState(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->connectionText(); break;
        case 3: *reinterpret_cast<QDateTime*>(_v) = _t->lastUpdated(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->notice(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->noticeIsError(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->selectedSymbol(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->selectedName(); break;
        case 8: *reinterpret_cast<double*>(_v) = _t->selectedPrice(); break;
        case 9: *reinterpret_cast<double*>(_v) = _t->selectedChange(); break;
        case 10: *reinterpret_cast<bool*>(_v) = _t->selectedHasPrice(); break;
        case 11: *reinterpret_cast<QVariantList*>(_v) = _t->chartPoints(); break;
        case 12: *reinterpret_cast<double*>(_v) = _t->chartMinimum(); break;
        case 13: *reinterpret_cast<double*>(_v) = _t->chartMaximum(); break;
        case 14: *reinterpret_cast<QString*>(_v) = _t->chartStartLabel(); break;
        case 15: *reinterpret_cast<QString*>(_v) = _t->chartMiddleLabel(); break;
        case 16: *reinterpret_cast<QString*>(_v) = _t->chartEndLabel(); break;
        case 17: *reinterpret_cast<bool*>(_v) = _t->chartLoading(); break;
        case 18: *reinterpret_cast<QString*>(_v) = _t->chartError(); break;
        default: break;
        }
    }
}

const QMetaObject *AppController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13AppControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AppController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void AppController::connectionStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AppController::lastUpdatedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AppController::noticeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AppController::selectedCoinChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void AppController::chartPointsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void AppController::chartRangeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void AppController::chartLabelsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void AppController::chartLoadingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void AppController::chartErrorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
