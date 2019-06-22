
import QtQuick 2.9;
import QtQuick.Controls 2.3;
import QtQuick.Layouts 1.2;
import QtQuick.Window 2.2;
import com.alex.lang 1.0;

Window {
    visible: true;
    width: 1024;
    height: 768;
    title: qsTr("Text Visualizer Demo");
    id: mainId;

    TextModel {
        id: modelId;
        language: "de";
        fileName: "1_course_beginner.txt";
        /*language: "en";
        fileName: "5_Baum_Oz_1.txt";
        trim: true;
        limit: 1000;*/

        function setAsKnown(text, index) {
            setAsKnownCpp(text, index);
            textVisuId.setAsKnown(text);
        }
    }

    Helper {
        id: helperId;
        language: modelId.language;
    }

    Image {
        anchors.fill: parent;
        source: "images/meadow.jpg";
        opacity: 0.5;
    }

    ColumnLayout {
        id: containerId;

        spacing: 10;
        x: 10;
        y: 10;
        width: parent.width-2*x;
        height: parent.height-2*y;

        Rectangle {
            Layout.fillWidth: true;
            height: 80;
            color: "#00AA00";
            opacity: 0.5;

            RowLayout {
                x: 10;
                y: 8;
                spacing: 20;

                Image {
                    source: "images/open.png";
                }
                Image {
                    source: "images/prev.png";
                }
                Image {
                    source: "images/next.png";
                }
            }
        }

        TextVisuArea {
            id: textVisuId;
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            maxWidth: mainId.width;
            objectName: "text_visu_area";

            onItemSelectedByClick: {
                var item = modelId.selectedItem();
                var localX = globalX - mainId.x
                var localY = globalY - mainId.y;
                infoId.x = localX + 10;
                infoId.y = localY + item.height;
                infoId.item = item;
                addPanelId.show(item);
            }
        }
    }

    InfoRect {
        id: infoId;
        model: modelId;
        visible: false;
    }

    AddPanel {
        id: addPanelId;

        x: mainId.width - width - containerId.spacing;
        y: textVisuId.y + containerId.spacing;
        width: mainId.width * 0.4;
        height: mainId.height - y - containerId.spacing;

        font.pointSize: 16;
        categories: helperId.categories;
        visible: false;

        helper: helperId;
        model: modelId;

        function show(item) {

            text = item.text.toLowerCase();
            translation = "";

            visible = !item.isKnown;
            if(visible)
                dirTranslation();
        }

        onDirTranslation: {
            translate(addPanelId.text, helperId.language, "ru", function(translation) {
                addPanelId.translation = translation;
                console.log("Tr: " + translation);
            });
        }

        onRevTranslation: {
            translateWithDict(addPanelId.translation, "ru", helperId.language, function(translation) {
                addPanelId.text = translation;
                console.log("Rev tr: " + translation);
            });
        }
    }

    Rectangle {
        id: nbUnknownId;
        x: mainId.width - width - containerId.spacing;
        y: containerId.spacing;
        width: 120;
        height: 80;
        color: "white";
        opacity: 0.75;

        Text {
            anchors.fill: parent;
            font.pointSize: 22;
            text: modelId.nbUnknown;
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }
    }

    function parseDict(data, lang, callback) {
        var tr = data.def[0].tr[0];
        var art = '';
        if(lang==="de") {
            if(tr.gen==="m")
               art = 'der ';
            else if(tr.gen==="f")
               art = 'die ';
            else if(tr.gen==="n")
               art = 'das ';
        }
        callback(art + tr.text);
    }

    function translateWithDict(text, lang1, lang2, callback) {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if (xhr.readyState===XMLHttpRequest.HEADERS_RECEIVED) {
                console.log("Headers received");
            } else if(xhr.readyState===XMLHttpRequest.DONE) {
                if(xhr.status===200) {
                    var data = JSON.parse(xhr.responseText.toString());
                    parseDict(data, lang2, callback);
                } else {
                    callback("");
                }
            }
        }
        var key2 = "dict.1.1.20190622T145724Z.7ea4b950838f66b7.5d5be843c6cbe9e93a204eb670957dc230d0e990";
        var url = "https://dictionary.yandex.net/api/v1/dicservice.json/lookup?key=" + key2 + "&lang=" + lang1 + "-" + lang2 + "&text=" + text;
        xhr.open("POST", url);
        xhr.send();
    }

    function translate(text, lang1, lang2, callback) {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if (xhr.readyState===XMLHttpRequest.HEADERS_RECEIVED) {
                console.log("Headers received");
            } else if(xhr.readyState===XMLHttpRequest.DONE) {
                if(xhr.status===200) {
                    var data = JSON.parse(xhr.responseText.toString());
                    callback(data.text.join(" ").toLowerCase());
                } else {
                    callback("<error>");
                }
            }
        }

        var url = "https://translate.yandex.net/api/v1.5/tr.json/translate?key=trnsl.1.1.20190621T185111Z.273701bcf5a4a70b.5cfddf72b96400a5db01e0b8b3c63dd22caf5abd&text="+text+"&lang="+lang1+"-"+lang2
        xhr.open("POST", url);
        xhr.send();
    }
}
