#include "averages.h"
#include "ui_averages.h"
#include "../calculator/calculator.h"
#include <tsettings.h>
#include <QSettings>

struct AveragesPrivate{
    Calc calc;
    QSettings settings;
    tSettings tsettings;
};

Averages::Averages(QWidget* parent) : QWidget(parent), ui(new Ui::Averages){
    ui->setupUi(this);
    d = new AveragesPrivate();
    updateAverages();
}

Averages::~Averages(){
    delete d;
    delete ui;
}

void Averages::updateAverages(){
    QStringList classes = d->settings.childGroups();
    classes.removeAll("theGrades"); // remove app config object
    if (classes.length() == 0){
        ui->gpaLabel->setText("");
        ui->infoLabel->setText(tr("No grades are set. Please set some in the Grades tab. If your institution uses qualitative grades, please set it also by clicking on the icon menu -> Options."));
    } else {
        ui->infoLabel->setText(tr("Your calculated GPA is"));
        double gpaScore;
        d->calc.clearGPA();
        for (int i=0; i < classes.length(); i++){
            QString curClass = classes[i];
            int classCreds = d->settings.value(curClass+"/credits").toInt();

             // calculate weighted score
            QStringList componentGrades = d->tsettings.delimitedList(curClass+"/component_grades");
            QStringList componentWeights = d->tsettings.delimitedList(curClass+"/component_weights");
            d->calc.clearScore();
            for (int i=0; i < componentGrades.length(); i++){
                    d->calc.addWeightedScore(componentGrades[i].toDouble(),
                                             componentWeights[i].toDouble());
            }

            double classScore = d->calc.getFinalScore();
            if (d->tsettings.value("theGrades/qual_enabled").toBool()){
                classScore = d->calc.findQualitativeGrade(classScore)["value"].toDouble();
            }
            d->calc.addWeightedGPA(classScore, classCreds);
        }
        gpaScore = d->calc.getGPA();
        ui->gpaLabel->setText(QString::number(gpaScore));
    }
}
