#pragma once

//#include "../calculation/CalculationInput.hpp"
//#include "../calculation/CalculationOutput.hpp"
#include "report_mocks.hpp"

namespace mtobridge {
struct Report {
  MockCalculationInputT input;
  MockCalculationOutputT results;
};
};  // namespace mtobridge
