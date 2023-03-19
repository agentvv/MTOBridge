#pragma once

#include <QtCharts>
#include <QtWidgets>

#include "../report/report.hpp"
#include "util/data_types.hpp"

namespace mtobridge {
class SolverVisual : public QWidget {
  Q_OBJECT

 public:
  SolverVisual(QWidget* parent) : QWidget(parent) { createPage(); };
  ~SolverVisual(){};

  void setBridge(QGraphicsScene*);
  void setPlatoon(QGraphicsScene*);
  void visualize();

 signals:
  void runCommand(MockCalculationInputT);

 public slots:
  void errorOccurred(QString);
  void updateChart(MockCalculationInputT, MockCalculationOutputT);

 private:
  QGroupBox* forceSettingGroup;
  QGroupBox* solverSettingGroup;
  // Force setting window
  // Solver setting window
  QPushButton* calculateButton;
  QPushButton* saveButton;
  QGroupBox* saveLoadGroup;
  // QPushButton* saveButton;
  // QPushButton* loadButton;
  // Truck + bridge window
  QChart* mChart;
  QChartView* mChartView;

  // Force Envelope Chart
  QChart* mEnvelopeChart;
  QChartView* mEnvelopeChartView;

  QRadioButton* positiveMomentButton;
  QRadioButton* negativeMomentButton;
  QRadioButton* shearButton;
  QRadioButton* concernedButton;
  QRadioButton* criticalButton;

  QGraphicsView* truckVisual;
  QGraphicsView* bridgeVisual;

  Report mReport;

  void createPage();
  void updatePage();
};
};  // namespace mtobridge
