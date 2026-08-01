import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

pragma ComponentBehavior: Bound

Rectangle {
    id: root

    required property AppController controller
    radius: 18
    color: Theme.backgroundRaised
    border.color: Theme.border

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 14

        RowLayout {
            Layout.fillWidth: true

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 2

                Text {
                    text: qsTr("Watchlist")
                    color: Theme.textPrimary
                    font.pixelSize: 18
                    font.weight: Font.DemiBold
                }

                Text {
                    text: qsTr("USD spot markets")
                    color: Theme.textMuted
                    font.pixelSize: 11
                }
            }

            Rectangle {
                implicitWidth: countLabel.implicitWidth + 16
                implicitHeight: 26
                radius: 8
                color: Theme.panel

                Text {
                    id: countLabel
                    anchors.centerIn: parent
                    text: coinList.count
                    color: Theme.textSecondary
                    font.pixelSize: 11
                    font.weight: Font.DemiBold
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            TextField {
                id: symbolField

                Layout.fillWidth: true
                implicitHeight: 42
                placeholderText: qsTr("Add symbol, e.g. DOGE")
                color: Theme.textPrimary
                placeholderTextColor: Theme.textMuted
                selectionColor: Theme.accent
                selectedTextColor: Theme.textPrimary
                font.capitalization: Font.AllUppercase
                maximumLength: 15
                leftPadding: 13
                rightPadding: 13
                onAccepted: addRequested()

                function addRequested() {
                    if (root.controller.addCoin(text))
                        clear()
                }

                background: Rectangle {
                    radius: 11
                    color: symbolField.activeFocus ? Theme.panelHover : Theme.panel
                    border.color: symbolField.activeFocus ? Theme.accent : Theme.border
                    Behavior on border.color { ColorAnimation { duration: 140 } }
                }
            }

            Button {
                id: addButton

                implicitWidth: 44
                implicitHeight: 42
                text: "+"
                onClicked: symbolField.addRequested()

                contentItem: Text {
                    text: addButton.text
                    color: Theme.textPrimary
                    font.pixelSize: 21
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 11
                    color: addButton.down ? Theme.accentBright
                                          : addButton.hovered ? Qt.lighter(Theme.accent, 1.08)
                                                              : Theme.accent
                    Behavior on color { ColorAnimation { duration: 120 } }
                }
            }
        }

        ListView {
            id: coinList

            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 8
            clip: true
            model: root.controller.watchlistModel
            currentIndex: -1

            delegate: CoinDelegate {
                width: coinList.width
                controller: root.controller
                selected: symbol === root.controller.selectedSymbol
            }

            add: Transition {
                NumberAnimation { properties: "opacity,scale"; from: 0.75; to: 1; duration: 180 }
            }

            remove: Transition {
                NumberAnimation { property: "opacity"; to: 0; duration: 130 }
            }

            displaced: Transition {
                NumberAnimation { properties: "x,y"; duration: 180; easing.type: Easing.OutCubic }
            }

            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AsNeeded
            }

            Text {
                anchors.centerIn: parent
                visible: coinList.count === 0
                text: qsTr("Your watchlist is empty.\nAdd a symbol to begin.")
                color: Theme.textMuted
                font.pixelSize: 13
                horizontalAlignment: Text.AlignHCenter
                lineHeight: 1.4
            }
        }
    }
}
