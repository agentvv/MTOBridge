#pragma once
#include <QtWidgets>
namespace mtobridge {
class PlatoonVisual : public QWidget {
  Q_OBJECT

 public:
  PlatoonVisual(QTabWidget *parent = nullptr);
  ~PlatoonVisual();
 public slots:
  void buttonClicked();

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
};
}  // namespace mtobridge
