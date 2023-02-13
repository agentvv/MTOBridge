#pragma once
#include <string>
#include <list>
#include <QString>
namespace mtobridge {
class PlatoonConfiguration {
 private:
  static struct PlatoonT {
    int numberOfTrucks;
    std::list<double> axleLoad;
    std::list<double> axleSpacing;
    double headway;
  } TruckConfig;

 public:
  static PlatoonT* getConfiguration();
  static void updateAxleLoad(QString newLoad);
  static void updateAxleSpacing(QString newSpacing);
  static void updateNumberOfTrucks(QString newNum);
  static void updateHeadway(QString newHead);

  static int getNumTrucks();
  static double getHeadway();
  static std::list<double> getAxleLoads();
  static std::list<double> getAxleSpacings();
};
}  // namespace mtobridge
