
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

    Image {
        anchors.fill: parent;
        source: "images/meadow.jpg";
        opacity: 0.5;
    }

    ColumnLayout {
        spacing: 10;
        x: 10;
        y: 10;
        width: parent.width-2*x;
        height: parent.height-2*y;

        Rectangle {
            Layout.fillWidth: true;
            height: 80;
            color: "#00AA00";
            opacity: 0.5;

            RowLayout {
                x: 10;
                y: 8;
                spacing: 20;

                Image {
                    source: "images/open.png";
                }
                Image {
                    source: "images/prev.png";
                }
                Image {
                    source: "images/next.png";
                }
            }
        }

        TextVisuArea {

            Layout.fillWidth: true;
            Layout.fillHeight: true;
            maxWidth: mainId.width;

            onItemSelectedByClick: {
                var item = modelId.selectedItem();
                infoId.x = x + 10;
                infoId.y = y;
                infoId.item = item;
            }
        }

        Row {
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
        visible: false;
    }
}
