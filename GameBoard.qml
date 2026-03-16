import QtQuick

Item {
    id: root
    width: 1920
    height: 1080
    focus: true


    Rectangle {
        id: backgoundRect
        anchors.fill: parent
        color: "#7373fd"
    }

    Row {
        id: row
        x: 860
        y: 340
        width: 723
        height: 400
        anchors.centerIn: parent

        Column {
            id: holdCol
            spacing: 8
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: matrix.left
            anchors.rightMargin: 116

            Text {
                text: "HOLD"
                color: "#aaaaaa"
                font.family: "Verdana"
                font.pixelSize: 16
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Grid {
                rows: 4
                columns: 4
                Repeater {
                    model: game.holdCells
                    Rectangle {
                        width:  Constants.rectWidth
                        height: Constants.rectHeight
                        color:  modelData === "" ? "#111111" : modelData
                        border.color: "#2a2a2a"
                        border.width: 1
                    }
                }
            }

            // Score / Level / Lines
            Column {
                spacing: 12
                topPadding: 24

                Repeater {
                    model: [
                        { label: "SCORE", value: game.score },
                        { label: "LEVEL", value: game.level },
                        { label: "LINES", value: game.lines }
                    ]
                    Column {
                        spacing: 2
                        Text {
                            text: modelData.label
                            color: "#888888"
                            font.pixelSize: 12
                            font.family: "Verdana"
                        }
                        Text {
                            text: modelData.value
                            color: "#ffffff"
                            font.pixelSize: 22
                            font.family: "Verdana"
                            font.bold: true
                        }
                    }
                }
            }
        }

        Item {
            id: matrix
            width: 400
            height: 800
            anchors.centerIn: parent

            // Cellules figées + pièce courante
            Grid {
                id: mainGrid
                anchors.fill: parent
                rows:    Constants.gridRows
                columns: Constants.gridCols

                Repeater {
                    model: game.cells
                    Rectangle {
                        visible: false
                        color:  modelData === "" ? "#111111" : modelData
                        border.color: "#2a2a2a"
                        border.width: 1
                    }
                }
            }

            // Ghost piece (superposée, semi-transparente)
        }

        Column {
            id: nextCol
            spacing: 8
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: matrix.right
            anchors.leftMargin: 0

            Text {
                text: "NEXT"
                color: "#aaaaaa"
                font.family: "Verdana"
                font.pixelSize: 16
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Grid {
                rows: 4
                columns: 4
                Repeater {
                    model: game.holdCells
                    Rectangle {
                        width:  Constants.rectWidth
                        height: Constants.rectHeight
                        color:  modelData === "" ? "#111111" : modelData
                        border.color: "#2a2a2a"
                        border.width: 1
                    }
                }
            }
        }
    }
}
