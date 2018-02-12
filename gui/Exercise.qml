import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {

    id: exercise_page

    width: 600
    height: 400

    title: qsTr("Exercise")

    property alias question1 : part1.text;
    property alias question2 : part2.text;

    GridLayout {
        id: grid
        columns: 3
        anchors.centerIn: parent

        Text { id: part1; color: "blue"; font.pointSize: 20; }
        Text { text: "<?>"; color: "green"; font.pointSize: 30; }
        Text { id: part2; color: "blue"; font.pointSize: 20; }
    }
}
