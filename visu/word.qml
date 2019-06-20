
import QtQuick 2.9
import QtQuick.Layouts 1.2;

Item {
    id: rootId;
    property int spacing: 0;

    property alias text: internalTextId.text;
    property string translation: "";
    property bool isWord: true;
    property bool isKnown: true;
    property int maxWidth: 1000;

    property alias fontSize: internalTextId.font.pointSize;

    width: {
        if (text==="\r")
            maxWidth;
        else
            internalTextId.implicitWidth + spacing;
    }
    height: {
        if (text==="\r")
            rootId.spacing;
        else
            internalTextId.implicitHeight;
    }

    Rectangle {
        anchors.fill: parent;
        border.color: "lightblue";
        border.width: {
            if(text==="\r" || text==="  ")
                0;
            else
                1;
        }
        color: "white";
        Layout.fillWidth: true;
        Text {
            id: internalTextId;
            anchors.fill: parent;
            color: rootId.isWord ? "darkblue" : "lightgray";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
    }
}
