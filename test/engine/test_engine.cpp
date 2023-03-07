#include <QSignalSpy>
#include <QTest>

#include "../../src/engine/engine.hpp"

class TestEngine : public QObject {
  Q_OBJECT
  mtobridge::Engine* engine;
 private slots:
  void initTestCase() {
    engine = &mtobridge::Engine::getInstance();
    QSignalSpy spy{engine, &mtobridge::Engine::engineStarted};
    QTRY_COMPARE_EQ_WITH_TIMEOUT(spy.count(), 1, 10000);
  }

  void testDifferentThread() { QCOMPARE_NE(this->thread(), engine->thread()); }

  void testRunCommand() {
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
    {
      QObject tmp;
      QObject::connect(&tmp, &QObject::destroyed, engine, [&]() { engine->runCommand(in); });
    }

    QSignalSpy spy{ engine, &mtobridge::Engine::finishedCommand };
    QTRY_COMPARE_EQ_WITH_TIMEOUT(spy.count(), 1, 10000);
  }

  void cleanupTestCase() {
    engine->stopEngine();
    QTRY_VERIFY_WITH_TIMEOUT(engine->thread()->isFinished(), 10000);
  }
};

QTEST_MAIN(TestEngine)
#include "test_engine.moc"
