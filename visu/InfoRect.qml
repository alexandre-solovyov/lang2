
import QtQuick 2.0
import com.alex.lang 1.0;

Item {
    id: rootId;
    width: internalInfoId.implicitWidth + 10;
    height: internalInfoId.implicitHeight + 10;

    property Item item: null;
    property TextModel model: null;

    Rectangle {
        id: rectId;
        anchors.fill: parent;
        color: "#90CAF9";
        radius: 10;

        Text {
            id: internalInfoId;
            anchors.fill: parent;
            text: "test";
            color: "#283593";
            font.pointSize: 16;
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
    }

    onItemChanged: {
        var text = "";
        if(item.isKnown)
            text = modelId.translation(item.text);
        else
            text = "Unknown";

        internalInfoId.text = text;
        visible = item.isWord;
    }
}
