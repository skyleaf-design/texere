import QtQuick 2.0
import QtQuick.Controls 1.0
import "qrc:/custom"

ApplicationWindow
{
  visible: true
  width: 640
  height: 480
  title: qsTr("Minimal Qml")

  Red {
    anchors.left: parent.left
  }
  Blue {
    anchors.right: parent.right
  }
}