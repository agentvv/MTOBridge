#pragma once

#include <QtCharts>
#include <QtWidgets>
#include <QtGui>
#include "../engine/engine.hpp"

namespace mtobridge {
class Window : public QWidget {
  Q_OBJECT

 public:
  Window(QWidget *parent = nullptr);
  ~Window() { Engine::getInstance().stopEngine(); };
  QTabWidget *getTabWidget();

  QGraphicsScene* scene;

 signals:
  void runCommand(MockCalculationInputT);

 public slots:
  void errorOccurred(QString);

 private:
  void createWindow();

  QTabWidget *mTabWidget;
  QWidget *mPage;

  QWidget *mInputWidget;
  QLabel *mAxleLoadLabel;
  QLineEdit *mAxleLoad;
  QLabel *mAxleSpacingLabel;
  QLineEdit *mAxleSpacing;
  QLabel *mNumberOfTrucksLabel;
  QLineEdit *mNumberOfTrucks;
  QLabel *mHeadwayLabel;
  QLineEdit *mHeadway;
  QLabel *mSpanLengthLabel;
  QLineEdit *mSpanLength;
  QLabel *mConcernedSectionLabel;
  QLineEdit *mConcernedSection;
  QLabel* mNumberSpansLabel;
  QLineEdit* mNumberSpans;
  QLabel* mDiscretizationLengthLabel;
  QLineEdit* mDiscretizationLength;
  QLabel* mForceTypeLabel;
  QLineEdit* mForceType;
  QLabel* mSolverTypeLabel;
  QLineEdit* mSolverType;
  
  QLineSeries *mSeries;
  QChart *mChart;
  QWidget *mChartWidget;
  QChartView *mChartView;
  QPushButton *mButton;

  //Bridge UI Elements
  QWidget *bridgePage;
  QWidget *bridgeInputWidget;
  QWidget *mVisualizerWidget;
  QGraphicsView *mVisualizerView;
  //QGraphicsScene *scene;
  QGraphicsRectItem *bridgeRect;
  QPushButton *previewButton;
  QWidget *bridgeIOWidget;
  QPushButton *saveButton;
  QPushButton *loadButton;
};
};  // namespace mtobridge
