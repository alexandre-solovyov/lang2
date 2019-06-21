
import QtQuick 2.9
import QtQuick.Layouts 1.2;

Item {
    id: rootId;
    property int spacing: 0;
    property int v_spacing: 1;
    property alias fontSize: internalTextId.font.pointSize;
    property color knownColor: "#aed581";
    property color unknownColor: "#f48fb1";
    property int maxWidth: 1000;

    property alias text: internalTextId.text;
    property string translation: "";
    property bool isWord: true;
    property bool isKnown: true;
    property int wordIndex: 0;

    property bool selection: false;
    signal selectedByClick();

    width: {
        if (text==="\r")
            maxWidth;
        else
            internalTextId.implicitWidth + spacing;
    }
    height: {
        if (text==="\r")
            rootId.v_spacing;
        else
            internalTextId.implicitHeight;
    }

    Rectangle {
        anchors.fill: parent;
        radius: 10;
        border.color: {
            if(selection)
                "red";
            else
                "lightblue";
        }
        border.width: {
            if(text==="\r" || text==="  ")
                1;
            else if(selection)
                2;
            else
                1;
        }
        color: {
            if(text==="\r" || text==="  " || !isWord)
                "lightgray";
            else if (isKnown)
                knownColor;
            else
                unknownColor;
        }
        opacity: {
            if(text==="\r" || text==="  ")
                0.0;
            else if(!isWord)
                0.5;
            else
                1.0;
        }


        Layout.fillWidth: true;
        Text {
            id: internalTextId;
            anchors.fill: parent;
            color: rootId.isWord ? "darkblue" : "black";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                selectedByClick();
            }
        }
    }
}
