
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

    Flickable {
        id: flickable;
        anchors.fill: parent;
        contentHeight: flowId.implicitHeight;
        clip: true;
        ScrollBar.vertical: ScrollBar{
            id: vScrollId;
        }

        Flow {
            id: flowId;
            anchors.fill: parent;
            flow: Flow.LeftToRight;
            layoutDirection: Qt.LeftToRight;
            spacing: 10;

            Repeater {
                id: repeatId;
                model: modelId;

                delegate: Word {
                    spacing: 15;
                    fontSize: 18;
                    maxWidth: mainId.width;
                    text: m_text;
                    translation: m_translation;
                    isWord: m_isWord;
                    isKnown: m_isKnown;

                    onSelectedByClick: {
                        modelId.select(this);
                        infoId.x = this.x + this.width;
                        var d = vScrollId.position * flowId.height;
                        infoId.y = this.y + this.height - d;
                        //console.log(vScrollId.position);
                        infoId.visible = true;
                        internalInfoId.text = modelId.translation(this.text);
                    }
                }
            }
        }
    }

    Rectangle {
        id: infoId;
        width: internalInfoId.implicitWidth + 10;
        height: internalInfoId.implicitHeight + 10;
        color: "dodgerblue";
        visible: false;

        Text {
            id: internalInfoId;
            anchors.fill: parent;
            text: "test";
            color: "white";
            font.pointSize: 16;
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
    }
}
