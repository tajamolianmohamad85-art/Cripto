import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window

    width: 1180
    height: 760
    minimumWidth: 960
    minimumHeight: 640
    visible: true
    title: qsTr("CryptoPulse")
    color: Palette.background

    AppController {
        id: controller
    }

    Rectangle {
        width: 420
        height: 420
        radius: width / 2
        x: window.width - width * 0.45
        y: -height * 0.65
        color: Palette.accent
        opacity: 0.055
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 14

        AppHeader {
            Layout.fillWidth: true
            controller: controller
        }

        StatusBanner {
            Layout.fillWidth: true
            visible: controller.notice.length > 0
            message: controller.notice
            error: controller.noticeIsError
            onDismissed: controller.dismissNotice()
            onRetryRequested: controller.retryConnections()
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 14

            WatchlistPanel {
                Layout.preferredWidth: 354
                Layout.minimumWidth: 310
                Layout.fillHeight: true
                controller: controller
            }

            CoinDetail {
                Layout.fillWidth: true
                Layout.fillHeight: true
                controller: controller
            }
        }
    }
}
