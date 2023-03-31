#pragma once
#include <numeric>
#include <vector>
namespace mtobridge {
struct MockTruckT {
  std::vector<double> axleLoad{};
  std::vector<double> axleSpacing{};
  int numberOfTrucks = -1;
  double headway = -1;

  bool operator==(MockTruckT that) {
    return this->axleLoad == that.axleLoad &&
           this->axleSpacing == that.axleSpacing &&
           this->numberOfTrucks == that.numberOfTrucks &&
           this->headway == that.headway;
  }
};

struct MockBridgeT {
  int numberSpans = -1;
  std::vector<double> spanLength{};
  double concernedSection = -1;
  double discretizationLength = -1;

  bool operator==(MockBridgeT that) {
    return this->numberSpans == that.numberSpans &&
      this->spanLength == that.spanLength &&
      this->concernedSection == that.concernedSection &&
      this->discretizationLength == that.discretizationLength;
  }
};

struct MockSolverT {
  enum ForceE {
    POSITIVE_MOMENT,
    NEGATIVE_MOMENT,
    SHEAR
  } forceType = POSITIVE_MOMENT;
  enum SolverE { CONCERNED, CRITICAL } solverType = CONCERNED;

  bool operator==(MockSolverT that) {
    return this->forceType == that.forceType &&
      this->solverType == that.solverType;
  }
};

struct MockCalculationInputT {
  MockTruckT truckConfig;
  MockBridgeT bridgeConfig;
  MockSolverT solverConfig;

  bool operator==(MockCalculationInputT that) {
    return this->truckConfig == that.truckConfig &&
      this->bridgeConfig == that.bridgeConfig &&
      this->solverConfig == that.solverConfig;
  }
};

struct MockCalculationOutputT {
  std::vector<std::vector<double>> allForces{};
  std::vector<double> firstAxlePosition{};
  std::vector<double> forceConcernedSection{};
  std::vector<double> forceCriticalSection{};
  double maxForce = -1;
  double firstAxlePositionMaxForce = -1;
  std::vector<double> sections{};
  double criticalSection = -1;
  std::vector<double> forceEnvelope{};
  std::vector<double> firstAxlePositionForceEnvelope{};

  bool operator==(MockCalculationOutputT that)
  {
    return this->allForces == that.allForces &&
      this->firstAxlePosition == that.firstAxlePosition &&
      this->forceConcernedSection == that.forceConcernedSection &&
      this->forceCriticalSection == that.forceCriticalSection &&
      this->maxForce == that.maxForce &&
      this->firstAxlePositionMaxForce == that.firstAxlePositionMaxForce &&
      this->sections == that.sections &&
      this->criticalSection == that.criticalSection &&
      this->forceEnvelope == that.forceEnvelope &&
      this->firstAxlePositionForceEnvelope == that.firstAxlePositionForceEnvelope;
  }
};

class invalidConfigurationValue : public std::exception {
 public:
  char* what() { return (char*)"Invalid configuration value given"; }
};

bool validateTruckConfig(MockTruckT platoon);
bool validateBridgeConfig(MockBridgeT bridge);
bool validateInput(MockCalculationInputT in);
};  // namespace mtobridge
