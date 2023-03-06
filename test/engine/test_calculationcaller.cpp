#include <QTest>

#include "calculationcaller.hpp"
#include "report_mocks.hpp"

class TestCalculationCaller : public QObject {
  Q_OBJECT

 private slots:
  void testMatlabInit() {
    auto m = mtobridge::getMatlab();
    Q_ASSERT(m.get());
  }

  void testMatLabDestroy() {
    auto m = mtobridge::getMatlab();
    mtobridge::destroyMatlab();
    Q_ASSERT(m != nullptr);
  }

  void testMatlabRunCommand() {
    mtobridge::MockCalculationInputT in = {.truckConfig = {.axleLoad = {},
                                                           .axleSpacing = {},
                                                           .numberOfTrucks = 1,
                                                           .headway = 5}};
  }
};

QTEST_MAIN(TestCalculationCaller)
#include "test_calculationcaller.moc"
