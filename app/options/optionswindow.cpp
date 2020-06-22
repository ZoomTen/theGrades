#include "optionswindow.h"
#include "ui_optionswindow.h"

#include <tstackedwidget.h>

#include <tsettings.h>

//struct OptionsPrivate{
    //tSettings settings;
//};

Options::Options(QWidget* parent) : QWidget(parent), ui(new Ui::Options){
    ui->setupUi(this);

    //d = new OptionsPrivate();
    settings = new tSettings();

    ui->stackedWidget->setCurrentAnimation(tStackedWidget::Lift);

    connect(settings, &tSettings::settingChanged,
            this, &Options::onSettingChanged);
}

Options::~Options(){
    //delete d;
    delete settings;
    delete ui;
}

void Options::on_optionTabs_currentRowChanged(int row){
    ui->stackedWidget->setCurrentIndex(row);
}

void Options::resizeEvent(QResizeEvent *e) {
    // Automatically adjust sidebar size
    if (this->width() < SC_DPI(500)) {
        // collapse sidebar
        ui->optionTabs->setMaximumSize(SC_DPI(40), QWIDGETSIZE_MAX);
    } else {
        // expand sidebar
        ui->optionTabs->setMaximumSize(SC_DPI(130), QWIDGETSIZE_MAX);
    }
}

void Options::onSettingChanged(QString key, QVariant value){
    ui->qualOptions->checkQualEnabled();
    emit settingsChanged();
}

void Options::closeEvent(QCloseEvent *e){
    ui->qualOptions->saveEverything();
    e->accept();
}
