#include "PlatoonConfiguration.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <list>
using namespace std;
namespace mtobridge {
//Initialize Struct   
MockTruckT PlatoonConfiguration::TruckConfig;

MockTruckT* PlatoonConfiguration::getConfiguration() { return &TruckConfig; }

//vector<double>/int/double versions of functions are for loading from files, QString versions of functions are for processing user input
void PlatoonConfiguration::updateAxleLoad(std::vector<double> newLoad)
{
  TruckConfig.axleLoad = newLoad;
}

void PlatoonConfiguration::updateAxleLoad(QString newLoad) {

  TruckConfig.axleLoad.clear();
  double temp;
  std::stringstream tempStream(newLoad.toStdString());
  while (tempStream >> temp) {
    TruckConfig.axleLoad.push_back(temp);
  }
}

void PlatoonConfiguration::updateAxleSpacing(std::vector<double> newSpacing) {
  TruckConfig.axleSpacing = newSpacing;
}

void PlatoonConfiguration::updateAxleSpacing(QString newSpacing) {

  TruckConfig.axleSpacing.clear();
  double temp;
  std::stringstream tempStream(newSpacing.toStdString());
  while (tempStream >> temp) {
    TruckConfig.axleSpacing.push_back(temp);
  }

 }

void PlatoonConfiguration::updateNumberOfTrucks(int newNum) {
  TruckConfig.numberOfTrucks = newNum;
}

void PlatoonConfiguration::updateNumberOfTrucks(QString newNum) {

  string s = newNum.toStdString();
  TruckConfig.numberOfTrucks = std::stoi(s);

}

void PlatoonConfiguration::updateHeadway(double newHead) {
  TruckConfig.headway = newHead;
}

void PlatoonConfiguration::updateHeadway(QString newHead) {
  string s = newHead.toStdString();
  TruckConfig.headway = std::stod(s);

}

    int PlatoonConfiguration::getNumTrucks() { return TruckConfig.numberOfTrucks; }
    double PlatoonConfiguration::getHeadway() { return TruckConfig.headway; }
    vector<double> PlatoonConfiguration::getAxleLoads() {return TruckConfig.axleLoad;}
    vector<double> PlatoonConfiguration::getAxleSpacings() {return TruckConfig.axleSpacing;}
    }  // namespace mtobridge