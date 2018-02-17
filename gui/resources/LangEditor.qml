import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {

    id: editor_page

    width: 600
    height: 400

    //title: qsTr("Editor")
    property string fileName;

    Flickable {
        id: flick

        anchors.fill: parent

        clip: true

        function ensureVisible(r)
        {
            if (contentX >= r.x)
                contentX = r.x;
            else if (contentX+width <= r.x+r.width)
                contentX = r.x+r.width-width;
            if (contentY >= r.y)
                contentY = r.y;
            else if (contentY+height <= r.y+r.height)
                contentY = r.y+r.height-height;
        }

        TextEdit {
            id: editor_textedit

            font.family: "Courier New"
            font.pointSize: 12
            color: "blue"

            anchors.fill: parent
            focus: true
            wrapMode: TextEdit.Wrap

            onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)

            Keys.onPressed: {
                if (event.key == Qt.Key_PageDown)
                {
                    editor_textedit.cursor += 20;
                    event.accepted = true;
                }
            }
        }
    }

    Component.onCompleted: fileName = 'D:/asl/lang3/lang/progress/french/fr_noms.lang'

    onFileNameChanged:
    {
        editor_textedit.text = gui_model.readFile(fileName)
    }
}
