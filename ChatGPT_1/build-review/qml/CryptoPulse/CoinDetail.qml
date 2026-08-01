import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root

    required property AppController controller
    property real animatedPrice: controller.selectedHasPrice ? controller.selectedPrice : 0

    radius: 18
    color: Theme.backgroundRaised
    border.color: Theme.border

    Behavior on animatedPrice {
        NumberAnimation { duration: 460; easing.type: Easing.OutCubic }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 22
        spacing: 18
        visible: root.controller.selectedSymbol.length > 0

        RowLayout {
            Layout.fillWidth: true
            spacing: 14

            Rectangle {
                Layout.preferredWidth: 50
                Layout.preferredHeight: 50
                radius: 15
                color: Qt.alpha(Theme.accent, 0.18)

                Text {
                    anchors.centerIn: parent
                    text: root.controller.selectedSymbol.slice(0, 2)
                    color: Theme.accentBright
                    font.pixelSize: 15
                    font.weight: Font.Bold
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 3

                Text {
                    text: root.controller.selectedName
                    color: Theme.textPrimary
                    font.pixelSize: 20
                    font.weight: Font.DemiBold
                }

                Text {
                    text: root.controller.selectedSymbol + " / USD · 7 day history"
                    color: Theme.textMuted
                    font.pixelSize: 11
                }
            }

            ColumnLayout {
                spacing: 5

                Text {
                    Layout.alignment: Qt.AlignRight
                    text: root.controller.selectedHasPrice
                          ? "$" + root.controller.formatPrice(root.animatedPrice)
                          : "—"
                    color: Theme.textPrimary
                    font.pixelSize: 25
                    font.weight: Font.DemiBold
                }

                Rectangle {
                    Layout.alignment: Qt.AlignRight
                    implicitWidth: changeText.implicitWidth + 16
                    implicitHeight: 25
                    radius: 8
                    color: root.controller.selectedChange >= 0
                           ? Theme.positiveMuted : Theme.negativeMuted

                    Text {
                        id: changeText
                        anchors.centerIn: parent
                        text: root.controller.selectedHasPrice
                              ? root.controller.formatChange(root.controller.selectedChange) + "  24h"
                              : qsTr("Waiting for tick")
                        color: root.controller.selectedChange >= 0
                               ? Theme.positive : Theme.negative
                        font.pixelSize: 11
                        font.weight: Font.DemiBold
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 15
            color: Theme.panel
            border.color: Theme.border

            PriceChart {
                anchors.fill: parent
                anchors.margins: 12
                controller: root.controller
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Text {
                Layout.fillWidth: true
                text: qsTr("Streaming from Kraken WebSocket v2")
                color: Theme.textMuted
                font.pixelSize: 10
            }

            Text {
                text: qsTr("Hourly OHLC · Local time")
                color: Theme.textMuted
                font.pixelSize: 10
            }
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 10
        visible: root.controller.selectedSymbol.length === 0

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("No coin selected")
            color: Theme.textPrimary
            font.pixelSize: 18
            font.weight: Font.DemiBold
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Add a symbol to restart the live monitor.")
            color: Theme.textMuted
            font.pixelSize: 12
        }
    }
}
