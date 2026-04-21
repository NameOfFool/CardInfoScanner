import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Card Search")

    ColumnLayout {
        anchors.fill: parent
        anchors.margin: 15
        spacing: 10

        Label{
            text: "Путь поиска"
        }

        TextField{
            id: pathField
            placeholderText: "/path/to/file"
            Layout.fillWidth: true;
        }

        CheckBox {
            id: deepScanCheck
            text: "Enable deep scan"
        }

        Button {
                    text: "Start"
                    Layout.fillWidth: true

                    onClicked: {
                        console.log("Path:", pathField.text)
                        console.log("Deep scan:", deepScanCheck.checked)

            // здесь потом дергаешь C++ backend
            }
        }
    }
}
