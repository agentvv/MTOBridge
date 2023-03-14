#pragma once

#include <QtCharts>
#include <QtWidgets>
#include <QtGui>
#include "../engine/engine.hpp"
#include "../bridge/bridgevisual.hpp"
#include "../PlatoonConfiguration/PlatoonVisual.hpp"
#include "../solver/solverVisual.hpp"
#include "../report/reportpage.hpp" 

namespace mtobridge {
class Window : public QWidget {
  Q_OBJECT

 public:
  Window(QWidget *parent = nullptr);
  ~Window() { Engine::getInstance().stopEngine(); };

 signals:
  void runCommand(MockCalculationInputT);

 public slots:
  void errorOccurred(QString);

 private:
  void createWindow();

  QTabWidget *mTabWidget;
  PlatoonVisual* mPlatoon;
  BridgeVisual* mBridge;
  SolverVisual* mSolver;
  ReportPage* mReport;
};
};  // namespace mtobridge
