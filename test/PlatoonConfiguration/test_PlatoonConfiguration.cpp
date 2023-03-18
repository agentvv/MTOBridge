#include <QTest>

#include "../../src/PlatoonConfiguration/PlatoonConfiguration.hpp"
#include "../../src/report/report_mocks.hpp"

class TestPlatoonConfiguration : public QObject {
  Q_OBJECT

 private slots:
  void testUpdateAxleLoadSpaces() {
    std::list<double> testList = {53.4, 75.6, 75.6, 75.6, 75.6};
    mtobridge::PlatoonConfiguration::updateAxleLoad("53.4 75.6 75.6 75.6 75.6");
    Q_ASSERT(mtobridge::PlatoonConfiguration::getAxleLoads() == testList);
  }
  void testUpdateAxleLoadCommas() {
    std::list<double> testList = {53.5, 75.7, 75.7, 75.7, 75.7};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::updateAxleLoad("53.5,75.7,75.7,75.7,75.7"));
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::getAxleLoads());
    QVERIFY(mtobridge::PlatoonConfiguration::getAxleLoads() == testList);
  }
  void testUpdateAxleLoadNonsense() {
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::updateAxleLoad("I like turtles"));
  }
  void testUpdateAxleSpacingSpaces() {
    std::list<double> testList = {3.6576, 1.2192, 9.4488, 1.2192};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::updateAxleSpacing("3.6576 1.2192 9.4488 1.2192"));
    Q_ASSERT(mtobridge::PlatoonConfiguration::getAxleSpacings() == testList);
  }
  void testUpdateAxleSpacingCommas() {
    std::list<double> testList = {53.5, 75.7, 75.7, 75.7, 75.7};
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::updateAxleSpacing("53.5,75.7,75.7,75.7,75.7"));
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::getAxleSpacings());
    QVERIFY(mtobridge::PlatoonConfiguration::getAxleLoads() == testList);
  }
  void testUpdateAxleSpacingNonsense() {
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::updateAxleSpacing("I like turtles"));
  }
  void testUpdateNumberofTrucksNormal() {
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::updateNumberOfTrucks("15"));
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::getNumTrucks());
    QVERIFY(mtobridge::PlatoonConfiguration::getNumTrucks() == 15);
  }
  void testUpdateNumberofTrucksNegative() {
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::updateNumberOfTrucks("-8"));
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::getNumTrucks());
    QVERIFY(mtobridge::PlatoonConfiguration::getNumTrucks() != -8);
  }
  void testUpdateNumberofTrucksNonsense() {
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::updateNumberOfTrucks("Booyakasha"));
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::getNumTrucks());
  }
  void testUpdateHeadwayNormal() {
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::updateHeadway("15"));
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::getHeadway());
    QVERIFY(mtobridge::PlatoonConfiguration::getHeadway() == 15);
  }
  void testUpdateHeadwayNegative() {
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::updateHeadway("-8"));
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::getHeadway());
    QVERIFY(mtobridge::PlatoonConfiguration::getHeadway() != -8);
  }
  void testUpdateHeadwayNonsense() {
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::updateHeadway("Booyakasha"));
    QVERIFY_THROWS_NO_EXCEPTION(mtobridge::PlatoonConfiguration::getHeadway());
  }
  };
  QTEST_MAIN(TestPlatoonConfiguration)
#include "test_PlatoonConfiguration.moc"
