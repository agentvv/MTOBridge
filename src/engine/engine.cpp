#include "engine.hpp"

#include <qdebug.h>

#include <MatlabCppSharedLib.hpp>
#include <MatlabDataArray.hpp>
#include <QDebug>
#include <string>

#include "../matlab/mtobridge_matlab.hpp"

namespace mtobridge {

Engine::Engine(QObject* parent) : QObject(parent) {
  this->moveToThread(&mThread);

  connect(&mThread, &QThread::started, this, &Engine::startEngine);

  mThread.start();
}

void Engine::startEngine() {
  mMatlabAppPtr = matlab::cpplib::initMATLABApplication(
      matlab::cpplib::MATLABApplicationMode::IN_PROCESS,
      std::vector<std::u16string>({u"-nojvm"}));
  mMatlabLibPtr = matlab::cpplib::initMATLABLibrary(
      mMatlabAppPtr, u"mtobridge_matlab.ctf");

  QObject::connect(this, &Engine::addCommand, this, &Engine::addedCommand);

  emit engineStarted();
}

void Engine::addedCommand(concernedOneMomentInput command) { runCommand(command); }

void Engine::runCommand(concernedOneMomentInput command) {
  matlab::data::ArrayFactory factory;
  Engine::concernedOneMomentReturn output;
  try {
    // // running custom matlab script!!
    auto results = Concerned_section_one_span_moment(
        mMatlabLibPtr,
        factory.createArray<std::vector<double>::iterator, double>(
            {1, command.axle_load.size()}, command.axle_load.begin(), command.axle_load.end()),
        factory.createArray<std::vector<double>::iterator, double>(
            {1, command.axle_spacing.size()}, command.axle_spacing.begin(), command.axle_spacing.end()),
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
    std::cerr << "A MATLAB exception has occured!\n";
    std::cerr << mError << "\n";
  }
  catch (const std::exception& e) {
    std::cerr << "An cpp exception has occured!\n";
    qDebug() << e.what() << "\n";
  }
  emit finishedCommand(output);
}
}  // namespace mtobridge
