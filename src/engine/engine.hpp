#pragma once

#include <MatlabCppSharedLib.hpp>
#include <QObject>
#include <QQueue>
#include <QThread>
#include <memory>

#include "calculationcaller.hpp"

namespace mtobridge {
class Engine : public QObject {
  Q_OBJECT
 public:
  static Engine &getInstance() {
    static Engine instance;
    return instance;
  }

  Engine(const Engine &) = delete;
  void operator=(const Engine &) = delete;
  void stopEngine();

 signals:
  void engineStarted();
  void finishedCommand(MockCalculationInputT, MockCalculationOutputT);
  void errorOccurred(QString);

 public slots:
  void runCommand(MockCalculationInputT);

 protected slots:
  void startEngine();

 private:
  Engine(QObject *parent = nullptr);
  QThread mThread;
};
}  // namespace mtobridge