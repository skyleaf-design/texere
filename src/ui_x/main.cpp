#include <QtWidgets>
#include "TexereWindow.h"



int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  TexereWindow the_window;
  the_window.show();

  return app.exec();
}
