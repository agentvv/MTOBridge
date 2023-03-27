#include "window.hpp"

#include <chrono>
#include <sstream>
#include <thread>

#include "../PlatoonConfiguration/PlatoonVisual.hpp"
#include "../bridge/bridgevisual.hpp"
#include "../engine/engine.hpp"

namespace mtobridge {
Window::Window(QWidget *parent) : QWidget(parent) {
  setWindowTitle("MTOBridge");
  resize(800, 600);
  createWindow();
}

/// SPAGHETTI INCOMING
/// should move this stuff to separate custom widgets, and also .ui files...
void Window::createWindow() {
  mTabWidget = new QTabWidget(this);
  mTabWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                        QSizePolicy::Policy::Expanding));

  auto *mainLayout = new QStackedLayout(this);
  mainLayout->addWidget(mTabWidget);
  setLayout(mainLayout);

  mPlatoon = new PlatoonVisual(this);
  mBridge = new BridgeVisual(this);
  mSolver = new SolverVisual(this);

  mTabWidget->addTab(mPlatoon, "Platoon");
  mTabWidget->addTab(mBridge, "Bridge");
  mTabWidget->addTab(mSolver, "Solver");

  auto &engine = Engine::getInstance();

  QObject::connect(&engine, &Engine::errorOccurred, this,
                   &Window::errorOccurred);

  QObject::connect(mPlatoon->getScene(), &QGraphicsScene::changed, this, [&]() {
      mSolver->updateScene("Truck", mPlatoon->getScene());
    });

  QObject::connect(mBridge->getScene(), &QGraphicsScene::changed, this, [&]() {
    mSolver->updateScene("Bridge", mBridge->getScene());
    });
}

void Window::errorOccurred(QString error) {
  QMessageBox::critical(this, QString("Unknown Error!"), error);
}
};  // namespace mtobridge