import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    id: main_window

    visible: true
    width: 640
    height: 480
    title: qsTr("Lang")

    property alias pageName: label.text

    Rectangle
    {
        id: title_rect

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 50
        color: "blue"

        Text {
            id: label

            text: "Hello"
            color: "white"
            font.pointSize: 20
            font.family: "Verdana"
            anchors.centerIn: parent
        }
    }

    StackView {
        id: stackView

        initialItem: exercise_page
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: title_rect.bottom
        anchors.bottom: parent.bottom

        Component.onCompleted: exercise_page.newExercise()
    }

    Exercise
    {
        id: exercise_page

        function newExercise()
        {
            var parts = gui_model.randomExercise();
            main_window.pageName = exercise_page.title

            question1 = parts[0];
            questmid = "<?>"
            question2 = parts[1];
            state = 0;
            user = "";
        }
    }
}
