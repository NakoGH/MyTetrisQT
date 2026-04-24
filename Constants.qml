pragma Singleton
import QtQuick

QtObject {
    readonly property int width: 1920
    readonly property int height: 1080

    readonly property int gridCols: 10
    readonly property int gridRows: 20

    readonly property int rectHeight: 40
    readonly property int rectWidth: 40

    readonly property int holdWidth: 250
    readonly property int holdHeight: 205
    readonly property int holdCols: 6
    readonly property int holdRows: 4


    property string relativeFontDirectory: "fonts"

    readonly property font font: Qt.font({
                                             family: Qt.application.font.family,
                                             pixelSize: Qt.application.font.pixelSize
                                         })
    readonly property font largeFont: Qt.font({
                                                  family: Qt.application.font.family,
                                                  pixelSize: Qt.application.font.pixelSize * 1.6
                                              })

    readonly property color backgroundColor: "#EAEAEA"


}