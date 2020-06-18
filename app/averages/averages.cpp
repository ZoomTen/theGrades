#include "averages.h"
#include "ui_averages.h"

Averages::Averages(QWidget* parent) : QWidget(parent), ui(new Ui::Averages){
    ui->setupUi(this);
}

Averages::~Averages(){
    delete ui;
}
