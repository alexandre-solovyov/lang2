import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {

    id: exercise_page

    width: 600
    height: 400

    title: qsTr("Exercise")

    property int mainPSize: 20
    property int bigPSize: 30
    property int margin: 20
    property int state: 0

    property alias question1 : part1.text
    property alias question2 : part2.text

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height/2 - 3*margin

        Text { id: part1; color: "blue"; font.pointSize: mainPSize; }
        Text { id: quest; text: "<?>"; color: "green"; font.pointSize: bigPSize; }
        Text { id: part2; color: "blue"; font.pointSize: mainPSize; }

    }

    RowLayout {
        x: margin
        y: parent.height/2 - 2*margin
        width: parent.width - 2*margin

        TextField {
            id: user_answer
            color: "green"
            font.pointSize: bigPSize
            Layout.fillWidth: true
        }
        Button {
            id: check_btn
            text: "Check"
            Layout.fillWidth: false

            onClicked:
            {
                var ok = gui_model.checkAnswer(user_answer.text);
                exercise_page.state = ok ? 1 : -1;
                quest.text = gui_model.answer();
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
}
