import QtQuick
import QtQuick.Controls
import Tetris

Item {
    id: root
    width: Constants.width
    height: Constants.height

    focus: true

    TetrisGame {
        id: game
    }

    Rectangle {
        anchors.fill: parent
        color: "#1a1a2e"
    }

    Row {
        anchors.centerIn: parent
        spacing: 16

        Column {
            spacing: 8
            anchors.verticalCenter: parent.verticalCenter

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
            width:  Constants.rectWidth  * Constants.gridCols
            height: Constants.rectHeight * Constants.gridRows

            Grid {
                id: mainGrid
                anchors.fill: parent
                rows:    Constants.gridRows
                columns: Constants.gridCols

                Repeater {
                    model: game.cells
                    Rectangle {
                        width:  Constants.rectWidth
                        height: Constants.rectHeight
                        color:  modelData === "" ? "#111111" : modelData
                        border.color: "#2a2a2a"
                        border.width: 1
                    }
                }
            }

            Grid {
                anchors.fill: parent
                rows:    Constants.gridRows
                columns: Constants.gridCols

                Repeater {
                    model: game.ghost
                    Rectangle {
                        width:  Constants.rectWidth
                        height: Constants.rectHeight
                        color:  modelData === "" ? "transparent" : modelData
                        opacity: 0.35
                        border.color: modelData === "" ? "transparent" : "#666666"
                        border.width: 1
                    }
                }
            }

            Rectangle {
                anchors.fill: parent
                color: "#99000000"
                visible: !game.running && !game.gameOver

                Text {
                    anchors.centerIn: parent
                    text: "PAUSE"
                    color: "white"
                    font.pixelSize: 40
                    font.bold: true
                    font.family: "Verdana"
                }
            }

            Rectangle {
                anchors.fill: parent
                color: "#CC000000"
                visible: game.gameOver

                Column {
                    anchors.centerIn: parent
                    spacing: 20

                    Text {
                        text: "GAME OVER"
                        color: "#ff4444"
                        font.pixelSize: 36
                        font.bold: true
                        font.family: "Verdana"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        text: "Score : " + game.score
                        color: "white"
                        font.pixelSize: 20
                        font.family: "Verdana"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Rectangle {
                        width: 140; height: 44
                        color: "#3a3a5c"
                        radius: 6
                        anchors.horizontalCenter: parent.horizontalCenter

                        Text {
                            anchors.centerIn: parent
                            text: "REJOUER"
                            color: "white"
                            font.pixelSize: 16
                            font.family: "Verdana"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                game.start()
                                root.forceActiveFocus()
                            }
                        }
                    }
                }
            }
        }

        Column {
            spacing: 8
            anchors.verticalCenter: parent.verticalCenter

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
                    model: game.nextCells
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

    Rectangle {
        anchors.centerIn: parent
        width: 160; height: 50
        color: "#3a3a5c"
        radius: 8
        visible: !game.running && !game.gameOver

        Text {
            anchors.centerIn: parent
            text: "START"
            color: "white"
            font.pixelSize: 20
            font.bold: true
            font.family: "Verdana"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                game.start()
                root.forceActiveFocus()
            }
        }
    }

    Keys.onPressed: (event) => {
        if (event.isAutoRepeat && event.key !== Qt.Key_Down) return

        switch (event.key) {
            case Qt.Key_Left:   game.moveLeft();   break
            case Qt.Key_Right:  game.moveRight();  break
            case Qt.Key_Up:     game.rotate();     break
            case Qt.Key_Down:   game.softDrop();   break
            case Qt.Key_Space:  game.hardDrop();   break
            case Qt.Key_C:
            case Qt.Key_Shift:  game.holdPiece();  break
            case Qt.Key_P:
            case Qt.Key_Escape: game.pause();      break
        }
        event.accepted = true
    }
}
