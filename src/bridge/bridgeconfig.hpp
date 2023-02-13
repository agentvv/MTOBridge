#pragma once
#include <QtGlobal>
#include <QString>

namespace mtobridge {
struct BridgeT {
  int numberSpans;
  std::vector<double> spanLength{};
  double concernedSection;
  double discretizationLength;
};
class BridgeConfiguration {
 private:
    BridgeT config;

 public:
    BridgeConfiguration();
    BridgeConfiguration(QString NumberOfSpans, QString ConcernedSection,
                        QString SpanLength, QString DiscretizationLength);
    BridgeT getConfiguration();
    void updateNumberOfSpans(QString newNumberOfSpans);
    void updateConcernedSection(QString newConcernedSection);
    void updateDiscretizationLength(QString newDiscretizationLength);

 private:
    std::vector<double> convertQstringToDoubleVector(QString qstring);
};
}  // namespace mtobridge