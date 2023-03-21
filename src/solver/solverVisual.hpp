#pragma once

#include <QtCharts>
#include <QtWidgets>

#include "../report/report.hpp"
#include "util/data_types.hpp"

#define ANIMATION_TIME 15000    //Total time the animation should take in miliseconds

namespace mtobridge {
class SolverVisual : public QWidget {
  Q_OBJECT

 public:
  SolverVisual(QWidget* parent) : QWidget(parent) { createPage(); };
  ~SolverVisual(){};

  void setBridge(QGraphicsScene*);
  void showEvent(QShowEvent* showEvent);
  void setPlatoon(QGraphicsScene*);
  void visualize();

 signals:
  void runCommand(MockCalculationInputT);

 public slots:
  void errorOccurred(QString);
  void updateChart(MockCalculationInputT, MockCalculationOutputT);

 private:
   int animationMin;
   int animationMax;
   int animationInc;
   int animationSpeed;
   enum {NotLoaded, AtBeginning, AtEnd, Paused, RunningForward, RunningBackward} animationStatus;

  QGroupBox* forceSettingGroup;
  QGroupBox* solverSettingGroup;
  // Force setting window
  // Solver setting window
  QPushButton* calculateButton;
  QPushButton* lastFrameButton;
  QPushButton* animationButton;
  QPushButton* nextFrameButton;
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

  QLabel* concernedSectionLabel;
  QLineEdit* concernedSectionReminder;
  QLabel* discretizationLengthLabel;
  QLineEdit* discretizationLengthReminder;

  Report mReport;

  QList<QGraphicsItemGroup*>* groups;

  bool nextFrame();
  void animateForward();
  bool lastFrame();
  void animateBackward();
  void setUpAnimation();
  void createPage();
  void updatePage();
};
};  // namespace mtobridge
