import QtQuick 2.2
import QtQuick.Controls 1.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Lang")

    /*header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }*/

    /*Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            Item {
                text: qsTr("Exercise")
                width: parent.width
                onClicked: {
                    exercise();
                    drawer.close()
                }
            }
            Item {
                text: qsTr("Statistics")
                width: parent.width
                onClicked: {
                    stackView.push("Statistics.qml")
                    drawer.close()
                }
            }
            Item {
                text: qsTr("Editor")
                width: parent.width
                onClicked: {
                    stackView.push(editor_page)
                    drawer.close()
                }
            }
        }

        Component.onCompleted: exercise();
        //Component.onCompleted: stackView.push(editor_page)
    }*/

    Exercise
    {
        id: exercise_page
        width: stackView.width
        height: stackView.height

        function newExercise()
        {
            var parts = gui_model.randomExercise();
            question1 = parts[0];
            questmid = "<?>"
            question2 = parts[1];
            state = 0;
            user = "";
        }
    }

    LangEditor
    {
        id: editor_page
        width: stackView.width
        height: stackView.height
    }

    function exercise()
    {
        stackView.push(exercise_page)
        exercise_page.newExercise()
    }

    StackView {
        id: stackView
        //initialItem: "HomeForm.qml"
        initialItem: exercise_page
        anchors.fill: parent
    }
}
