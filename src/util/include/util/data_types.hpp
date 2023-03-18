#pragma once
#include <vector>
namespace mtobridge {
  struct MockTruckT {
    std::vector<double> axleLoad{};
    std::vector<double> axleSpacing{};
    int numberOfTrucks = -1;
    double headway = -1;
  };

  struct MockBridgeT {
    int numberSpans = -1;
    std::vector<double> spanLength{};
    double concernedSection = -1;
    double discretizationLength = -1;
  };

  struct MockSolverT {
    enum ForceE { POSITIVE_MOMENT, NEGATIVE_MOMENT, SHEAR } forceType = POSITIVE_MOMENT;
    enum SolverE { CONCERNED, CRITICAL } solverType = CONCERNED;
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
    double maxForce = -1;
    double firstAxlePositionMaxForce = -1;
    std::vector<double> sections{};
    double criticalSection = -1;
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
