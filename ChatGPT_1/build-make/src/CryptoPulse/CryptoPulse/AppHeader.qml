import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    required property AppController controller
    implicitHeight: 64

    RowLayout {
        anchors.fill: parent
        spacing: 14

        Rectangle {
            Layout.preferredWidth: 46
            Layout.preferredHeight: 46
            radius: 14
            color: Palette.accent

            Rectangle {
                width: 18
                height: 18
                anchors.centerIn: parent
                radius: 6
                color: Palette.background
                rotation: 45
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 2

            Text {
                text: qsTr("CryptoPulse")
                color: Palette.textPrimary
                font.pixelSize: 23
                font.weight: Font.DemiBold
            }

            Text {
                text: qsTr("Real-time digital asset monitor")
                color: Palette.textSecondary
                font.pixelSize: 13
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter
            spacing: 4

            RowLayout {
                Layout.alignment: Qt.AlignRight
                spacing: 8

                Rectangle {
                    id: statusDot

                    width: 9
                    height: 9
                    radius: 5
                    color: root.controller.connectionState === AppController.Live
                           ? Palette.positive
                           : root.controller.connectionState === AppController.Offline
                             ? Palette.negative
                             : Palette.warning

                    SequentialAnimation on opacity {
                        running: root.controller.connectionState === AppController.Live
                        loops: Animation.Infinite
                        NumberAnimation { to: 0.35; duration: 850; easing.type: Easing.InOutSine }
                        NumberAnimation { to: 1.0; duration: 850; easing.type: Easing.InOutSine }
                    }
                }

                Text {
                    text: root.controller.connectionText
                    color: Palette.textPrimary
                    font.pixelSize: 13
                    font.weight: Font.DemiBold
                }
            }

            Text {
                Layout.alignment: Qt.AlignRight
                text: root.controller.lastUpdated.getTime() > 0
                      ? qsTr("Last tick %1").arg(Qt.formatTime(root.controller.lastUpdated, "hh:mm:ss"))
                      : qsTr("Waiting for market data")
                color: Palette.textMuted
                font.pixelSize: 11
            }
        }
    }
}
