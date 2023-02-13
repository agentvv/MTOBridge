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
    static BridgeT config;

 public:
    /*BridgeConfiguration();
    BridgeConfiguration(QString NumberOfSpans, QString ConcernedSection,
                        QString SpanLength, QString DiscretizationLength);*/
    static BridgeT getConfiguration();
    static void updateNumberOfSpans(QString newNumberOfSpans);
    static void updateSpanLength(QString SpanLength);
    static void updateConcernedSection(QString newConcernedSection);
    static void updateDiscretizationLength(QString newDiscretizationLength);

 private:
    static std::vector<double> convertQstringToDoubleVector(QString qstring);
};
}  // namespace mtobridge