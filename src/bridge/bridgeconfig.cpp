#include <bridgeconfig.hpp>
#include <sstream>
using namespace std;

namespace mtobridge {
//BridgeConfiguration::BridgeConfiguration() {}
//BridgeConfiguration::BridgeConfiguration(QString NumberOfSpans,
//                                         QString ConcernedSection,
//                                         QString SpanLength,
//                                         QString DiscretizationLength) {
//  this->config.numberSpans = NumberOfSpans.toInt();
//  this->config.spanLength = convertQstringToDoubleVector(SpanLength);
//  this->config.concernedSection = ConcernedSection.toDouble();
//  this->config.discretizationLength = DiscretizationLength.toDouble();
//}
// 
int defaultSpanNumber;
std::vector<double> defaultSpanLength;
double defualtConcernedSection;
double defualtDiscretizationLength;
BridgeT BridgeConfiguration::config = {defaultSpanNumber, defaultSpanLength,
                                      defualtConcernedSection,defualtDiscretizationLength}; 


vector<double> BridgeConfiguration::convertQstringToDoubleVector(QString qstring) {
   vector<double> numbers{};
   istringstream f(qstring.toStdString());
   string s;
   while (getline(f, s, ' ')) {
     double n1 = stod(s);
     numbers.push_back(n1);
   }
   return numbers;
}
BridgeT BridgeConfiguration::getConfiguration() {
   return BridgeConfiguration::config;
}

void BridgeConfiguration::updateNumberOfSpans(QString newNumberOfSpans) {
   BridgeConfiguration::config.numberSpans = newNumberOfSpans.toInt();
}

void BridgeConfiguration::updateSpanLength(QString SpanLength) {
  BridgeConfiguration::config.spanLength = convertQstringToDoubleVector(SpanLength);
}

void BridgeConfiguration::updateConcernedSection(QString newConcernedSection) {
  BridgeConfiguration::config.concernedSection = newConcernedSection.toDouble();
}

void BridgeConfiguration::updateDiscretizationLength(QString newDiscretizationLength) {
  BridgeConfiguration::config.discretizationLength = newDiscretizationLength.toDouble();
}
}  // namespace mtobridge