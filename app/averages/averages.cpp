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
    if (classes.length() == 0){
        ui->gpaLabel->setText(tr("No grades set"));
    } else {
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
            d->calc.addWeightedGPA(d->calc.getFinalScore(), classCreds);
        }
        gpaScore = d->calc.getGPA();
        ui->gpaLabel->setText(QString::number(gpaScore));
    }
}
