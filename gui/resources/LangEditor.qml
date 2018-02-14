import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {

    id: editor_page

    width: 600
    height: 400

    title: qsTr("Editor")
    property string fileName;

    TextEdit {
        id: editor_textedit

        font.family: "Courier New"
        font.pointSize: 12
        color: "blue"

        anchors.fill: parent
        focus: true
        wrapMode: TextEdit.Wrap
    }

    Component.onCompleted: fileName = 'D:/asl/lang3/lang/progress/french/fr_noms.lang'

    onFileNameChanged:
    {
        editor_textedit.text = gui_model.readFile(fileName)
    }
}
