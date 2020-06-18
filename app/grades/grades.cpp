#include "grades.h"
#include "ui_grades.h"

#include "widget/gradewidget.h"

struct GradesPrivate{
    QList<GradeWidget*> grades;
};

Grades::Grades(QWidget* parent) : QWidget(parent), ui(new Ui::Grades){
    ui->setupUi(this);

    d = new GradesPrivate();
}

Grades::~Grades(){
    delete d;
    delete ui;
}

void Grades::on_addClassButton_clicked(){
    GradeWidget* g = new GradeWidget();
    ui->gradesArea->addWidget(g);
    d->grades.append(g);
}
