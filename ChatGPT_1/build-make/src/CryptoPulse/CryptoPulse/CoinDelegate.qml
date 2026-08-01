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
    color: selected ? Palette.panelSelected : hovered ? Palette.panelHover : Palette.panel
    border.color: selected ? Qt.alpha(Palette.accent, 0.72) : Palette.border

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
            color: root.selected ? Qt.alpha(Palette.accent, 0.22) : Palette.backgroundRaised

            Text {
                anchors.centerIn: parent
                text: root.symbol.slice(0, 2)
                color: root.selected ? Palette.accentBright : Palette.textSecondary
                font.pixelSize: 12
                font.weight: Font.Bold
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 2

            Text {
                text: root.name
                color: Palette.textPrimary
                font.pixelSize: 13
                font.weight: Font.DemiBold
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Text {
                text: root.symbol + " / USD"
                color: Palette.textMuted
                font.pixelSize: 10
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignVCenter
            spacing: 4

            Text {
                Layout.alignment: Qt.AlignRight
                text: root.hasPrice ? "$" + root.controller.formatPrice(root.animatedPrice) : "—"
                color: root.direction > 0 ? Palette.positive
                                          : root.direction < 0 ? Palette.negative
                                                               : Palette.textPrimary
                font.pixelSize: 13
                font.weight: Font.DemiBold

                Behavior on color { ColorAnimation { duration: 180 } }
            }

            Text {
                Layout.alignment: Qt.AlignRight
                text: root.hasPrice ? root.controller.formatChange(root.change) : qsTr("Loading")
                color: root.hasPrice
                       ? root.change >= 0 ? Palette.positive : Palette.negative
                       : Palette.textMuted
                font.pixelSize: 10
                font.weight: Font.DemiBold
            }
        }

        Button {
            Layout.preferredWidth: 28
            Layout.preferredHeight: 28
            text: "×"
            onClicked: root.controller.removeCoin(root.symbol)

            contentItem: Text {
                text: parent.text
                color: parent.hovered ? Palette.negative : Palette.textMuted
                font.pixelSize: 17
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                radius: 8
                color: parent.hovered ? Qt.alpha(Palette.negative, 0.11) : "transparent"
            }
        }
    }
}
