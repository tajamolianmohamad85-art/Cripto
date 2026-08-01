import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    required property string message
    required property bool error
    signal dismissed
    signal retryRequested

    implicitHeight: 46
    radius: 12
    color: error ? Palette.negativeMuted : Palette.positiveMuted
    border.color: error ? Qt.alpha(Palette.negative, 0.35) : Qt.alpha(Palette.positive, 0.28)

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 14
        anchors.rightMargin: 8
        spacing: 10

        Rectangle {
            width: 8
            height: 8
            radius: 4
            color: root.error ? Palette.negative : Palette.positive
        }

        Text {
            Layout.fillWidth: true
            text: root.message
            color: Palette.textPrimary
            font.pixelSize: 12
            elide: Text.ElideRight
        }

        Button {
            visible: root.error
            text: qsTr("Retry")
            implicitWidth: 62
            implicitHeight: 30
            onClicked: root.retryRequested()

            contentItem: Text {
                text: parent.text
                color: Palette.textPrimary
                font.pixelSize: 11
                font.weight: Font.DemiBold
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                radius: 8
                color: parent.hovered ? Palette.panelHover : Palette.panel
                border.color: Palette.borderStrong
            }
        }

        Button {
            text: "×"
            implicitWidth: 32
            implicitHeight: 30
            onClicked: root.dismissed()

            contentItem: Text {
                text: parent.text
                color: Palette.textSecondary
                font.pixelSize: 19
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                radius: 8
                color: parent.hovered ? Qt.alpha(Palette.textPrimary, 0.08) : "transparent"
            }
        }
    }
}
