#pragma once

#include <QtCharts>
#include <QtWidgets>

#include "report.hpp"

namespace mtobridge {
class ReportPage : public QWidget {
  Q_OBJECT

 public:
  ReportPage(QTabWidget *parent = nullptr);
  ~ReportPage();

  Report getReport();
  void updateReport(Report newReport);

// signals:
//  void runCommand(Engine::concernedOneMomentInput);

 public slots:
  void errorOccurred(QString);

 private:
  void createPage();

  Report report;
};
};  // namespace mtobridge
