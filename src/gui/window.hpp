#pragma once

#include <QtCharts>
#include <QtWidgets>
#include <QtGui>
#include "../engine/engine.hpp"
#include "../bridge/bridgeconfig.hpp"
#include "../bridge/bridgevisual.hpp"

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

  QLabel *mSpanLengthLabel;
  QLineEdit *mSpanLength;
  QLabel *mConcernedSectionLabel;
  QLineEdit *mConcernedSection;
  QLabel* mNumberSpansLabel;
  QLineEdit* mNumberSpans;
  QLabel* mDiscretizationLengthLabel;
  QLineEdit* mDiscretizationLength;

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
  BridgeConfiguration *bridgeConfiguration;
};
};  // namespace mtobridge
