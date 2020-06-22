#include "calctab.h"
#include "ui_calctab.h"

struct CalcOptionsPrivate{
};

CalcOptions::CalcOptions(QWidget* parent) : QWidget(parent), ui(new Ui::CalcOptions){
    ui->setupUi(this);

    d = new CalcOptionsPrivate();
}

CalcOptions::~CalcOptions(){
    delete d;
    delete ui;
}
