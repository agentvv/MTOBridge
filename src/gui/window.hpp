#pragma once

#include <QtCharts>
#include <QtGui>
#include <QtWidgets>

#include "../PlatoonConfiguration/PlatoonVisual.hpp"
#include "../bridge/bridgevisual.hpp"
#include "../engine/engine.hpp"
#include "../solver/solverVisual.hpp"

namespace mtobridge {
class Window : public QWidget {
  Q_OBJECT

 public:
  Window(QWidget* parent = nullptr);
  ~Window() {
    Engine::getInstance().stopEngine();
    // this ensures the engine thread is stopped before
    // the application is killed
    QEventLoop loop(this);
    while (!Engine::getInstance().thread()->isFinished()) {
      loop.processEvents();
      Engine::getInstance().thread()->wait(10);
    }
  };

 signals:
  void runCommand(MockCalculationInputT);

 public slots:
  void loadReport();
  void errorOccurred(QString);

 private:
  void createWindow();

  QTabWidget* mTabWidget;
  PlatoonVisual* mPlatoon;
  BridgeVisual* mBridge;
  SolverVisual* mSolver;
};
};  // namespace mtobridge
