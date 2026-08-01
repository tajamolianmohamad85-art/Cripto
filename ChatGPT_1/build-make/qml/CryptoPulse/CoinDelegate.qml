import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    required property AppController controller
    required property string symbol
    required property string name
    required property string pair
    required property real price
    required property real change
    required property bool hasPrice
    required property int direction
    required property bool selected

    property bool hovered: hoverHandler.hovered
    property real animatedPrice: hasPrice ? price : 0

    height: 76
    radius: 13
    color: selected ? Theme.panelSelected : hovered ? Theme.panelHover : Theme.panel
    border.color: selected ? Qt.alpha(Theme.accent, 0.72) : Theme.border

    Behavior on color { ColorAnimation { duration: 150 } }
    Behavior on border.color { ColorAnimation { duration: 150 } }
    Behavior on animatedPrice {
        NumberAnimation { duration: 420; easing.type: Easing.OutCubic }
    }

    HoverHandler {
        id: hoverHandler
    }

    TapHandler {
        onTapped: root.controller.selectCoin(root.symbol)
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 12
        anchors.rightMargin: 8
        spacing: 10

        Rectangle {
            Layout.preferredWidth: 38
            Layout.preferredHeight: 38
            radius: 12
            color: root.selected ? Qt.alpha(Theme.accent, 0.22) : Theme.backgroundRaised

            Text {
                anchors.centerIn: parent
                text: root.symbol.slice(0, 2)
                color: root.selected ? Theme.accentBright : Theme.textSecondary
                font.pixelSize: 12
                font.weight: Font.Bold
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 2

            Text {
                text: root.name
                color: Theme.textPrimary
                font.pixelSize: 13
                font.weight: Font.DemiBold
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Text {
                text: root.symbol + " / USD"
                color: Theme.textMuted
                font.pixelSize: 10
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter
            spacing: 4

            Text {
                Layout.alignment: Qt.AlignRight
                text: root.hasPrice ? "$" + root.controller.formatPrice(root.animatedPrice) : "—"
                color: root.direction > 0 ? Theme.positive
                                          : root.direction < 0 ? Theme.negative
                                                               : Theme.textPrimary
                font.pixelSize: 13
                font.weight: Font.DemiBold

                Behavior on color { ColorAnimation { duration: 180 } }
            }

            Text {
                Layout.alignment: Qt.AlignRight
                text: root.hasPrice ? root.controller.formatChange(root.change) : qsTr("Loading")
                color: root.hasPrice
                       ? root.change >= 0 ? Theme.positive : Theme.negative
                       : Theme.textMuted
                font.pixelSize: 10
                font.weight: Font.DemiBold
            }
        }

        Button {
            id: removeButton

            Layout.preferredWidth: 28
            Layout.preferredHeight: 28
            text: "×"
            onClicked: root.controller.removeCoin(root.symbol)

            contentItem: Text {
                text: removeButton.text
                color: removeButton.hovered ? Theme.negative : Theme.textMuted
                font.pixelSize: 17
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                radius: 8
                color: removeButton.hovered ? Qt.alpha(Theme.negative, 0.11) : "transparent"
            }
        }
    }
}
