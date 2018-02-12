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

            onClicked: gui_model.checkAnswer(user_answer.text)
        }
    }
}
