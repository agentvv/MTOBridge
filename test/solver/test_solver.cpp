#include <QTest>

#include "../../src/solver/solver.hpp"

class TestSolver : public QObject {
    Q_OBJECT

private:

private slots:
    void testSolverDefault() {
        std::string forceType, solverType;
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(forceType, "Positive Moment");
        QCOMPARE(solverType, "Concerned Section");
    }

    void testSolverUpdateForceValid() {
        std::string forceType;
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Positive Moment");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateForceType("Negative Moment"));
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Negative Moment");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateForceType("Shear"));
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Shear");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateForceType("Positive Moment"));
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Positive Moment");
    }

    void testSolverUpdateForceInvalid() {
        std::string forceType;
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Positive Moment");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateForceType("Garbage"));/////////////////////////////////////////////////////////////////////////////////////////////////////////
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Positive Moment");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateForceType(""));/////////////////////////////////////////////////////////////////////////////////////////////////////////
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Positive Moment");
    }

    void testSolverUpdateTypeValid() {
        std::string solverType;
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Concerned Section");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateSolverType("Critical Section"));
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Critical Section");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateSolverType("Concerned Section"));
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Concerned Section");
    }

    void testSolverUpdateTypeInvalid() {
        std::string solverType;
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Concerned Section");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateSolverType("Garbage"));/////////////////////////////////////////////////////////////////////////////////////////////////////////
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Concerned Section");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateSolverType(""));/////////////////////////////////////////////////////////////////////////////////////////////////////////
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Concerned Section");
    }
};

QTEST_MAIN(TestSolver)
#include "test_solver.moc"