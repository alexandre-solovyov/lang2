
import QtQuick 2.9;
import QtQuick.Controls 2.3;
import QtQuick.Layouts 1.0;

Item {
    id: rootId;

    property alias label: labelId.text;
    property alias value: valueId.text;
    property font font;
    property int margin: 10;

    height: containerId.height;

    RowLayout {
        id: containerId;
        width: parent.width;
        spacing: 0;

        Rectangle {
            id: rectId;
            width: labelId.implicitWidth + 10;
            height: labelId.implicitHeight + 10;
            color: 'white';
            opacity: 0.9;
            radius: 10;
            Layout.leftMargin: rootId.margin;

            Text {
                id: labelId;
                anchors.fill: parent;
                font: rootId.font;
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
            }
        }

        Rectangle {
            id: rect2Id;
            height: rectId.height;
            color: 'white';
            opacity: 0.9;
            radius: 10;

            Layout.fillWidth: true;
            Layout.leftMargin: rootId.margin;
            Layout.rightMargin: rootId.margin;

            TextEdit {
                id: valueId;

                x: margin;
                width: rect2Id.width - 2*margin;
                y: (rect2Id.height - implicitHeight)/2;
                height: implicitHeight;

                focus: true;
                font: rootId.font;
            }
        }
    }
}
