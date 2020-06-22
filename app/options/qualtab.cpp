#include "qualtab.h"
#include "ui_qualtab.h"

#include "qualwidget.h"

#include <tsettings.h>
#include <QDebug>

struct QualOptionsPrivate{
    tSettings tsettings;
    bool qualEnabled;
};

QualOptions::QualOptions(QWidget* parent) : QWidget(parent), ui(new Ui::QualOptions){
    ui->setupUi(this);

    d = new QualOptionsPrivate();

    checkQualEnabled();

    loadEverything();
}

QualOptions::~QualOptions(){
    delete d;
    delete ui;
}

void QualOptions::on_addGradeButton_pressed(){
    QualWidget* q = new QualWidget();
    ui->qualGradesArea->addWidget(q);
}

void QualOptions::checkQualEnabled(){
    d->qualEnabled = d->tsettings.value("theGrades/qual_enabled").toBool();
    qDebug() << "theGrades: Qual. enabled:" << d->qualEnabled;
    ui->stackedWidget->setCurrentIndex((int)d->qualEnabled);
}

void QualOptions::loadEverything(){
    d->qualEnabled = d->tsettings.value("theGrades/qual_enabled").toBool();
    if(d->qualEnabled){
        QStringList gradeNames = d->tsettings.delimitedList("theGrades/grades_name");
        QStringList gradeUpperLimits = d->tsettings.delimitedList("theGrades/grades_upper_limits");
        QStringList gradeLowerLimits = d->tsettings.delimitedList("theGrades/grades_lower_limits");
        QStringList gradeWorth = d->tsettings.delimitedList("theGrades/grades_worth");
        for (int i=0; i<gradeNames.length(); i++){
            QualWidget* q = new QualWidget();
            q->setData(gradeNames[i],
                       QVariant(gradeLowerLimits[i]).toDouble(),
                       QVariant(gradeUpperLimits[i]).toDouble(),
                       QVariant(gradeWorth[i]).toDouble()
                       );
            ui->qualGradesArea->addWidget(q);
        }
    }
}

void QualOptions::saveEverything(){
    d->qualEnabled = d->tsettings.value("theGrades/qual_enabled").toBool();
    if (d->qualEnabled){
        int qualCount = ui->qualGradesArea->count();
        if (qualCount > 0){
            qDebug() << "theGrades: saving qualitative grade definitions";
            QStringList gradeNames;
            QStringList gradeUpperLimits;
            QStringList gradeLowerLimits;
            QStringList gradeWorth;
            for (int i=0; i < qualCount; i++){
                QLayoutItem* curWidget = ui->qualGradesArea->itemAt(i);
                QualWidget* curQual =(QualWidget*)curWidget->widget();
                QList<QVariant> curList = curQual->getEverything();
                gradeNames.append(curList[0].toString());
                gradeLowerLimits.append(curList[1].toString());
                gradeUpperLimits.append(curList[2].toString());
                gradeWorth.append(curList[3].toString());
                qDebug() << "theGrades: saving" << curList;
            }
            d->tsettings.setDelimitedList("theGrades/grades_name",gradeNames);
            d->tsettings.setDelimitedList("theGrades/grades_lower_limits",gradeLowerLimits);
            d->tsettings.setDelimitedList("theGrades/grades_upper_limits",gradeUpperLimits);
            d->tsettings.setDelimitedList("theGrades/grades_worth",gradeWorth);
        }
    }
}
