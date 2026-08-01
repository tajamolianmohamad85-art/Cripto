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
    color: error ? Theme.negativeMuted : Theme.positiveMuted
    border.color: error ? Qt.alpha(Theme.negative, 0.35) : Qt.alpha(Theme.positive, 0.28)

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 14
        anchors.rightMargin: 8
        spacing: 10

        Rectangle {
            Layout.preferredWidth: 8
            Layout.preferredHeight: 8
            radius: 4
            color: root.error ? Theme.negative : Theme.positive
        }

        Text {
            Layout.fillWidth: true
            text: root.message
            color: Theme.textPrimary
            font.pixelSize: 12
            elide: Text.ElideRight
        }

        Button {
            id: retryButton

            visible: root.error
            text: qsTr("Retry")
            implicitWidth: 62
            implicitHeight: 30
            onClicked: root.retryRequested()

            contentItem: Text {
                text: retryButton.text
                color: Theme.textPrimary
                font.pixelSize: 11
                font.weight: Font.DemiBold
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                radius: 8
                color: retryButton.hovered ? Theme.panelHover : Theme.panel
                border.color: Theme.borderStrong
            }
        }

        Button {
            id: dismissButton

            text: "×"
            implicitWidth: 32
            implicitHeight: 30
            onClicked: root.dismissed()

            contentItem: Text {
                text: dismissButton.text
                color: Theme.textSecondary
                font.pixelSize: 19
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                radius: 8
                color: dismissButton.hovered ? Qt.alpha(Theme.textPrimary, 0.08) : "transparent"
            }
        }
    }
}
