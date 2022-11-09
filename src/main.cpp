#include <QtWidgets/QApplication>
#include <exception>
#include <iostream>
#include <string>

#include "window.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  mtobridge::Window window;
  window.show();
  return app.exec();
}