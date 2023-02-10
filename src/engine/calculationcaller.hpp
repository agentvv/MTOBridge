#pragma once

#include <QList>
#include <MatlabCppSharedLib.hpp>

namespace mtobridge {
struct MockTruckT {
  std::vector<double> axleLoad;
  std::vector<double> axleSpacing;
  quint8 numberOfTrucks;
  double headway;
};

struct MockBridgeT {
  quint8 numberSpans;
  std::vector<double> spanLength;
  double concernedSection;
  double discretizationLength;
};

struct MockSolverT {
  enum ForceE {
    POSITIVE_MOMENT,
    NEGATIVE_MOMENT,
    SHEAR
  } forceType;
  enum SolverE {
    CONCERNED,
    CRITICAL
  } solverType;
};

struct CalculationInputT {
  MockTruckT truckConfig;
  MockBridgeT bridgeConfig;
  MockSolverT solverConfig;
};

struct CalculationOutputT {
  std::vector<std::vector<double>> allForces;
  std::vector<double> firstAxlePosition;
  std::vector<double> forceConcernedSection;
  std::vector<double> forceCriticalSection;
  double maxForce = -1.0;
  double firstAxlePositionMaxForce = -1.0;
  std::vector<double> sections;
  double criticalSection = -1.0;
  std::vector<double> forceEnvelope;
  std::vector<double> firstAxlePositionForceEnvelope;
};

CalculationOutputT runCalculation(CalculationInputT in);
std::shared_ptr<matlab::cpplib::MATLABLibrary> getMatlab();
void destroyMatlab();
};
