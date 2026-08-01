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
        "chartRangeChanged",
        "chartPointsChanged",
        "chartAxisRangeChanged",
        "chartStatsChanged",
        "chartLabelsChanged",
        "chartLoadingChanged",
        "chartErrorChanged",
        "addCoin",
        "input",
        "removeCoin",
        "symbol",
        "selectCoin",
        "setChartRange",
        "range",
        "refresh",
        "retryConnections",
        "dismissNotice",
        "formatPrice",
        "value",
        "formatChange",
        "formatCompactNumber",
        "chartPointInfo",
        "QVariantMap",
        "index",
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
        "selectedChangeOneHour",
        "selectedChangeSevenDays",
        "selectedMarketCap",
        "selectedVolume",
        "selectedHigh",
        "selectedLow",
        "selectedRank",
        "selectedHasPrice",
        "chartRange",
        "chartRangeLabel",
        "chartPoints",
        "QVariantList",
        "chartMinimum",
        "chartMaximum",
        "chartPeriodChange",
        "chartHigh",
        "chartLow",
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
        // Signal 'chartRangeChanged'
        QtMocHelpers::SignalData<void()>(8, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'chartPointsChanged'
        QtMocHelpers::SignalData<void()>(9, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'chartAxisRangeChanged'
        QtMocHelpers::SignalData<void()>(10, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'chartStatsChanged'
        QtMocHelpers::SignalData<void()>(11, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'chartLabelsChanged'
        QtMocHelpers::SignalData<void()>(12, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'chartLoadingChanged'
        QtMocHelpers::SignalData<void()>(13, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'chartErrorChanged'
        QtMocHelpers::SignalData<void()>(14, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'addCoin'
        QtMocHelpers::MethodData<bool(const QString &)>(15, 4, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 16 },
        }}),
        // Method 'removeCoin'
        QtMocHelpers::MethodData<void(const QString &)>(17, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 },
        }}),
        // Method 'selectCoin'
        QtMocHelpers::MethodData<void(const QString &)>(19, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 },
        }}),
        // Method 'setChartRange'
        QtMocHelpers::MethodData<void(const QString &)>(20, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 21 },
        }}),
        // Method 'refresh'
        QtMocHelpers::MethodData<void()>(22, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'retryConnections'
        QtMocHelpers::MethodData<void()>(23, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'dismissNotice'
        QtMocHelpers::MethodData<void()>(24, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'formatPrice'
        QtMocHelpers::MethodData<QString(double) const>(25, 4, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Double, 26 },
        }}),
        // Method 'formatChange'
        QtMocHelpers::MethodData<QString(double) const>(27, 4, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Double, 26 },
        }}),
        // Method 'formatCompactNumber'
        QtMocHelpers::MethodData<QString(double) const>(28, 4, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Double, 26 },
        }}),
        // Method 'chartPointInfo'
        QtMocHelpers::MethodData<QVariantMap(int) const>(29, 4, QMC::AccessPublic, 0x80000000 | 30, {{
            { QMetaType::Int, 31 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'watchlistModel'
        QtMocHelpers::PropertyData<QAbstractItemModel*>(32, 0x80000000 | 33, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'connectionState'
        QtMocHelpers::PropertyData<enum ConnectionState>(34, 0x80000000 | 35, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'connectionText'
        QtMocHelpers::PropertyData<QString>(36, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'lastUpdated'
        QtMocHelpers::PropertyData<QDateTime>(37, QMetaType::QDateTime, QMC::DefaultPropertyFlags, 1),
        // property 'notice'
        QtMocHelpers::PropertyData<QString>(38, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
        // property 'noticeIsError'
        QtMocHelpers::PropertyData<bool>(39, QMetaType::Bool, QMC::DefaultPropertyFlags, 2),
        // property 'selectedSymbol'
        QtMocHelpers::PropertyData<QString>(40, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'selectedName'
        QtMocHelpers::PropertyData<QString>(41, QMetaType::QString, QMC::DefaultPropertyFlags, 3),
        // property 'selectedPrice'
        QtMocHelpers::PropertyData<double>(42, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
        // property 'selectedChange'
        QtMocHelpers::PropertyData<double>(43, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
        // property 'selectedChangeOneHour'
        QtMocHelpers::PropertyData<double>(44, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
        // property 'selectedChangeSevenDays'
        QtMocHelpers::PropertyData<double>(45, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
        // property 'selectedMarketCap'
        QtMocHelpers::PropertyData<double>(46, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
        // property 'selectedVolume'
        QtMocHelpers::PropertyData<double>(47, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
        // property 'selectedHigh'
        QtMocHelpers::PropertyData<double>(48, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
        // property 'selectedLow'
        QtMocHelpers::PropertyData<double>(49, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
        // property 'selectedRank'
        QtMocHelpers::PropertyData<int>(50, QMetaType::Int, QMC::DefaultPropertyFlags, 3),
        // property 'selectedHasPrice'
        QtMocHelpers::PropertyData<bool>(51, QMetaType::Bool, QMC::DefaultPropertyFlags, 3),
        // property 'chartRange'
        QtMocHelpers::PropertyData<QString>(52, QMetaType::QString, QMC::DefaultPropertyFlags, 4),
        // property 'chartRangeLabel'
        QtMocHelpers::PropertyData<QString>(53, QMetaType::QString, QMC::DefaultPropertyFlags, 4),
        // property 'chartPoints'
        QtMocHelpers::PropertyData<QVariantList>(54, 0x80000000 | 55, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 5),
        // property 'chartMinimum'
        QtMocHelpers::PropertyData<double>(56, QMetaType::Double, QMC::DefaultPropertyFlags, 6),
        // property 'chartMaximum'
        QtMocHelpers::PropertyData<double>(57, QMetaType::Double, QMC::DefaultPropertyFlags, 6),
        // property 'chartPeriodChange'
        QtMocHelpers::PropertyData<double>(58, QMetaType::Double, QMC::DefaultPropertyFlags, 7),
        // property 'chartHigh'
        QtMocHelpers::PropertyData<double>(59, QMetaType::Double, QMC::DefaultPropertyFlags, 7),
        // property 'chartLow'
        QtMocHelpers::PropertyData<double>(60, QMetaType::Double, QMC::DefaultPropertyFlags, 7),
        // property 'chartStartLabel'
        QtMocHelpers::PropertyData<QString>(61, QMetaType::QString, QMC::DefaultPropertyFlags, 8),
        // property 'chartMiddleLabel'
        QtMocHelpers::PropertyData<QString>(62, QMetaType::QString, QMC::DefaultPropertyFlags, 8),
        // property 'chartEndLabel'
        QtMocHelpers::PropertyData<QString>(63, QMetaType::QString, QMC::DefaultPropertyFlags, 8),
        // property 'chartLoading'
        QtMocHelpers::PropertyData<bool>(64, QMetaType::Bool, QMC::DefaultPropertyFlags, 9),
        // property 'chartError'
        QtMocHelpers::PropertyData<QString>(65, QMetaType::QString, QMC::DefaultPropertyFlags, 10),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'ConnectionState'
        QtMocHelpers::EnumData<enum ConnectionState>(35, 35, QMC::EnumFlags{}).add({
            {   66, ConnectionState::Starting },
            {   67, ConnectionState::Connecting },
            {   68, ConnectionState::Live },
            {   69, ConnectionState::Reconnecting },
            {   70, ConnectionState::Offline },
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
        case 4: _t->chartRangeChanged(); break;
        case 5: _t->chartPointsChanged(); break;
        case 6: _t->chartAxisRangeChanged(); break;
        case 7: _t->chartStatsChanged(); break;
        case 8: _t->chartLabelsChanged(); break;
        case 9: _t->chartLoadingChanged(); break;
        case 10: _t->chartErrorChanged(); break;
        case 11: { bool _r = _t->addCoin((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->removeCoin((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 13: _t->selectCoin((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->setChartRange((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->refresh(); break;
        case 16: _t->retryConnections(); break;
        case 17: _t->dismissNotice(); break;
        case 18: { QString _r = _t->formatPrice((*reinterpret_cast<std::add_pointer_t<double>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 19: { QString _r = _t->formatChange((*reinterpret_cast<std::add_pointer_t<double>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 20: { QString _r = _t->formatCompactNumber((*reinterpret_cast<std::add_pointer_t<double>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 21: { QVariantMap _r = _t->chartPointInfo((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
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
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::chartRangeChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::chartPointsChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::chartAxisRangeChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::chartStatsChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::chartLabelsChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::chartLoadingChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppController::*)()>(_a, &AppController::chartErrorChanged, 10))
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
        case 10: *reinterpret_cast<double*>(_v) = _t->selectedChangeOneHour(); break;
        case 11: *reinterpret_cast<double*>(_v) = _t->selectedChangeSevenDays(); break;
        case 12: *reinterpret_cast<double*>(_v) = _t->selectedMarketCap(); break;
        case 13: *reinterpret_cast<double*>(_v) = _t->selectedVolume(); break;
        case 14: *reinterpret_cast<double*>(_v) = _t->selectedHigh(); break;
        case 15: *reinterpret_cast<double*>(_v) = _t->selectedLow(); break;
        case 16: *reinterpret_cast<int*>(_v) = _t->selectedRank(); break;
        case 17: *reinterpret_cast<bool*>(_v) = _t->selectedHasPrice(); break;
        case 18: *reinterpret_cast<QString*>(_v) = _t->chartRange(); break;
        case 19: *reinterpret_cast<QString*>(_v) = _t->chartRangeLabel(); break;
        case 20: *reinterpret_cast<QVariantList*>(_v) = _t->chartPoints(); break;
        case 21: *reinterpret_cast<double*>(_v) = _t->chartMinimum(); break;
        case 22: *reinterpret_cast<double*>(_v) = _t->chartMaximum(); break;
        case 23: *reinterpret_cast<double*>(_v) = _t->chartPeriodChange(); break;
        case 24: *reinterpret_cast<double*>(_v) = _t->chartHigh(); break;
        case 25: *reinterpret_cast<double*>(_v) = _t->chartLow(); break;
        case 26: *reinterpret_cast<QString*>(_v) = _t->chartStartLabel(); break;
        case 27: *reinterpret_cast<QString*>(_v) = _t->chartMiddleLabel(); break;
        case 28: *reinterpret_cast<QString*>(_v) = _t->chartEndLabel(); break;
        case 29: *reinterpret_cast<bool*>(_v) = _t->chartLoading(); break;
        case 30: *reinterpret_cast<QString*>(_v) = _t->chartError(); break;
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
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 22;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
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
void AppController::chartRangeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void AppController::chartPointsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void AppController::chartAxisRangeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void AppController::chartStatsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void AppController::chartLabelsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void AppController::chartLoadingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void AppController::chartErrorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
