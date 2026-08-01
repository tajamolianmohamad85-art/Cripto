import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtGraphs

Item {
    id: root

    required property AppController controller

    function replaceSeries() {
        const source = root.controller.chartPoints
        const points = []
        for (let index = 0; index < source.length; ++index)
            points.push(Qt.point(source[index].x, source[index].y))
        priceSeries.replace(points)
    }

    Connections {
        target: root.controller
        function onChartPointsChanged() {
            replaceTimer.restart()
        }
    }

    Timer {
        id: replaceTimer
        interval: 0
        onTriggered: root.replaceSeries()
    }

    Component.onCompleted: replaceSeries()

    ColumnLayout {
        anchors.fill: parent
        spacing: 2

        GraphsView {
            id: graph

            Layout.fillWidth: true
            Layout.fillHeight: true
            opacity: root.controller.chartLoading ? 0.45 : 1.0
            marginLeft: 8
            marginRight: 12
            marginTop: 10
            marginBottom: 4
            axisXSmoothing: 1
            axisYSmoothing: 1
            gridSmoothing: 1
            shadowVisible: false
            clipPlotArea: true

            Behavior on opacity {
                NumberAnimation { duration: 180 }
            }

            theme: GraphsTheme {
                colorScheme: GraphsTheme.ColorScheme.Dark
                backgroundVisible: false
                plotAreaBackgroundVisible: false
                gridVisible: true
                labelBackgroundVisible: false
                labelBorderVisible: false
                labelTextColor: Palette.textMuted
                seriesColors: [Palette.accentBright]
                borderColors: [Palette.accentBright]
                grid.mainColor: Qt.alpha(Palette.borderStrong, 0.34)
                grid.subColor: Qt.alpha(Palette.border, 0.14)
                axisX.mainColor: "transparent"
                axisY.mainColor: Qt.alpha(Palette.borderStrong, 0.6)
            }

            axisX: ValueAxis {
                min: 0
                max: Math.max(1, root.controller.chartPoints.length - 1)
                labelsVisible: false
                lineVisible: false
                gridVisible: false
            }

            axisY: ValueAxis {
                min: root.controller.chartMinimum
                max: root.controller.chartMaximum
                labelDecimals: -1
                labelFormat: "%.2f"
                subTickCount: 1
            }

            LineSeries {
                id: priceSeries
                color: Palette.accentBright
                width: 2.6
                capStyle: Qt.RoundCap
                joinStyle: Qt.RoundJoin
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.leftMargin: 12
            Layout.rightMargin: 14

            Text {
                Layout.fillWidth: true
                text: root.controller.chartStartLabel
                color: Palette.textMuted
                font.pixelSize: 9
            }

            Text {
                Layout.fillWidth: true
                text: root.controller.chartMiddleLabel
                color: Palette.textMuted
                font.pixelSize: 9
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                Layout.fillWidth: true
                text: root.controller.chartEndLabel
                color: Palette.textMuted
                font.pixelSize: 9
                horizontalAlignment: Text.AlignRight
            }
        }
    }

    BusyIndicator {
        anchors.centerIn: parent
        running: root.controller.chartLoading
        visible: running
        palette.dark: Palette.accent
    }

    Rectangle {
        anchors.centerIn: parent
        width: Math.min(parent.width - 40, 390)
        height: errorColumn.implicitHeight + 30
        radius: 12
        color: Palette.backgroundRaised
        border.color: Palette.borderStrong
        visible: root.controller.chartError.length > 0 && !root.controller.chartLoading

        Column {
            id: errorColumn
            anchors.centerIn: parent
            width: parent.width - 28
            spacing: 10

            Text {
                width: parent.width
                text: root.controller.chartError
                color: Palette.textSecondary
                font.pixelSize: 11
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Retry")
                implicitWidth: 82
                implicitHeight: 32
                onClicked: root.controller.retryConnections()

                contentItem: Text {
                    text: parent.text
                    color: Palette.textPrimary
                    font.pixelSize: 11
                    font.weight: Font.DemiBold
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    radius: 9
                    color: parent.hovered ? Palette.accentBright : Palette.accent
                }
            }
        }
    }
}
