#pragma once

#include <QtCharts>
#include <QtWidgets>
#include <QtGui>
#include "../engine/engine.hpp"
#include "../bridge/bridgevisual.hpp"
#include "../PlatoonConfiguration/PlatoonVisual.hpp"
#include "../solver/solverVisual.hpp"

namespace mtobridge {
class Window : public QWidget {
  Q_OBJECT

 public:
  Window(QWidget *parent = nullptr);
  ~Window() { 
    Engine::getInstance().stopEngine();

    QEventLoop loop(this);
    while (!Engine::getInstance().thread()->isFinished())
    {
      loop.processEvents();
      Engine::getInstance().thread()->wait(10);
    }
  };

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
};
};  // namespace mtobridge
