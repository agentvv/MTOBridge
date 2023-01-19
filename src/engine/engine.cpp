#include "engine.hpp"

#include <qdebug.h>

#include <MatlabCppSharedLib.hpp>
#include <QDebug>
#include <QThread>
#include <QMessageBox>
#include <iostream>
#include <string>

#include "../matlab/mtobridge_matlab.hpp"

namespace mtobridge {

Engine::Engine(QObject* parent) : QObject(parent) {
  this->moveToThread(&mThread);

  connect(&mThread, &QThread::started, this, &Engine::startEngine);

  mThread.start();
}

void Engine::stopEngine() {
  mMatlabLibPtr.reset();
  mMatlabAppPtr.reset();
  mThread.quit();
}

void Engine::startEngine() {
  mMatlabAppPtr = matlab::cpplib::initMATLABApplication(
      matlab::cpplib::MATLABApplicationMode::IN_PROCESS,
      std::vector<std::u16string>({u"-nojvm"}));
  mMatlabLibPtr =
      matlab::cpplib::initMATLABLibrary(mMatlabAppPtr, u"mtobridge_matlab.ctf");

  QObject::connect(this, &Engine::addCommand, this, &Engine::addedCommand);

  emit engineStarted();
}

void Engine::addedCommand(concernedOneMomentInput command) {
  runCommand(command);
}

void Engine::runCommand(concernedOneMomentInput command) {
  Engine::concernedOneMomentReturn output;
  try {
    matlab::data::ArrayFactory factory;

    // // running custom matlab script!!
    auto results = Concerned_section_one_span_moment(
        mMatlabLibPtr,
        factory.createArray<std::vector<double>::iterator, double>(
            {1, command.axle_load.size()}, command.axle_load.begin(),
            command.axle_load.end()),
        factory.createArray<std::vector<double>::iterator, double>(
            {1, command.axle_spacing.size()}, command.axle_spacing.begin(),
            command.axle_spacing.end()),
        factory.createScalar<double>(command.number_of_trucks),
        factory.createScalar<double>(command.truck_position_increment),
        factory.createScalar<double>(command.headway),
        factory.createScalar<double>(command.span_length),
        factory.createScalar<double>(command.concerned_section));

    output.firstAxlePosition = matlab::data::TypedArray<double>(results[0])[0];
    matlab::data::TypedArray<double> moment_concerned_section_array =
        results[1];
    output.moment = std::vector<double>(moment_concerned_section_array.begin(),
                                        moment_concerned_section_array.end());

    output.maxMoment = matlab::data::TypedArray<double>(results[2])[0];
    output.firstAxlePositionMaxMoment =
        matlab::data::TypedArray<double>(results[3])[0];
    output.input = command;
    // std::cout << mOut << "\n";
  } catch (const matlab::Exception& e) {
    emit errorOccurred(QString("A MATLAB exception has occurred!\nError: %1").arg(e.what()));
    return;
  } catch (const std::exception& e) {
    emit errorOccurred(QString("An exception has occurred!\nError: %1").arg(e.what()));
    return;
  }
  emit finishedCommand(output);
}
}  // namespace mtobridge
