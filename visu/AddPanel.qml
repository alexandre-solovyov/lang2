
import QtQuick 2.9;
import QtQuick.Controls 2.4;
import QtQuick.Controls.Styles 1.4;
import QtQuick.Layouts 1.2;

Item {
    id: rootId;

    property font font;
    property alias text: wordId.value;
    property alias translation: translationId.value;
    property variant categories;
    property int margin: 10;

    Rectangle {
        id: mainId;
        anchors.fill: parent;
        color: "#81C784";
        opacity: 0.75;

        ColumnLayout {
            spacing: 0;
            width: mainId.width;

            ComboBox {
                id: categoryId;
                width: parent.width;
                height: 50;
                font: rootId.font;
                model: categories;

                Layout.leftMargin: rootId.margin;
                Layout.rightMargin: rootId.margin;
                Layout.topMargin: rootId.margin;
                Layout.fillWidth: true;

                delegate: ItemDelegate {

                    width: categoryId.width;
                    highlighted: categoryId.highlightedIndex === index;

                    contentItem: Rectangle {

                        color: highlighted ? "darkgreen" : "white";
                        anchors.fill: parent;
                        opacity: mainId.opacity;

                        Text {
                            anchors.fill: parent;
                            text: " " + modelData;
                            color: highlighted ? "white" : "darkgreen";
                            font: categoryId.font;
                            elide: Text.ElideRight;
                            verticalAlignment: Text.AlignVCenter;
                        }
                    }
                }
            }

            TextField {
                id: wordId;
                label: "Word:";
                font: rootId.font;
                Layout.fillWidth: true;
                Layout.topMargin: rootId.margin;
            }

            TextField {
                id: translationId;
                label: "Translation:";
                font: rootId.font;
                Layout.fillWidth: true;
                Layout.topMargin: rootId.margin;
            }
        }
    }
}
