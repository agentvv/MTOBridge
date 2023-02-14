#include "PlatoonConfiguration.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <list>
using namespace std;
namespace mtobridge {
    std::list<double> emptyLoads;
    std::list<double> emptySpacings;
    int defaultTrucks = 3;
    double defaultHeadway = 5;

    PlatoonConfiguration::PlatoonT PlatoonConfiguration::TruckConfig = {defaultTrucks, emptyLoads, emptySpacings, defaultHeadway};
    
    PlatoonConfiguration::PlatoonT* PlatoonConfiguration::getConfiguration() { return &TruckConfig; }

void PlatoonConfiguration::updateAxleLoad(QString newLoad) {

  TruckConfig.axleLoad.clear();
  double temp;
  std::stringstream tempStream(newLoad.toStdString());
  while (tempStream >> temp) {
    TruckConfig.axleLoad.push_back(temp);
  }

}
void PlatoonConfiguration::updateAxleSpacing(QString newSpacing) {

  TruckConfig.axleSpacing.clear();
  double temp;
  std::stringstream tempStream(newSpacing.toStdString());
  while (tempStream >> temp) {
    TruckConfig.axleSpacing.push_back(temp);
  }

 }
void PlatoonConfiguration::updateNumberOfTrucks(QString newNum) {

  string s = newNum.toStdString();
  TruckConfig.numberOfTrucks = std::stoi(s);

}
void PlatoonConfiguration::updateHeadway(QString newHead) {
  string s = newHead.toStdString();
  TruckConfig.headway = std::stod(s);

}

    int PlatoonConfiguration::getNumTrucks() { return TruckConfig.numberOfTrucks; }
    double PlatoonConfiguration::getHeadway() { return TruckConfig.headway; }
    list<double> PlatoonConfiguration::getAxleLoads() {return TruckConfig.axleLoad;}
    list<double> PlatoonConfiguration::getAxleSpacings() {return TruckConfig.axleSpacing;}
    }  // namespace mtobridge