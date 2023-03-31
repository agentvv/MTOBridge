#include "util/data_types.hpp"

namespace mtobridge
{
  bool validateTruckConfig(MockTruckT platoon) {
    if (platoon.axleLoad.size() < 1 ||
      platoon.axleLoad.size() != platoon.axleSpacing.size() + 1 ||
      platoon.headway <= 0 || platoon.numberOfTrucks <= 0) {
      return false;
    }
    return true;
  }

  bool validateBridgeConfig(MockBridgeT bridge) {
    double bridgeLength =
      std::reduce(bridge.spanLength.begin(), bridge.spanLength.end());
    if (bridge.numberSpans <= 0 || bridge.numberSpans > 3 ||
      bridge.spanLength.size() != bridge.numberSpans ||
      bridge.concernedSection < 0 || bridge.concernedSection > bridgeLength ||
      bridge.discretizationLength <= 0) {
      return false;
    }
    return true;
  }

  bool validateInput(MockCalculationInputT in) {
    return validateTruckConfig(in.truckConfig) &&
      validateBridgeConfig(in.bridgeConfig) &&
      !(in.solverConfig.forceType == MockSolverT::NEGATIVE_MOMENT &&
        in.bridgeConfig.numberSpans == 1);
  }
}
