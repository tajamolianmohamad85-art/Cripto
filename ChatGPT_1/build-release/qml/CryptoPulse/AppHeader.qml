import QtQuick
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
            color: Theme.accent

            Rectangle {
                width: 18
                height: 18
                anchors.centerIn: parent
                radius: 6
                color: Theme.background
                rotation: 45
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 2

            Text {
                text: qsTr("CryptoPulse")
                color: Theme.textPrimary
                font.pixelSize: 23
                font.weight: Font.DemiBold
            }

            Text {
                text: qsTr("Real-time digital asset monitor")
                color: Theme.textSecondary
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

                    Layout.preferredWidth: 9
                    Layout.preferredHeight: 9
                    radius: 5
                    color: root.controller.connectionState === AppController.Live
                           ? Theme.positive
                           : root.controller.connectionState === AppController.Offline
                             ? Theme.negative
                             : Theme.warning

                    SequentialAnimation on opacity {
                        running: root.controller.connectionState === AppController.Live
                        loops: Animation.Infinite
                        NumberAnimation { to: 0.35; duration: 850; easing.type: Easing.InOutSine }
                        NumberAnimation { to: 1.0; duration: 850; easing.type: Easing.InOutSine }
                    }
                }

                Text {
                    text: root.controller.connectionText
                    color: Theme.textPrimary
                    font.pixelSize: 13
                    font.weight: Font.DemiBold
                }
            }

            Text {
                Layout.alignment: Qt.AlignRight
                text: root.controller.lastUpdated.getTime() > 0
                      ? qsTr("Last tick %1").arg(Qt.formatTime(root.controller.lastUpdated, "hh:mm:ss"))
                      : qsTr("Waiting for market data")
                color: Theme.textMuted
                font.pixelSize: 11
            }
        }
    }
}
