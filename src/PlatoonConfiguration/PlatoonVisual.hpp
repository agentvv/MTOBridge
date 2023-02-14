#pragma once
#include <QtWidgets>
namespace mtobridge {
class PlatoonVisual : public QWidget {
  Q_OBJECT

 public:
  PlatoonVisual(QTabWidget *parent = nullptr);
  ~PlatoonVisual();
  QGraphicsScene* mSceneWidget;
 public slots:
  void buttonClicked();
  void saveButtonClicked();
  void loadButtonClicked();

 private:
  void createPage();

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

  QPushButton *mButton;
  QPushButton *mSaveButton;
  QPushButton *mLoadButton;

  QGraphicsView* mViewWidget;
};
}  // namespace mtobridge
