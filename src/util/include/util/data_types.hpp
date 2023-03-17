#pragma once
#include <vector>
namespace mtobridge {
  struct MockTruckT {
    std::vector<double> axleLoad{};
    std::vector<double> axleSpacing{};
    quint8 numberOfTrucks;
    double headway;
  };

  struct MockBridgeT {
    quint8 numberSpans;
    std::vector<double> spanLength{};
    double concernedSection;
    double discretizationLength;
  };

  struct MockSolverT {
    enum ForceE { POSITIVE_MOMENT, NEGATIVE_MOMENT, SHEAR } forceType;
    enum SolverE { CONCERNED, CRITICAL } solverType;
  };

  struct MockCalculationInputT {
    MockTruckT truckConfig;
    MockBridgeT bridgeConfig;
    MockSolverT solverConfig;
  };

  struct MockCalculationOutputT {
    std::vector<std::vector<double>> allForces{};
    std::vector<double> firstAxlePosition{};
    std::vector<double> forceConcernedSection{};
    std::vector<double> forceCriticalSection{};
    double maxForce;
    double firstAxlePositionMaxForce;
    std::vector<double> sections{};
    double criticalSection;
    std::vector<double> forceEnvelope{};
    std::vector<double> firstAxlePositionForceEnvelope{};
  };

  class invalidConfigurationValue : public std::exception {
  public:
    char* what() {
      return (char*)"Invalid configuration value given";
    }
  };
};  // namespace mtobridge
