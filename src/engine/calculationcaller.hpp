#pragma once

#include <QList>
#include <MatlabCppSharedLib.hpp>
#include "../report/report_mocks.hpp"

namespace mtobridge {
MockCalculationOutputT runCalculation(MockCalculationInputT in);
std::shared_ptr<matlab::cpplib::MATLABLibrary> getMatlab();
void destroyMatlab();
};
