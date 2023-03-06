#include <QTest>

#include "../../src/engine/engine.hpp"

class TestEngine : public QObject {
  Q_OBJECT

 private slots:

};

QTEST_MAIN(TestEngine)
#include "test_engine.moc"
