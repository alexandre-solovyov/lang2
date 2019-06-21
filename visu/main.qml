
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

        function setAsKnown(text, index) {
            setAsKnownCpp(text, index);
            textVisuId.setAsKnown(text);
        }
    }

    Helper {
        id: helperId;
        path: "/home/alex/lang/progress/german";
    }

    Image {
        anchors.fill: parent;
        source: "images/meadow.jpg";
        opacity: 0.5;
    }

    ColumnLayout {
        id: containerId;

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
            id: textVisuId;
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            maxWidth: mainId.width;
            objectName: "text_visu_area";

            onItemSelectedByClick: {
                var item = modelId.selectedItem();
                var localX = globalX - mainId.x
                var localY = globalY - mainId.y;
                infoId.x = localX + 10;
                infoId.y = localY + item.height;
                infoId.item = item;

                addPanelId.text = item.text;
                //console.log(item.wordIndex);
                addPanelId.itemIndex = item.wordIndex;
                addPanelId.translation = "";
                addPanelId.visible = !item.isKnown;
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

        x: mainId.width - width - containerId.spacing;
        y: textVisuId.y + containerId.spacing;
        width: mainId.width * 0.4;
        height: mainId.height - y - containerId.spacing;

        font.pointSize: 16;
        categories: helperId.categories;
        visible: false;

        helper: helperId;
        model: modelId;
    }
}
