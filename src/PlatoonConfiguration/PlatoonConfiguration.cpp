#include "PlatoonConfiguration.hpp"
#include <iostream>
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
  string s = newLoad.toStdString();
  string delimiter = " ";
  int start = 0;
  int end = s.find(delimiter);
  while (end != -1) {
    TruckConfig.axleLoad.push_back(std::stod(s.substr(start, end - start)));
    start = end + delimiter.size();
    end = s.find(delimiter, start);
  }
  TruckConfig.axleLoad.push_back(std::stod(s.substr(start, end - start)));

}
void PlatoonConfiguration::updateAxleSpacing(QString newSpacing) {

  TruckConfig.axleSpacing.clear();
  string s = newSpacing.toStdString();
  string delimiter = " ";
  int count = 0;
  int start = 0;
  int end = s.find(delimiter);
  while (end != -1) {
    TruckConfig.axleSpacing.push_back(std::stod(s.substr(start, end - start)));
    start = end + delimiter.size();
    end = s.find(delimiter, start);
  }
  TruckConfig.axleSpacing.push_back(std::stod(s.substr(start, end - start)));
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