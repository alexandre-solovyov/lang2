
import QtQuick 2.9;
import QtQuick.Controls 2.3;
import QtQuick.Layouts 1.2;
import QtQuick.Window 2.2;
import com.alex.lang 1.0;

Window {
    visible: true;
    width: 1024;
    height: 768;
    title: qsTr("Text Visualizer Demo");
    id: mainId;

    TextModel {
        id: modelId;
        //fileName: "4_Peter_Pan.txt";
        fileName: "1_course_beginner.txt";
    }

    ColumnLayout {
        spacing: 10;
        anchors.fill: parent;

        TextVisuArea {

            Layout.fillWidth: true;
            Layout.fillHeight: true;
            maxWidth: mainId.width;

            onItemSelectedByClick: {
                var item = modelId.selectedItem();
                infoId.x = x;
                infoId.y = y;
                infoId.item = item;
            }
        }
    }

    InfoRect {
        id: infoId;
        model: modelId;
        visible: false;
    }

    AddPanel {
        id: addPanelId;
        x: mainId.width - width;
        y: 0;
        width: 300;
        height: mainId.height;
        font.pointSize: 16;
    }
}
