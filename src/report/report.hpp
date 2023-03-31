#pragma once
#include "util/data_types.hpp"

namespace mtobridge {
struct Report {
  MockCalculationInputT input;
  MockCalculationOutputT results;

  bool operator==(Report that)
  {
    return this->input == that.input && this->results == that.results;
  }
};
};  // namespace mtobridge
