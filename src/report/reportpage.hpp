#pragma once

#include <QtCharts>
#include <QtWidgets>

#include "report.hpp"

namespace mtobridge {
class ReportPage : public QWidget {
  Q_OBJECT

 public:
  ReportPage(QWidget *parent = nullptr);
  ~ReportPage();

  Report getReport();
  void updateReport(Report newReport);

 public slots:
  void errorOccurred(QString);

 private:
  void createPage();

  Report report;

  QPushButton *saveButton;
};
};  // namespace mtobridge
