
import QtQuick 2.9;
import QtQuick.Controls 2.3;

Item {
    id: rootId;

    property font font;

    Rectangle {
        anchors.fill: parent;
        color: "#81C784";
        opacity: 0.5;

        TextField {
            label: "Word";
        }

        TextField {
            label: "Translation";
        }

        ComboBox {
            width: parent.width;
            height: 50;
            font: rootId.font;
            model: [ "Banana", "Apple", "Coconut" ]
        }
    }
}
