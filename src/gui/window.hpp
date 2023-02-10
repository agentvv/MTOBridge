#pragma once

#include <QtCharts>
#include <QtWidgets>

#include "../engine/engine.hpp"

namespace mtobridge {
class Window : public QWidget {
  Q_OBJECT

 public:
  Window(QWidget *parent = nullptr);
  ~Window() { Engine::getInstance().stopEngine(); };
  QTabWidget *getTabWidget();

 signals:
  void runCommand(Engine::concernedOneMomentInput);

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
  QLabel *mTruckPositionIncrementLabel;
  QLineEdit *mTruckPositionIncrement;
  QLabel *mHeadwayLabel;
  QLineEdit *mHeadway;
  QLabel *mSpanLengthLabel;
  QLineEdit *mSpanLength;
  QLabel *mConcernedSectionLabel;
  QLineEdit *mConcernedSection;

  QLineSeries *mSeries;
  QChart *mChart;
  QWidget *mChartWidget;
  QChartView *mChartView;
  QPushButton *mButton;
};
};  // namespace mtobridge
