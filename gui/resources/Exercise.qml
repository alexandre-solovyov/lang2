import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Rectangle {

    id: exercise_page

    property string title: qsTr("Exercise")

    property int mainPSize: 20
    property int bigPSize: 30
    property int margin: 20
    property int state: 0

    property alias question1 : part1.text
    property alias questmid  : quest.text
    property alias question2 : part2.text
    property alias user      : user_answer.text

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height/2 - 3*margin

        Text { id: part1; color: "blue"; font.pointSize: mainPSize; }
        Text { id: quest; color: "green"; font.pointSize: bigPSize; }
        Text { id: part2; color: "blue"; font.pointSize: mainPSize; }
    }

    RowLayout {
        x: margin
        y: parent.height/2
        width: parent.width - 2*margin

        TextField {
            id: user_answer
            textColor: "magenta"
            font.pointSize: bigPSize
            Layout.fillWidth: true

            Keys.onPressed:
            {
                if (event.key == Qt.Key_Return)
                {
                    exercise_page.check()
                    event.accepted = true;
                }
            }
        }
        Button {
            id: check_btn
            text: "Check"
            Layout.fillWidth: false

            onClicked:
            {
                exercise_page.check()
            }
        }
    }


    Image {
        id: state_img
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    onStateChanged:
    {
        if(state==0)
            state_img.source = ""
        else if( state==1)
            state_img.source = "image_ok.png"
        else
            state_img.source = "image_fail.png"
    }

    function check()
    {
        if(exercise_page.state == 0)
        {
            user_answer.text = gui_model.normalize(user_answer.text)
            var ok = gui_model.checkAnswer(user_answer.text);
            exercise_page.state = ok ? 1 : -1;
            quest.text = gui_model.answer();
        }
        else
            exercise_page.newExercise()
    }
}
