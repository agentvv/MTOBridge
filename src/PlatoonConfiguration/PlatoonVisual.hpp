#pragma once
#include <QtWidgets>
namespace mtobridge {
class PlatoonVisual : public QWidget {
  Q_OBJECT

 public:
  PlatoonVisual(QWidget *parent = nullptr);
  ~PlatoonVisual();

  QGraphicsScene *getScene() { return mSceneWidget; }

 public slots:
  void platoonConfigured();
  void saveButtonClicked();
  void loadButtonClicked();

 private:
  void createPage();

  QGraphicsItemGroup *makeTruck();

  QTabWidget *mTabWidget;
  QWidget *mPage;

  QWidget *mInputWidget;
  QLabel *mAxleLoadLabel;
  QLineEdit *mAxleLoad;
  QLabel *mAxleSpacingLabel;
  QLineEdit *mAxleSpacing;
  QLabel *mNumberOfTrucksLabel;
  QLineEdit *mNumberOfTrucks;
  QLabel *mHeadwayLabel;
  QLineEdit *mHeadway;

  QPushButton *mSaveButton;
  QPushButton *mLoadButton;

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
