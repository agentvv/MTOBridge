#include <bridgeconfig.hpp>
#include <sstream>
using namespace std;

namespace mtobridge {
BridgeConfiguration::BridgeConfiguration() {}
BridgeConfiguration::BridgeConfiguration(QString NumberOfSpans,
                                         QString ConcernedSection,
                                         QString SpanLength,
                                         QString DiscretizationLength) {
  this->config.numberSpans = NumberOfSpans.toInt();
  this->config.spanLength = convertQstringToDoubleVector(SpanLength);
  this->config.concernedSection = ConcernedSection.toDouble();
  this->config.discretizationLength = DiscretizationLength.toDouble();
}
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
  return this->config;
}

void BridgeConfiguration::updateNumberOfSpans(QString newNumberOfSpans) {
  this->config.numberSpans = newNumberOfSpans.toInt();
}

void BridgeConfiguration::updateConcernedSection(QString newConcernedSection) {
  this->config.concernedSection = newConcernedSection.toDouble();
}

void BridgeConfiguration::updateDiscretizationLength(QString newDiscretizationLength) {
  this->config.discretizationLength = newDiscretizationLength.toDouble();
}
}  // namespace mtobridge