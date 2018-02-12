import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Stack")

    header: ToolBar {
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
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Exercise")
                width: parent.width
                onClicked: {
                    exercise();
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Statistics")
                width: parent.width
                onClicked: {
                    stackView.push("Statistics.qml")
                    drawer.close()
                }
            }
        }

        Component.onCompleted: exercise();
    }

    Exercise
    {
        id: exercise_page

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

    function exercise()
    {
        stackView.push(exercise_page)
        exercise_page.newExercise()
    }

    StackView {
        id: stackView
        initialItem: "HomeForm.qml"
        anchors.fill: parent
    }
}
