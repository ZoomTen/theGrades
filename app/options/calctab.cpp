#include "calctab.h"
#include "ui_calctab.h"

#include <tsettings.h>

struct CalcOptionsPrivate{
    tSettings tsettings;
};

CalcOptions::CalcOptions(QWidget* parent) : QWidget(parent), ui(new Ui::CalcOptions){
    ui->setupUi(this);

    d = new CalcOptionsPrivate();

    ui->qualCheckbox->setChecked(d->tsettings.value("theGrades/qual_enabled").toBool());
}

CalcOptions::~CalcOptions(){
    delete d;
    delete ui;
}

void CalcOptions::on_qualCheckbox_toggled(bool checked){
    d->tsettings.setValue("theGrades/qual_enabled", checked);
}
