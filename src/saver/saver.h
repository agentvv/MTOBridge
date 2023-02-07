#ifndef SAVER_H
#define SAVER_H

#include <QWidget>
#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class saver; }
QT_END_NAMESPACE

class saver : public QWidget
{
    Q_OBJECT

public:
    saver(QWidget *parent = nullptr);
    ~saver();
    struct MockTruckT {
      std::vector<double> axleLoad {};
      std::vector<double> axleSpacing {};
      quint8 numberOfTrucks;
      double headway;
    };

    struct MockBridgeT {
      quint8 numberSpans;
      std::vector<double> spanLength {};
      double concernedSection;
      double discretizationLength;
    };

    struct MockSolverT {
      enum ForceE {
        POSITIVE_MOMENT,
        NEGATIVE_MOMENT,
        SHEAR
      } forceType;
      enum SolverE {
        CONCERNED,
        CRITICAL
      } solverType;
    };

public slots:
//! [save and load functions declaration]
    void savePlatoonConfiguration(saver::MockTruckT PlatoonT);
    void loadFromFile();

private slots:
    void on_saveTruck_clicked();
    void on_loadTruck_clicked();



private:
    Ui::saver *ui;
};
#endif // SAVER_H
