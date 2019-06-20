
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
        fileName: "D:/lang/texts/english/1_North_wind_and_the_Sun.txt";
    }

    Flickable {
        id: flickable;
        anchors.fill: parent;
        contentHeight: flowId.implicitHeight;
        clip: true;
        ScrollBar.vertical: ScrollBar{}

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
                }
            }
        }
    }
}
