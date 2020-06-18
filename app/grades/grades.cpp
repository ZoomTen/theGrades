#include "grades.h"
#include "ui_grades.h"

Grades::Grades(QWidget* parent) : QWidget(parent), ui(new Ui::Grades){
    ui->setupUi(this);
}

Grades::~Grades(){
    delete ui;
}
