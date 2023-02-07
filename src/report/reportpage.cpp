#include "reportpage.hpp"

#include <sstream>

namespace mtobridge {
ReportPage::ReportPage(QTabWidget* parent) : QWidget(parent) {
  createPage();
  parent->addTab(this, "Report");
}

ReportPage::~ReportPage() {
  
}

Report ReportPage::getReport() { return report; }

void ReportPage::updateReport(Report newReport) { report = newReport; }

void ReportPage::errorOccurred(QString error) {
  QMessageBox::critical(this, QString("Unknown Error!"), error);
}

void ReportPage::createPage() {
  setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                            QSizePolicy::Policy::Expanding));
  auto* pageLayout = new QHBoxLayout();
  setLayout(pageLayout);
}
};  // namespace mtobridge