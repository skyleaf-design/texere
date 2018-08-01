import QtQuick.Layouts 1.11
import QtQuick 2.11
import QtQuick.Controls 1.0

ApplicationWindow
{
  visible: true
  width: 640
  height: 480
  title: qsTr("Minimal Qml")

  RowLayout {
    id: layout
    anchors.fill: parent
    spacing: 6
    Rectangle {
      color: 'gray'
      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.preferredWidth: 64
      Layout.maximumWidth: 64
      Layout.minimumWidth: 64
    }

    Rectangle {
      color: "teal"
      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.minimumWidth: 200
      Layout.preferredWidth: 250
      Layout.maximumWidth: 300
      ListView {
        anchors.fill: parent
        model: api_results
        delegate: Rectangle {
          Column {
            Text { text: name }
            Text { text: email }
          }
        }
      }
    }
    

    ListModel {
      id: api_results
      ListElement { name: "My Self"; email: "some@some.com" }
      ListElement { name: "Schlomo Vaknin"; email: "some@schlomo.com" }
    }


    Rectangle {
      color: 'plum'
      Layout.fillWidth: true
      Layout.fillHeight: true
      TextArea {
        anchors.fill: parent
        text: "TextArea\n...\n...\n...\n...\n...\n...\n"
      }
    }
  }
}