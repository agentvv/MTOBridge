#include "engine.hpp"
#include "calculationcaller.hpp"

#include <MatlabCppSharedLib.hpp>
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QString>
#include <iostream>
#include <string>


namespace mtobridge {

Engine::Engine(QObject* parent) : QObject(parent) {
  this->moveToThread(&mThread);
  connect(&mThread, &QThread::started, this, &Engine::startEngine);
  mThread.start();
}

void Engine::stopEngine() {
  destroyMatlab();
  mThread.quit();
}

void Engine::startEngine() {
  getMatlab();
  emit engineStarted();
}

void Engine::runCommand(MockCalculationInputT in) {
#include <chrono>
  auto start = std::chrono::high_resolution_clock::now();
  MockCalculationOutputT out;
  try {
    // // running custom matlab script!!
    out = runCalculation(in);
  } catch (const matlab::Exception& e) {
    emit errorOccurred(
        QString("A MATLAB exception has occurred!\nError: %1").arg(e.what()));
    return;
  } catch (const std::exception& e) {
    emit errorOccurred(
        QString("An exception has occurred!\nError: %1").arg(e.what()));
    return;
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  QTextStream(stdout) << "Engine: " << duration.count();
  emit finishedCommand(in, out);
}
}  // namespace mtobridge
