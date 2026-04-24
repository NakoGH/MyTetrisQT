import QtQuick

Window {
    width:  Constants.width
    height: Constants.height
    visible: true
    title: "MyTetris"

    Main
    {
        anchors.fill: parent
        focus: true
    }
}