#include <QTest>

#include "../../src/solver/solver.hpp"
#include "util/data_types.hpp"

class TestSolver : public QObject {
    Q_OBJECT

private:

private slots:
    void testSolverGetForceType() {
        std::string forceType;
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Positive Moment");
    }

    void testSolverGetSolverType() {
        std::string solverType;
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Concerned Section");
    }

    void testSolverUpdateForceValid1() {
        std::string forceType;
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Positive Moment");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateForceType("Negative Moment"));
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Negative Moment");
    }

    void testSolverUpdateForceValid2() {
        std::string forceType;
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Negative Moment");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateForceType("Shear"));
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Shear");
    }

    void testSolverUpdateForceValid3() {
        std::string forceType;
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Shear");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateForceType("Positive Moment"));
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Positive Moment");
    }

    void testSolverUpdateForceInvalid1() {
        std::string forceType;
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Positive Moment");

        QVERIFY_EXCEPTION_THROWN(mtobridge::Solver::updateForceType("Negative"), mtobridge::invalidConfigurationValue);
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Positive Moment");
    }

    void testSolverUpdateForceInvalid2() {
        std::string forceType;
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Positive Moment");

        QVERIFY_EXCEPTION_THROWN(mtobridge::Solver::updateForceType(""), mtobridge::invalidConfigurationValue);
        QVERIFY_THROWS_NO_EXCEPTION(forceType = mtobridge::Solver::getForceType());
        QCOMPARE(forceType, "Positive Moment");
    }
    
    void testSolverUpdateTypeValid1() {
        std::string solverType;
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Concerned Section");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateSolverType("Critical Section"));
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Critical Section");
    }

    void testSolverUpdateTypeValid2() {
        std::string solverType;
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Critical Section");

        QVERIFY_THROWS_NO_EXCEPTION(mtobridge::Solver::updateSolverType("Concerned Section"));
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Concerned Section");
    }

    void testSolverUpdateTypeInvalid1() {
        std::string solverType;
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Concerned Section");

        QVERIFY_EXCEPTION_THROWN(mtobridge::Solver::updateSolverType("Critical"), mtobridge::invalidConfigurationValue);
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Concerned Section");
    }

    void testSolverUpdateTypeInvalid2() {
        std::string solverType;
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Concerned Section");

        QVERIFY_EXCEPTION_THROWN(mtobridge::Solver::updateSolverType(""), mtobridge::invalidConfigurationValue);
        QVERIFY_THROWS_NO_EXCEPTION(solverType = mtobridge::Solver::getSolverType());
        QCOMPARE(solverType, "Concerned Section");
    }
};

QTEST_MAIN(TestSolver)
#include "test_solver.moc"