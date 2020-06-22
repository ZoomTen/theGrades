#include "optionswindow.h"
#include "ui_optionswindow.h"

#include <tstackedwidget.h>

struct OptionsPrivate{
};

Options::Options(QWidget* parent) : QWidget(parent), ui(new Ui::Options){
    ui->setupUi(this);

    d = new OptionsPrivate();

    ui->stackedWidget->setCurrentAnimation(tStackedWidget::Lift);
}

Options::~Options(){
    delete d;
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
