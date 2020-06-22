#include "grades.h"
#include "ui_grades.h"

#include "widget/gradewidget.h"
#include "edit/edit.h"
#include "../calculator/calculator.h"

#include <tpopover.h>
#include <ttoast.h>
#include <tsettings.h>

#include <QDebug>

#include <QRandomGenerator>

struct GradesPrivate{
    QList<GradeWidget*> grades;
    QSettings settings;  // because tSettings childGroups() is broken for me
    tSettings tsettings; // tSettings is a QSettings wrapper, should read the same files
    Calc calcObject;
};

Grades::Grades(QWidget* parent) : QWidget(parent), ui(new Ui::Grades){
    ui->setupUi(this);

    d = new GradesPrivate();

    connect(this, &Grades::spawnAddOrEditDialog,
            this, &Grades::onAddOrEditSpawned);

    qDebug() << "theGrades: Updating grades from config file";
    updateListing();
}

Grades::~Grades(){
    delete d;
    delete ui;
}

void Grades::on_addClassButton_clicked(){
    // we set a random number as the new class ID
    int newID = QRandomGenerator::global()->bounded(0,1000000);
    emit spawnAddOrEditDialog(true, newID);
}

void Grades::onAddOrEditSpawned(bool isNew, int id){
    EditOrNew* popover = new EditOrNew(this, isNew, id);
    tPopover* p = new tPopover(popover);
    connect(popover, &EditOrNew::classAdded,
                this,    &Grades::updateListing);        // on add class button
    if (isNew){
       qDebug() << "theGrades: New ID " << id;    // display selected widget's ID
    } else {
        qDebug() << "theGrades: Editing ID " << id;    // display selected widget's ID
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
    // clear all items
    for (int i=0; i < ui->gradesArea->count(); i++){
        QLayoutItem* e = ui->gradesArea->itemAt(i);
        e->widget()->deleteLater();
    }
    QStringList classes = d->settings.childGroups();
    for (int i=0; i < classes.length(); i++){
        QString curClass = classes[i];
        QString className = d->settings.value(curClass+"/name").toString();
        int classId = curClass.toInt();
        int classCreds = d->settings.value(curClass+"/credits").toInt();

         // calculate weighted score
        QStringList componentGrades = d->tsettings.delimitedList(curClass+"/component_grades");
        QStringList componentWeights = d->tsettings.delimitedList(curClass+"/component_weights");
        d->calcObject.clearScore();
        for (int i=0; i < componentGrades.length(); i++){
                d->calcObject.addWeightedScore(componentGrades[i].toDouble(),
                                               componentWeights[i].toDouble());
        }

        double calcScore = d->calcObject.getFinalScore();

        GradeWidget* g = new GradeWidget(nullptr, classId);
        connect(g, &GradeWidget::spawnAddOrEditDialog,
                this, &Grades::onAddOrEditSpawned);
        connect(g, &GradeWidget::doRemove,
                this, &Grades::onRemove);


        g->setData(className, classCreds, calcScore);
        ui->gradesArea->addWidget(g);
        d->grades.append(g);
    }

    emit updateAverages();
}

void Grades::onRemove(int id){
    d->settings.remove(QString::number(id));

    tToast* removedIndicator = new tToast(this);
    removedIndicator->setTitle(tr("Removed"));
    removedIndicator->setText(tr("Successfully removed class from list."));
    removedIndicator->setTimeout(3000);
    connect(removedIndicator, &tToast::dismissed, removedIndicator, &tToast::deleteLater);
    removedIndicator->show(this);

    qDebug() << "theGrades: Removed ID" << id;
    updateListing();
}
