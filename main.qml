import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2
import QtQuick.Dialogs
import QtQuick.Window

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Card Search")
    color:"#ADD8E6"

    QtObject {
        id: filetype
        property string type
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        TextField {
            id: pathField
            width: 300
            placeholderText: "Выберите директорию"
            text: folderDialog.selectedFolder

            readOnly: true
        }

        Button {
            text: "Выбрать папку"
            onClicked: folderDialog.open()
        }

        Button {
            text: "Старт"
            onClicked: {
                backend.processFolder(pathField.text, filesTypeBox.currentValue)
            }
        }

        ComboBox {
            id: filesTypeBox
            model: [
                { text: "txt", value: ".txt"},
                { text: "png", value: ".png" },
                { text: "Все", value: "." }
            ]
            textRole: "text"
            valueRole: "value"
            onActivated: filetype.type = currentValue
        }
    }

    FolderDialog {
        id: folderDialog
        title: "Выбор директории"

        onAccepted: {
            pathField.text = selectedFolder
        }
    }

    Popup {
        id: finishedPopup
        modal: true
        focus: true
        anchors.centerIn: parent

        width: 200
        height: 100

        Label {
            anchors.centerIn: parent
            text: "Сканирование завершено"
        }
    }

    Connections {
        target: backend

        function onScanningFinished() {
            finishedPopup.open();
        }
    }
}
