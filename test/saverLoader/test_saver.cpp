#include <QTest>

#include "../../src/saver/saver.hpp"
#include "util/data_types.hpp"
#include "MatlabDataArray.hpp"

class TestCalculationCaller : public QObject {
  Q_OBJECT

 private:
  
 private slots:


  void testValidSavePlatoonConfiguration() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    //mtobridge::MockCalculationOutputT out;
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::saver::savePlatoonConfiguration(in.truckConfig));
  }
  

 void testInvalidSavePlatoonConfiguration() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    // mtobridge::MockCalculationOutputT out;
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::saver::savePlatoonConfiguration(in.truckConfig));
  }

   void testValidSaveBridgeConfiguration() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    // mtobridge::MockCalculationOutputT out;
    //QVERIFY_THROWS_NO_EXCEPTION(mtobridge::saver::saveBridgeConfiguration(in.bridgeConfig));
  }

  void testInvalidSaveBridgeConfiguration() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    // mtobridge::MockCalculationOutputT out;
    //QVERIFY_THROWS_NO_EXCEPTION(mtobridge::saver::saveBridgeConfiguration(in.bridgeConfig));
  }

  void testValidSaveSolverConfiguration() {
    QSKIP("Hello");
    return;
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    // mtobridge::MockCalculationOutputT out;
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::saver::saveSolverConfiguration(in.solverConfig));
  }
 
    void testInvalidSaveSolverConfiguration() {
    QSKIP("Hello");
    return;
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    // mtobridge::MockCalculationOutputT out;
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::saver::saveSolverConfiguration(in.solverConfig));
  }

};

QTEST_MAIN(TestCalculationCaller)
#include "test_saver.moc"
