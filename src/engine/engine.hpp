#pragma once

#include <MatlabCppSharedLib.hpp>
#include <MatlabDataArray.hpp>
#include <QObject>
#include <QQueue>
#include <QThread>
#include <memory>

namespace mtobridge {
class Engine : public QObject {
  Q_OBJECT
 public:
  static Engine &getInstance() {
    static Engine instance;
    return instance;
  }

  // std::vector<double> runCommand(std::vector<double> x);

  Engine(const Engine &) = delete;
  void operator=(const Engine &) = delete;

  struct concernedOneMomentInput {
    std::vector<double> axle_load = {53.4, 75.6, 75.6, 75.6, 75.6};
    std::vector<double> axle_spacing = {3.6576, 1.2192, 9.4488, 1.2192};
    int number_of_trucks = 3;
    double truck_position_increment = 0.1;
    int headway = 5;
    int span_length = 20;
    int concerned_section = 10;
  };

  struct concernedOneMomentReturn {
    double firstAxlePosition = -1;
    double firstAxlePositionMaxMoment = -1;
    std::vector<double> moment;
    double maxMoment = -1;
    concernedOneMomentInput input;
  };

 signals:
  void engineStarted();
  void addCommand(concernedOneMomentInput);
  void finishedCommand();
  void finishedCommand(concernedOneMomentReturn);

 public slots:
  void addedCommand(concernedOneMomentInput);

 protected slots:
  void startEngine();

 private:
  void runCommand(concernedOneMomentInput);
  Engine(QObject *parent = nullptr);
  QThread mThread;
  QQueue<std::string> mCommandQueue;
  QQueue<std::string> mOutputQueue;

  std::shared_ptr<matlab::cpplib::MATLABApplication> mMatlabAppPtr;
  std::shared_ptr<matlab::cpplib::MATLABLibrary> mMatlabLibPtr;

  std::shared_ptr<std::basic_stringbuf<char16_t>> mError =
      std::make_shared<std::basic_stringbuf<char16_t>>();
  std::shared_ptr<std::basic_stringbuf<char16_t>> mOut =
      std::make_shared<std::basic_stringbuf<char16_t>>();
};
}  // namespace mtobridge