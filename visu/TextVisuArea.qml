
import QtQuick 2.9
import QtQuick.Controls 2.3;

Item {
    id: rootId;
    property alias flow_spacing: flowId.spacing;
    property int spacing: 20;
    property int v_spacing: 1;
    property int fontSize: 18;
    property int maxWidth: 1000;

    signal itemSelectedByClick(int globalX, int globalY);

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
            spacing: 5;

            Repeater {
                id: repeatId;
                model: modelId;

                delegate: Word {
                    spacing: rootId.spacing;
                    v_spacing: rootId.v_spacing;
                    fontSize: rootId.fontSize;
                    maxWidth: rootId.maxWidth;
                    text: m_text;
                    translation: m_translation;
                    isWord: m_isWord;
                    isKnown: m_isKnown;

                    onSelectedByClick: {
                        modelId.select(this);
                        var globalPoint = this.mapToGlobal(0, 0);
                        //console.log(globalPoint);
                        itemSelectedByClick(globalPoint.x, globalPoint.y);
                    }
                }
            }
        }
    }
}
