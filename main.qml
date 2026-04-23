import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2
import QtQuick.Dialogs

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Card Search")

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
                backend.processFolder(pathField.text)
            }
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
