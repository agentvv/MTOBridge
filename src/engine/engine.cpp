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
  // move this object to a new thread to avoid clogging the main gui thread
  this->moveToThread(&mThread);
  connect(&mThread, &QThread::started, this, &Engine::startEngine);
  mThread.start();
}

/**
 * @brief Destroys MATLAB and ends this threads execution
 */
void Engine::stopEngine() {
  destroyMatlab();
  mThread.quit();
}

/**
 * @brief Ensures MATLAB is running, and emits engineStarted
 * signal
 */
void Engine::startEngine() {
  getMatlab();
  emit engineStarted();
}

/**
 * @brief Runs the command based on the calculation input, and
 * emits finishedCommand signal when finished
 * @param in input including all configuration
 */
void Engine::runCommand(MockCalculationInputT in) {
  MockCalculationOutputT out;
  try {
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
  emit finishedCommand(in, out);
}
}  // namespace mtobridge
