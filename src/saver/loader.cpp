#include "loader.hpp"
#include "../bridge/bridgeconfig.hpp"


//! This is the loader module. The following code is responsible for loading data from a text file.
//! The module takes the entire string and splits it into separate lines. 
//! Each line is then prcoessed and analyzed for specific requirments. 


namespace mtobridge {

//! loadPlatoonConfiguration is responsbile for loading the truck data which
//! include axleLoad, axleSapcing, # of trucks and headway.
mtobridge::MockTruckT loader::loadPlatoonConfiguration() {
  mtobridge::MockTruckT temptruck;
  QString fileName =
      QFileDialog::getOpenFileName(nullptr, "Load Truck Configuration", "",
                                   "MTOBridge (*.trk);;All Files (*)");

  //! If the file is empty, we prepopulate it with some data. If the file is
  //! unable to open we send a warning.
  if (fileName.isEmpty())
    return temptruck = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5};
  else {
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::information(nullptr, "Unable to open file",
                               file.errorString());
      return temptruck;
    }

    QString temp;
    QTextStream in(&file);
    temp = in.readAll();
    file.close();

    QList<QString> strList = temp.split("\n", Qt::SkipEmptyParts);

    if (temp.isEmpty()) {
      QMessageBox::information(
          nullptr, "Nothing in file",
          "The file you are attempting to open contains nothing.");
    }

    //! Once we check the strings arent empty, we split each using space
    //! character. We then setup a regex for double and floating point numbers
    //! which we can use to check against our list of values.

    QList<QString> axleLoadList = strList[0].split(" ", Qt::SkipEmptyParts);
    QList<QString> axleSpaceList = strList[1].split(" ", Qt::SkipEmptyParts);

    QRegularExpression regexDouble(
        QStringLiteral(R"([-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?)"));

    for (const auto& i : axleLoadList) {
      QRegularExpressionMatch match = regexDouble.match(i);
      if (match.hasMatch() && match.capturedStart() == 0 &&
          match.capturedLength() == i.length()) {
        temptruck.axleLoad.push_back(i.toDouble());
      } else {
        QMessageBox::information(nullptr, "Invalid Type",
                                 "The file you are attempting to load "
                                 "contains non-numbers for the axleLoad.");
      }
    }

    for (const auto& i : axleSpaceList) {
      QRegularExpressionMatch match = regexDouble.match(i);
      if (match.hasMatch() && match.capturedStart() == 0 &&
          match.capturedLength() == i.length()) {
        temptruck.axleSpacing.push_back(i.toDouble());
      } else {
        QMessageBox::information(
            nullptr, "Invalid Type",
            "The file you are attempting to load contains non-numbers "
            "for the axleSpacing.");
      }
    }
    //! Here we setup an int regex to check for integers only.
    QRegularExpression regexInt(QStringLiteral(R"([-+]?[0-9]+)"));
    QRegularExpressionMatch matchInt = regexInt.match(strList[3]);
    if (matchInt.hasMatch() && matchInt.capturedStart() == 0 &&
        matchInt.capturedLength() == strList[3].length()) {
      temptruck.numberOfTrucks = strList[3].toUInt();
    } else {
      QMessageBox::information(
          nullptr, "Invalid Type",
          "The file you are attempting to load contains non-integer value"
          "for the number of Trucks.");
    }
    // Check if the input matches the regular expression pattern
    QRegularExpressionMatch matchDouble = regexDouble.match(strList[2]);
    if (matchDouble.hasMatch() && matchDouble.capturedStart() == 0 &&
        matchDouble.capturedLength() == strList[2].length()) {
      temptruck.headway = strList[2].toDouble();
    } else {
      QMessageBox::information(
          nullptr, "Invalid Type",
          "The file you are attempting to load contains non-double value"
          "for the truck headway.");
    }

    return temptruck;
  }
}
//! loadBridgeConfiguration is responsbile for loading the bridge data which
//! include numberofSpans, spanLength, concernedSection and
//! discretizationLength.
mtobridge::BridgeT loader::loadBridgeConfiguration() {
  mtobridge::BridgeT tempbridge;

  QString fileName =
      QFileDialog::getOpenFileName(nullptr, "Load Bridge Configuration", "",
                                   "MTOBridge (*.brg);;All Files (*)");

  //! If the file is empty, we prepopulate it with some data. If the file is
  //! unable to open we send a warning.
  if (fileName.isEmpty())
    return tempbridge = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1};
  else {
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::information(nullptr, "Unable to open file",
                               file.errorString());
      return tempbridge;
    }

    QString temp;
    QTextStream in(&file);
    temp = in.readAll();
    file.close();

    //! We start by splitting the entire string into different lines.

    QList<QString> strList = temp.split("\n", Qt::SkipEmptyParts);

    if (temp.isEmpty()) {
      QMessageBox::information(
          nullptr, "Nothing in file",
          "The file you are attempting to open contains nothing.");
    }

    QList<QString> spanLengthList = strList[1].split(" ", Qt::SkipEmptyParts);

    //! We then setup a regex for double and integer point numbers which we can
    //! use to check against our list of values.

    QRegularExpression regexDouble(
        QStringLiteral(R"([-+]?[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?)"));
    QRegularExpression regexInt(QStringLiteral(R"([-+]?[0-9]+)"));


    QRegularExpressionMatch matchInt = regexInt.match(strList[0]);
    //! Return true if the input matches the pattern and the whole input is
    //! matched, otherwise return false
    if (matchInt.hasMatch() && matchInt.capturedStart() == 0 &&
        matchInt.capturedLength() == strList[0].length()) {
      tempbridge.numberSpans = strList[0].toInt();
    } else {
      QMessageBox::information(
          nullptr, "Invalid Type",
          "The file you are attempting to load contains non-int value "
          "for the numberSpans.");
    }

    QRegularExpressionMatch matchDouble;
    for (const auto& i : spanLengthList) {
      matchInt = regexInt.match(i);

      if (matchInt.hasMatch() && matchInt.capturedStart() == 0 &&
          matchInt.capturedLength() == i.length()) {
        tempbridge.spanLength.push_back(i.toDouble());
      } else {
        QMessageBox::information(
            nullptr, "Invalid Type",
            "The file you are attempting to load contains non-double value "
            "for the spanLength.");
      }
    }
    //! Define a regular expression pattern to match doubles only (excluding
    //! integers)
    matchInt = regexInt.match(strList[2]);

    //! Check if the input matches the regular expression pattern
    if (matchInt.hasMatch() && matchInt.capturedStart() == 0 &&
        matchInt.capturedLength() == strList[2].length()) {
      tempbridge.concernedSection = strList[2].toInt();
    } else {
      QMessageBox::information(
          nullptr, "Invalid Type",
          "The file you are attempting to load contains non-double value "
          "for the concernedSection.");
    }

    matchDouble = regexDouble.match(strList[3]);
    if (matchDouble.hasMatch() && matchDouble.capturedStart() == 0 &&
        matchDouble.capturedLength() == strList[3].length()) {
      tempbridge.discretizationLength = strList[3].toDouble();
    } else {
      QMessageBox::information(
          nullptr, "Invalid Type",
          "The file you are attempting to load contains non-double value "
          "for the discretizationLength.");
    }

  
  }
  return tempbridge;
}

mtobridge::MockSolverT loader::loadSolverConfiguration() {
  mtobridge::MockSolverT tempsolver;

  QString fileName =
      QFileDialog::getOpenFileName(nullptr, "Load Bridge Configuration", "",
                                   "MTOBridge (*.slv);;All Files (*)");

  //! [loadFromFile() function part2]
  if (fileName.isEmpty())
    return tempsolver = {.forceType = MockSolverT::POSITIVE_MOMENT,
                         .solverType = MockSolverT::CONCERNED};
  else {
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::information(nullptr, "Unable to open file",
                               file.errorString());
      return tempsolver;
    }

    QString temp;
    QTextStream in(&file);
    temp = in.readAll();
    file.close();

    //! [loadFromFile() function part3]

    QList<QString> strList = temp.split("\n", Qt::SkipEmptyParts);

    if (temp.isEmpty()) {
      QMessageBox::information(
          nullptr, "Nothing in file",
          "The file you are attempting to open contains nothing.");
    }

    if (strList[0] == "Positive Moment")
      tempsolver.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT;
    else if (strList[0] == "Negative Moment")
      tempsolver.forceType = mtobridge::MockSolverT::NEGATIVE_MOMENT;
    else
      tempsolver.forceType = mtobridge::MockSolverT::SHEAR;

    if (strList[1] == "Concerned")
      tempsolver.solverType = mtobridge::MockSolverT::CONCERNED;
    else
      tempsolver.solverType = mtobridge::MockSolverT::CRITICAL;
  }
  return tempsolver;
}

mtobridge::Report loader::loadReportConfiguration() {
  mtobridge::Report tempReport;

  QString fileName = QFileDialog::getOpenFileName(
      nullptr, "Load Report", "", "MTOBridge (*.txt);;All Files (*)");

  //! [loadFromFile() function part2]
  if (fileName.isEmpty())
    return tempReport;  //= {.forceType =
                        //MockSolverT::POSITIVE_MOMENT,.solverType =
                        //MockSolverT::CONCERNED};
  else {
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::information(nullptr, "Unable to open file",
                               file.errorString());
      return tempReport;
    }

    QString temp;
    QTextStream in(&file);
    temp = in.readAll();

    QString line;
    while (!in.atEnd()) {
      line = in.readLine().trimmed();
      if (line.isEmpty() || line.startsWith("*")) continue;
      if (line == "[Platoon]") {
        while (!line.isEmpty()) {
          if (line.startsWith("axleLoad")) {
            QStringList axleLoads =
                line.mid(10).split(' ', Qt::SkipEmptyParts);
            for (const QString& load : axleLoads) {
              tempReport.input.truckConfig.axleLoad.push_back(load.toDouble());
            }
          } else if (line.startsWith("axleSpacing")) {
            QStringList axleSpacings =
                line.mid(12).split(' ', Qt::SkipEmptyParts);
            for (const QString& spacing : axleSpacings) {
              tempReport.input.truckConfig.axleSpacing.push_back(
                  spacing.toDouble());
            }
          } else if (line.startsWith("headway")) {
            tempReport.input.truckConfig.headway = line.mid(8).toDouble();
          } else if (line.startsWith("numberofTrucks")) {
            tempReport.input.truckConfig.numberOfTrucks = line.mid(15).toInt();
          }
        }
      } else if (line == "[Bridge]") {
        while (!line.isEmpty()) {
          if (line.startsWith("numberSpans")) {
            tempReport.input.bridgeConfig.numberSpans = line.mid(12).toInt();
          } else if (line.startsWith("spanLength")) {
            tempReport.input.bridgeConfig.spanLength.push_back(
                line.mid(11).toDouble());
          } else if (line.startsWith("discretizationLength")) {
            tempReport.input.bridgeConfig.discretizationLength =
                line.mid(20).toDouble();
          }
        }
      } else if (line == "[Solver]") {
        while (!line.isEmpty()) {
          if (line.startsWith("forceType")) {
            QString forceTypeStr = line.mid(10).trimmed();
            if (forceTypeStr == "Positive Moment") {
              tempReport.input.solverConfig.forceType =
                  MockSolverT::ForceE::POSITIVE_MOMENT;
            } else if (forceTypeStr == "Negative Moment") {
              tempReport.input.solverConfig.forceType =
                  MockSolverT::ForceE::NEGATIVE_MOMENT;
            } else if (forceTypeStr == "Shear") {
              tempReport.input.solverConfig.forceType =
                  MockSolverT::ForceE::SHEAR;
            }
          } else if (line.startsWith("solverType")) {
            QString solverTypeStr = line.mid(11).trimmed();
            if (solverTypeStr == "Critical") {
              tempReport.input.solverConfig.solverType =
                  MockSolverT::SolverE::CRITICAL;
            } else if (solverTypeStr == "Concerned") {
              tempReport.input.solverConfig.solverType =
                  MockSolverT::SolverE::CONCERNED;
            }
          }
        }
      }
    }

    file.close();

  }
  return tempReport;
}
}  // namespace mtobridge
