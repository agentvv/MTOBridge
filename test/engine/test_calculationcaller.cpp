#include <QTest>

#include "../../src/engine/calculationcaller.hpp"
#include "../../src/report/report_mocks.hpp"
#include "MatlabDataArray.hpp"

class TestCalculationCaller : public QObject {
  Q_OBJECT

 private:
  std::shared_ptr<matlab::cpplib::MATLABLibrary> m;
 private slots:
  void initTestCase() {
    m = mtobridge::getMatlab();
    QVERIFY(m.get());
  }

  void testValidCommand() {
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
    mtobridge::MockCalculationOutputT out;
    QVERIFY_THROWS_NO_EXCEPTION(out = mtobridge::runCalculation(in));
    QCOMPARE(out.firstAxlePosition.size(),
             std::ceil(((3.6576 + 1.2192 + 9.4488 + 1.2192) * 3 + 5 * 2 + 40) /
                       0.1));
    QCOMPARE(out.firstAxlePosition.size(), out.forceConcernedSection.size());

    // critical section should not be defined
    QCOMPARE(out.criticalSection, -1);
    QVERIFY(out.forceCriticalSection.empty());
  }

  void testInvalidCommandAxleLoad() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::runCalculation(in));
  }

  void testInvalidCommandAxleSpacing1() {
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
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::runCalculation(in));
  }

  void testInvalidCommandAxleSpacing2() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::runCalculation(in));
  }

  void testInvalidCommandNumberOfTrucks() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 0,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::runCalculation(in));
  }

  void testInvalidCommandHeadway() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = -1},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::runCalculation(in));
  }

  void testInvalidCommandNumberOfSpans1() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 0,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::runCalculation(in));
  }

  void testInvalidCommandNumberOfSpans2() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 10,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::runCalculation(in));
  }

  void testInvalidCommandSpanLength1() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::runCalculation(in));
  }

  void testInvalidCommandSpanLength2() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {-1, -1},
                         .concernedSection = 10,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::runCalculation(in));
  }

  void testInvalidCommandConcernedSection() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = -1,
                         .discretizationLength = 0.1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::runCalculation(in));
  }

  void testInvalidCommandDiscretizationLength1() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = 70},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::runCalculation(in));
  }

  void testInvalidCommandDiscretizationLength2() {
    mtobridge::MockCalculationInputT in = {
        .truckConfig = {.axleLoad = {53.4, 75.6, 75.6, 75.6, 75.6},
                        .axleSpacing = {3.6576, 1.2192, 9.4488, 1.2192},
                        .numberOfTrucks = 3,
                        .headway = 5},
        .bridgeConfig = {.numberSpans = 2,
                         .spanLength = {20, 20},
                         .concernedSection = 10,
                         .discretizationLength = -1},
        .solverConfig = {.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT,
                         .solverType = mtobridge::MockSolverT::CONCERNED}};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::runCalculation(in));
  }

  void cleanupTestCase() { mtobridge::destroyMatlab(); }
};

QTEST_MAIN(TestCalculationCaller)
#include "test_calculationcaller.moc"
