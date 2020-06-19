#include "grades.h"
#include "ui_grades.h"

#include "widget/gradewidget.h"
#include "edit/edit.h"

#include <tpopover.h>

#include <QDebug>

struct GradesPrivate{
    QList<GradeWidget*> grades;
};

Grades::Grades(QWidget* parent) : QWidget(parent), ui(new Ui::Grades){
    ui->setupUi(this);

    d = new GradesPrivate();

    connect(this, &Grades::spawnAddOrEditDialog,
            this, &Grades::onAddOrEditSpawned);
}

Grades::~Grades(){
    delete d;
    delete ui;
}

void Grades::on_addClassButton_clicked(){
    emit spawnAddOrEditDialog(true, 999); // the ID is determined as the
                                     // actual widget is created
}

void Grades::onAddOrEditSpawned(bool isNew, int id){
    EditOrNew* popover = new EditOrNew(this, isNew, id);
    tPopover* p = new tPopover(popover);
    if (isNew){
        // add new class
        connect(popover, &EditOrNew::classAdded,
                this,    &Grades::updateListing);        // on add class button
    } else {
        // update existing class (but which?)
        qInfo() << "Selected ID: " << id;    // display selected widget's ID
    }
    connect(popover, &EditOrNew::done,
            p, &tPopover::dismiss);        // on close
    connect(p, &tPopover::dismissed,
            p, &tPopover::deleteLater);        // delete popover
    connect(p, &tPopover::dismissed,
            popover, &EditOrNew::deleteLater); // delete widget
    p->show(this);
}

void Grades::updateListing(){
    GradeWidget* g = new GradeWidget(nullptr,
                        qrand() % 1999); // assign random ID for now
    connect(g, &GradeWidget::spawnAddOrEditDialog,
            this, &Grades::onAddOrEditSpawned);
    ui->gradesArea->addWidget(g);
    d->grades.append(g);
}
