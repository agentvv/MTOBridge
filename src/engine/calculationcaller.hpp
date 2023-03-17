#pragma once

#include <QList>
#include <MatlabCppSharedLib.hpp>
#include "util/data_types.hpp"

namespace mtobridge {
MockCalculationOutputT runCalculation(MockCalculationInputT in);
std::shared_ptr<matlab::cpplib::MATLABLibrary> getMatlab();
void destroyMatlab();
};
