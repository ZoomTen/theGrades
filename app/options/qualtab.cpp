#include "qualtab.h"
#include "ui_qualtab.h"

struct QualOptionsPrivate{
};

QualOptions::QualOptions(QWidget* parent) : QWidget(parent), ui(new Ui::QualOptions){
    ui->setupUi(this);

    d = new QualOptionsPrivate();
}

QualOptions::~QualOptions(){
    delete d;
    delete ui;
}
