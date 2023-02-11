#include "solver.hpp"
#include "solverVisual.hpp"

namespace mtobridge {
SolverVisual::SolverVisual(QTabWidget* parent) : QWidget(parent) {
    createPage();
    parent->addTab(this, "Solver");
}

SolverVisual::~SolverVisual() {}

void SolverVisual::visualize() {
    
}

void SolverVisual::errorOccurred(QString error) {
    QMessageBox::critical(this, QString("Error!"), error);
}

void SolverVisual::createPage() {
    setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));
    QVBoxLayout* pageLayout = new QVBoxLayout();
    setLayout(pageLayout);

    QWidget* topHalf = new QWidget(this);
    QHBoxLayout* topHalfLayout = new QHBoxLayout();
    topHalf->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
        QSizePolicy::Policy::Expanding));
    topHalf->setLayout(topHalfLayout);


    // set up chart
    {
        auto* chartLayout = new QGridLayout();
        QWidget* mChartWidget = new QWidget(this);
        mChartWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
            QSizePolicy::Policy::Expanding));
        mChartWidget->setLayout(chartLayout);

        QChart* mChart = new QChart();
        mChart->legend()->hide();
        mChart->createDefaultAxes();

        QChartView* mChartView = new QChartView(mChart, mChartWidget);
        mChartView->setRenderHint(QPainter::Antialiasing);
        mChartView->resize(300, 300);
        mChartView->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
            QSizePolicy::Policy::Expanding));
        chartLayout->addWidget(mChartView, 0, 0);
        topHalfLayout->addWidget(mChartWidget);
    }

    QVBoxLayout* inputLayout = new QVBoxLayout();
    QWidget* mInputWidget = new QWidget(this);
    mInputWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
        QSizePolicy::Policy::Expanding));
    mInputWidget->setLayout(inputLayout);
    mInputWidget->setFixedWidth(200);

    this->saveLoadGroup = new QGroupBox("Save/Load From File", this);
    inputLayout->addWidget(this->saveLoadGroup);
    QVBoxLayout* saveLoadBox = new QVBoxLayout;
    this->saveLoadGroup->setLayout(saveLoadBox);
    QPushButton* saveButton = new QPushButton("Save Solver Configuration", this);
    QObject::connect(saveButton, &QPushButton::clicked, this, [&]() {
        //save to file
        });
    saveLoadBox->addWidget(saveButton);
    QPushButton* loadButton = new QPushButton("Load Solver Configuration", this);
    QObject::connect(loadButton, &QPushButton::clicked, this, [&]() {
        //load from file
        });
    saveLoadBox->addWidget(loadButton);
    saveLoadBox->addStretch(1);
    this->saveLoadGroup->setFixedHeight(100);

    this->forceSettingGroup = new QGroupBox("Force Type", this);
    inputLayout->addWidget(this->forceSettingGroup);
    QVBoxLayout* forceBox = new QVBoxLayout;
    this->forceSettingGroup->setLayout(forceBox);
    QRadioButton* positiveMomentButton = new QRadioButton("Positive Moment");
    positiveMomentButton->setChecked(true);
    QObject::connect(positiveMomentButton, &QPushButton::clicked, this, [&]() {
        Solver::updateForceType("Positive Moment");
        });
    forceBox->addWidget(positiveMomentButton);
    QRadioButton* negativeMomentButton = new QRadioButton("Negative Moment");
    QObject::connect(negativeMomentButton, &QPushButton::clicked, this, [&]() {
        Solver::updateForceType("Negative Moment");
        });
    forceBox->addWidget(negativeMomentButton);
    QRadioButton* shearButton = new QRadioButton("Shear");
    QObject::connect(shearButton, &QPushButton::clicked, this, [&]() {
        Solver::updateForceType("Shear");
        });
    forceBox->addWidget(shearButton);
    forceBox->addStretch(1);
    this->forceSettingGroup->setFixedHeight(100);

    this->solverSettingGroup = new QGroupBox("Solver Type", this);
    inputLayout->addWidget(this->solverSettingGroup);
    QVBoxLayout* solverBox = new QVBoxLayout;
    this->solverSettingGroup->setLayout(solverBox);
    QRadioButton* concernedButton = new QRadioButton("Concerned Section");
    concernedButton->setChecked(true);
    QObject::connect(concernedButton, &QPushButton::clicked, this, [&]() {
        Solver::updateSolverType("Concerned Section");
        });
    solverBox->addWidget(concernedButton);
    QRadioButton* criticalButton = new QRadioButton("Critical Section");
    QObject::connect(criticalButton, &QPushButton::clicked, this, [&]() {
        Solver::updateSolverType("Critical Section");
        });
    solverBox->addWidget(criticalButton);
    solverBox->addStretch(1);
    this->solverSettingGroup->setFixedHeight(75);


    this->calculateButton = new QPushButton("Run Analysis", this);
    QObject::connect(this->calculateButton, &QPushButton::clicked, this, [&]() {
        //call calculation
        });
    inputLayout->addWidget(this->calculateButton);
    topHalfLayout->addWidget(mInputWidget);
    pageLayout->addWidget(topHalf);

    QWidget* bottomHalf = new QWidget(this);
    bottomHalf->setFixedHeight(100);
    pageLayout->addWidget(bottomHalf);
}
};  // namespace mtobridge