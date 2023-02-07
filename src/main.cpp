#include <QtWidgets/QApplication>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>

#include "window.hpp"
#include "report/reportpage.hpp"

  int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    mtobridge::Window window;
    mtobridge::ReportPage* reportPage =
        new mtobridge::ReportPage(window.getTabWidget());
    window.show();
    
    int ret;
    try {
      ret = app.exec();
    } catch (std::exception& e) {
      QMessageBox::critical(
          nullptr, QString("Unknown Error!"),
          QString("An exception has occurred! {%1}").arg(e.what()));
    } catch (const matlab::Exception& e) {
      QMessageBox::critical(
          nullptr, QString("Unknown Error!"),
          QString("A MATLAB exception has occurred! {%1}").arg(e.what()));
    }
    delete reportPage;
    return ret;
  }