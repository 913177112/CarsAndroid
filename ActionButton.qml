import QtQuick 2.5
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.3

Rectangle {
    id: actionButton
    property color buttonColor: "#FF8C00"
    property string buttonText
    property int fontSize: screenH/70
    property int buttonRadius: 5
    signal activated()
    property bool isActivated: false;
    color : buttonColor
    radius: buttonRadius

    Text {
        id: btnText
        anchors.horizontalCenter: actionButton.horizontalCenter
        anchors.verticalCenter: actionButton.verticalCenter
        text: actionButton.buttonText
        font.pointSize: actionButton.fontSize
        color: "white"
    }

    MouseArea {
        id: mouseArea;
        anchors.fill: actionButton
        onClicked: {
            isActivated = true;
            btnClickAnimation.running = true
        }
    }

    SequentialAnimation {
        id: btnClickAnimation
        PropertyAnimation { target: actionButton; property: "opacity"; easing.type: Easing.Linear; to: 0; duration: 30 }
        PropertyAnimation { target: actionButton; property: "opacity"; easing.type: Easing.Linear; to: 1; duration: 30 }
        onRunningChanged: {
            if (btnClickAnimation.running) {}
            else { actionButton.activated() }
        }
    }

 } // Rectangle
