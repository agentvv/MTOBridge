#pragma once

#include <QtCharts>
#include <QtWidgets>

namespace mtobridge {
class ReportPage : public QWidget {
  Q_OBJECT

 public:
  ReportPage(QTabWidget *parent = nullptr);
  ~ReportPage();

// signals:
//  void runCommand(Engine::concernedOneMomentInput);

 public slots:
  void errorOccurred(QString);

 private:
  void createPage();
  
};
};  // namespace mtobridge
