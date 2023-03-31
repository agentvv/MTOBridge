#pragma once
#include <QtWidgets>
#include <util/data_types.hpp>

namespace mtobridge {
class PlatoonVisual : public QWidget {
  Q_OBJECT

 public:
  PlatoonVisual(QWidget *parent = nullptr);
  ~PlatoonVisual();

  QGraphicsScene *getScene() { return mSceneWidget; }

public slots:
  void loadConfiguration(MockTruckT config);

 private slots:
  void numAxlesChanged(int i);
  void validateLoadText(QString s);
  void validateSpacingText(QString s);
  void platoonConfigured();
  void saveButtonClicked();
  void loadButtonClicked();
  

 private:
  void createPage();

  QGraphicsItemGroup *makeTruck();

  QTabWidget *mTabWidget;
  QWidget *mPage;
  QGridLayout *inputLayout;

  QWidget *mInputWidget;
  QLabel *mAxleLoadLabel;
  QLineEdit *mAxleLoad;
  QLabel *mAxleSpacingLabel;
  QLineEdit *mAxleSpacing;
  QLabel *mNumberOfTrucksLabel;
  QSpinBox *mNumberOfTrucks;
  QLabel *mHeadwayLabel;
  QDoubleSpinBox *mHeadway;
  QSpinBox *mNumberOfAxles;
  QLabel *mNumberOfAxlesLabel;
  QList<QLineEdit*> axleLoadList;
  QList<QLineEdit*> axleSpacingList;
  QPushButton *mSaveButton;
  QPushButton *mLoadButton;
  QDoubleValidator *axleLoadValidator;
  QDoubleValidator *axleSpacingValidator;

  QGraphicsScene *mSceneWidget;
  QGraphicsView *mViewWidget;
  QGraphicsRectItem *truckHead;
  QGraphicsRectItem *truckWindow;
  QGraphicsRectItem *truckBody;
  QGraphicsEllipseItem *truckWheel;
  QGraphicsEllipseItem *truckRim;
  QGraphicsItemGroup *truck;
};
}  // namespace mtobridge
