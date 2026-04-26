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
                backend.processFolder(pathField.text, filetype.tyle)
            }
        }

        ComboBox {
            id: filesTypeBox
            model: [
                { text: "txt", value: ".txt"},
                { text: "docx", value: ".docx" },
                { text: "Все", value: "." }
            ]
            textRole: "text"
            valueRole: "value"
            onAccepted: {
                if (find(editText) === -1)
                    model.append({text: editText})
            }
            // Set currentValue to the value stored in the backend.

            // When an item is selected, update the backend.
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
}
