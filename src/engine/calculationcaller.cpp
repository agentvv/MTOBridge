#include "calculationcaller.hpp"

#include "../matlab/mtobridge_matlab.hpp"

namespace mtobridge {

// default truck incremenent, not necessary as user input
const double TRUCK_POSITION_INCREMENT = 0.1;

static std::shared_ptr<matlab::cpplib::MATLABApplication> matlabAppPtr =
    nullptr;
static std::shared_ptr<matlab::cpplib::MATLABLibrary> matlabLibPtr = nullptr;
static matlab::data::ArrayFactory factory;

// This stores all the matlab functions, this works well enough because the
// function signatures are the same for each matlab function. This may change
// in the future, so this may have to change
std::function<std::vector<matlab::data::Array>(
    std::shared_ptr<MATLABControllerType> _matlabPtr, matlab::data::Array,
    matlab::data::Array, matlab::data::Array, matlab::data::Array,
    matlab::data::Array, matlab::data::Array, matlab::data::Array)>
    matlabFunctions[2][3][3];

/**
 * @brief getMatlab() initializes matlab if it hasn't been initialized
 * @return matlabLibPtr matlab library for running matlab functions
 */
std::shared_ptr<matlab::cpplib::MATLABLibrary> getMatlab() {
  if (matlabAppPtr == nullptr) {
    matlabAppPtr = matlab::cpplib::initMATLABApplication(
        matlab::cpplib::MATLABApplicationMode::IN_PROCESS,
        std::vector<std::u16string>({u"-nojvm"}));
    matlabLibPtr = matlab::cpplib::initMATLABLibrary(matlabAppPtr,
                                                     u"mtobridge_matlab.ctf");
  }
  return matlabLibPtr;
}

/**
 * @brief destroyMatlab() deletes matlab lib and app
 */
void destroyMatlab() {
  matlabLibPtr.reset();
  matlabAppPtr.reset();
}

/**
 * @brief Converts matlab output to CalculationOutputT for
 * use by the GUI, specifically for concerned section calculation
 * @param matlabOut matlab output to be converted
 * @return converted matlab output
 */
MockCalculationOutputT concernedSectionOut(
    std::vector<matlab::data::Array> matlabOut) {
  MockCalculationOutputT out;
  matlab::data::TypedArray<double> firstAxlePosition = matlabOut[0];
  out.firstAxlePosition =
      std::vector<double>(firstAxlePosition.begin(), firstAxlePosition.end());

  matlab::data::TypedArray<double> forceConcernedSection = matlabOut[1];
  out.forceConcernedSection = std::vector<double>(forceConcernedSection.begin(),
                                                  forceConcernedSection.end());

  double maxForce = matlab::data::TypedArray<double>(matlabOut[2])[0];
  out.maxForce = maxForce;

  double firstAxlePositionMaxForce =
      matlab::data::TypedArray<double>(matlabOut[3])[0];
  out.firstAxlePositionMaxForce = firstAxlePositionMaxForce;

  return out;
}

/**
 * @brief Converts matlab output to CalculationOutputT for
 * use by the GUI, specifically for negative moment concerned section
 * calculation
 * @param matlabOut matlab output to be converted
 * @return converted matlab output
 */
MockCalculationOutputT concernedSectionNegativeOut(
    std::vector<matlab::data::Array> matlabOut) {
  MockCalculationOutputT out;
  const auto& firstAxlePosition =
      matlab::data::TypedArray<double>(matlabOut[0]);
  out.firstAxlePosition =
      std::vector<double>(firstAxlePosition.begin(), firstAxlePosition.end());

  const auto& momentConcernedSection =
      matlab::data::TypedArray<double>(matlabOut[1]);
  out.forceConcernedSection = std::vector<double>(
      momentConcernedSection.begin(), momentConcernedSection.end());

  double maxNegativeMoment = matlab::data::TypedArray<double>(matlabOut[4])[0];
  out.maxForce = maxNegativeMoment;

  double firstAxlePositionMaxNegativeMoment =
      matlab::data::TypedArray<double>(matlabOut[5])[0];
  out.firstAxlePositionMaxForce = firstAxlePositionMaxNegativeMoment;

  return out;
}

/**
 * @brief Converts matlab output to CalculationOutputT for
 * use by the GUI, specifically for critical section calculation
 * @param matlabOut matlab output to be converted
 * @return converted matlab output
 */
MockCalculationOutputT criticalSectionOut(
    std::vector<matlab::data::Array> matlabOut) {
  MockCalculationOutputT out;
  const auto& sections = matlab::data::TypedArray<double>(matlabOut[0]);
  out.sections = std::vector<double>(sections.begin(), sections.end());

  const auto& firstAxlePosition =
      matlab::data::TypedArray<double>(matlabOut[1]);
  out.firstAxlePosition =
      std::vector<double>(firstAxlePosition.begin(), firstAxlePosition.end());

  const auto& allForces = matlab::data::TypedArray<double>(matlabOut[2]);
  for (int i = 0; i < allForces.getDimensions().front(); i++) {
    std::vector<double> forces;
    for (int j = 0; j < allForces.getDimensions().back(); j++) {
      const auto& force = allForces[i][j];
      forces.push_back(force);
    }
    out.allForces.push_back(forces);
  }

  const auto& forceEnvelope = matlab::data::TypedArray<double>(matlabOut[3]);
  out.forceEnvelope =
      std::vector<double>(forceEnvelope.begin(), forceEnvelope.end());

  double firstAxlePositionMaxForce =
      matlab::data::TypedArray<double>(matlabOut[4])[0];
  out.firstAxlePositionMaxForce = firstAxlePositionMaxForce;

  const auto& forceCriticalSection =
      matlab::data::TypedArray<double>(matlabOut[5]);
  out.forceCriticalSection = std::vector<double>(forceCriticalSection.begin(),
                                                 forceCriticalSection.end());

  double criticalSection = matlab::data::TypedArray<double>(matlabOut[6])[0];
  out.criticalSection = criticalSection;

  return out;
}

/**
 * @brief run concerned section calculation
 * @param in calculation input
 * @return calulation output
 */
MockCalculationOutputT concernedSection(MockCalculationInputT& in) {
  const auto& result =
      matlabFunctions[in.solverConfig.solverType][in.bridgeConfig.numberSpans -
                                                  1][in.solverConfig.forceType](
          getMatlab(),
          factory.createArray<std::vector<double>::iterator, double>(
              {1, in.truckConfig.axleLoad.size()},
              in.truckConfig.axleLoad.begin(), in.truckConfig.axleLoad.end()),
          factory.createArray<std::vector<double>::iterator, double>(
              {1, in.truckConfig.axleSpacing.size()},
              in.truckConfig.axleSpacing.begin(),
              in.truckConfig.axleSpacing.end()),
          factory.createScalar<double>(in.truckConfig.numberOfTrucks),
          factory.createScalar<double>(TRUCK_POSITION_INCREMENT),
          factory.createScalar<double>(in.truckConfig.headway),
          factory.createArray<std::vector<double>::iterator, double>(
              {1, in.bridgeConfig.spanLength.size()},
              in.bridgeConfig.spanLength.begin(),
              in.bridgeConfig.spanLength.end()),
          factory.createScalar<double>(in.bridgeConfig.concernedSection));
  return concernedSectionOut(result);
};

/**
 * @brief run concerned section calculation for negative moment
 * @param in calculation input
 * @return calulation output
 */
MockCalculationOutputT concernedNegativeSection(MockCalculationInputT& in) {
  const auto& result =
      matlabFunctions[in.solverConfig.solverType][in.bridgeConfig.numberSpans -
                                                  1][in.solverConfig.forceType](
          getMatlab(),
          factory.createArray<std::vector<double>::iterator, double>(
              {1, in.truckConfig.axleLoad.size()},
              in.truckConfig.axleLoad.begin(), in.truckConfig.axleLoad.end()),
          factory.createArray<std::vector<double>::iterator, double>(
              {1, in.truckConfig.axleSpacing.size()},
              in.truckConfig.axleSpacing.begin(),
              in.truckConfig.axleSpacing.end()),
          factory.createScalar<double>(in.truckConfig.numberOfTrucks),
          factory.createScalar<double>(TRUCK_POSITION_INCREMENT),
          factory.createScalar<double>(in.truckConfig.headway),
          factory.createArray<std::vector<double>::iterator, double>(
              {1, in.bridgeConfig.spanLength.size()},
              in.bridgeConfig.spanLength.begin(),
              in.bridgeConfig.spanLength.end()),
          factory.createScalar<double>(in.bridgeConfig.concernedSection));
  return concernedSectionNegativeOut(result);
};

/**
 * @brief run critical section calculation
 * @param in calculation input
 * @return calulation output
 */
MockCalculationOutputT criticalSection(MockCalculationInputT& in) {
  const auto& result =
      matlabFunctions[in.solverConfig.solverType][in.bridgeConfig.numberSpans -
                                                  1][in.solverConfig.forceType](
          getMatlab(),
          factory.createArray<std::vector<double>::iterator, double>(
              {1, in.truckConfig.axleLoad.size()},
              in.truckConfig.axleLoad.begin(), in.truckConfig.axleLoad.end()),
          factory.createArray<std::vector<double>::iterator, double>(
              {1, in.truckConfig.axleSpacing.size()},
              in.truckConfig.axleSpacing.begin(),
              in.truckConfig.axleSpacing.end()),
          factory.createScalar<double>(in.truckConfig.numberOfTrucks),
          factory.createScalar<double>(TRUCK_POSITION_INCREMENT),
          factory.createScalar<double>(in.truckConfig.headway),
          factory.createArray<std::vector<double>::iterator, double>(
              {1, in.bridgeConfig.spanLength.size()},
              in.bridgeConfig.spanLength.begin(),
              in.bridgeConfig.spanLength.end()),
          factory.createScalar<double>(in.bridgeConfig.discretizationLength));
  return criticalSectionOut(result);
};

/**
 * @brief assigns matlab function pointers
 */
void setupCalculations() {
  matlabFunctions[0][0][0] = &Concerned_section_one_span_moment;
  matlabFunctions[0][0][1] = &Concerned_section_one_span_moment;
  matlabFunctions[0][0][2] = &Concerned_section_one_span_shear;
  matlabFunctions[0][1][0] = &Concerned_section_two_span_moment;
  matlabFunctions[0][1][1] = &Concerned_section_two_span_moment;
  matlabFunctions[0][1][2] = &Concerned_section_two_span_shear;
  matlabFunctions[0][2][0] = &Concerned_section_three_span_moment;
  matlabFunctions[0][2][1] = &Concerned_section_three_span_moment;
  matlabFunctions[0][2][2] = &Concerned_section_three_span_shear;

  matlabFunctions[1][0][0] = &Critical_section_one_span_moment;
  matlabFunctions[1][0][1] = &Critical_section_one_span_moment;
  matlabFunctions[1][0][2] = &Critical_section_one_span_shear;
  matlabFunctions[1][1][0] = &Critical_section_two_span_positive_moment;
  matlabFunctions[1][1][1] = &Critical_section_two_span_negative_moment;
  matlabFunctions[1][1][2] = &Critical_section_two_span_shear;
  matlabFunctions[1][2][0] = &Critical_section_three_span_positive_moment;
  matlabFunctions[1][2][1] = &Critical_section_three_span_negative_moment;
  matlabFunctions[1][2][2] = &Critical_section_three_span_shear;
}

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

/**
 * @brief runs appropriate calculation depending on the calculation input
 * @param in calculation input
 * @return calculation output
 */
MockCalculationOutputT runCalculation(MockCalculationInputT in) {
  static bool setup = false;
  if (!setup) {
    setupCalculations();
    setup = true;
  }

  if (!validateInput(in)) {
    return MockCalculationOutputT();
  }

  if (in.solverConfig.solverType == MockSolverT::CONCERNED) {
    if (in.solverConfig.forceType == MockSolverT::NEGATIVE_MOMENT) {
      return concernedNegativeSection(in);
    }
    return concernedSection(in);
  } else {
    return criticalSection(in);
  }
}
}  // namespace mtobridge
