#include "reportpage.hpp"
#include "../saver/saver.hpp"

#include <sstream>

namespace mtobridge {
ReportPage::ReportPage(QWidget* parent) : QWidget(parent) {
  createPage();
}

ReportPage::~ReportPage() {
  
}

Report ReportPage::getReport() { return report; }

void ReportPage::updateReport(Report newReport) {
  report = newReport;

  //validate report has all data, enable/disable save button as appropriate
  //saveButton->setDisabled(false);
}

void ReportPage::errorOccurred(QString error) {
  QMessageBox::critical(this, QString("Unknown Error!"), error);
}

void ReportPage::createPage() {
  setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                            QSizePolicy::Policy::Expanding));
  auto* pageLayout = new QHBoxLayout();
  setLayout(pageLayout);

  //button
  {
    saveButton = new QPushButton("Save", this);
    saveButton->setFixedWidth(64);
    //saveButton->setDisabled(true);
    pageLayout->addWidget(saveButton);

    QObject::connect(saveButton, &QPushButton::clicked, this, [&]() {
      mtobridge::saver::saveReport(report);
    });
  }
}
};  // namespace mtobridge