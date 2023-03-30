#pragma once
#include <QtWidgets>
#include <vector>
#include "bridgeconfig.hpp"

namespace mtobridge {
class BridgeVisual : public QWidget {
  Q_OBJECT

 public:
  BridgeVisual(QWidget* parent = nullptr) : QWidget(parent) { createPage(); }
  ~BridgeVisual() {}

  QGraphicsScene* getScene() { return mScene; }

 public slots:
	void bridgeConfigEdited();
	void spanLengthChanged();
	void concernedSectionChanged();
	void discretizationLengthChanged();

 private:
	void createPage();
	void numberOfSpansDetermined(QGridLayout* bridgeInputLayout, QString numberOfSpans);
	QLabel* mSpanLengthLabel;
	QLineEdit* mSpanLength;
	QLabel* mConcernedSectionLabel;
	QLineEdit* mConcernedSection;
	QLabel* mNumberSpansLabel;
	QComboBox* mNumberSpans;
	QLabel* mDiscretizationLengthLabel;
	QLabel* mSpanLengthErrorLabel;
	QLabel* mConcernedSectionErrorLabel;
	QLabel* mDiscretizationLengthErrorLabel;

	QLineEdit* mDiscretizationLength;
	QWidget* bridgeInputWidget;
	QWidget* mVisualizerWidget;
	QGraphicsView* mVisualizerView;
	QGraphicsScene* mScene;
	QGraphicsRectItem* bridgeRect;
	QGraphicsRectItem* topLayerRect;
	QPushButton* previewButton;
	QWidget* bridgeIOWidget;
	QPushButton* saveButton;
	QPushButton* loadButton;
	BridgeConfiguration* bridgeConfiguration;

	std::vector<QLineEdit*> spanLengthLineBoxes{};
	std::vector<QLabel*> spanLengthErrorLables{};
	QGridLayout* bridgeInputLayout;
};
}  // namespace mtobridge