#pragma once
#include <string>
#include <vector>
#include <QString>
#include "util/data_types.hpp"
namespace mtobridge {
class PlatoonConfiguration {
 private:
  static MockTruckT TruckConfig; 

 public:
  static MockTruckT* getConfiguration();
  static void updateAxleLoad(QString newLoad);
  static void updateAxleSpacing(QString newSpacing);
  static void updateNumberOfTrucks(QString newNum);
  static void updateHeadway(QString newHead);

  static int getNumTrucks();
  static double getHeadway();
  static std::vector<double> getAxleLoads();
  static std::vector<double> getAxleSpacings();
};
}  // namespace mtobridge
