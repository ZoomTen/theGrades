#include "calculator.h"
#include <QList>
#include <tsettings.h>

struct CalcPrivate{
    double score;

    double gpaCounter;
    double gpaSum;

    tSettings settings;
};

Calc::Calc(){
    d = new CalcPrivate();
    clearScore();
    clearGPA();
}

Calc::~Calc(){
    delete d;
}

void Calc::addWeightedScore(double score, double weight){
    d->score += (score*weight);
}

void Calc::clearScore(){
    d->score = 0;
}

void Calc::addWeightedGPA(double score, double weight){
    d->gpaSum += (score*weight);
    d->gpaCounter += weight;
}

void Calc::clearGPA(){
    d->gpaSum = 0;
    d->gpaCounter = 0;
}

double Calc::getFinalScore(){
    return d->score;
}

double Calc::getGPA(){
    return (d->gpaSum / d->gpaCounter);
}

QMap<QString, QVariant> Calc::findQualitativeGrade(double grade){
    QMap<QString, QVariant> q;
    QStringList gradeName = d->settings.delimitedList("theGrades/grades_name");
    QStringList lowerLimits = d->settings.delimitedList("theGrades/grades_lower_limits");
    QStringList upperLimits = d->settings.delimitedList("theGrades/grades_upper_limits");
    QStringList worth = d->settings.delimitedList("theGrades/grades_worth");
    for (int i=0; i<gradeName.length(); i++){
        if(QVariant(lowerLimits[i]).toDouble() <= grade){
            if(grade <= QVariant(upperLimits[i]).toDouble()){
                q["name"] = gradeName[i];
                q["value"] = worth[i];
                return q;
            }
        }
    }
    return q;
}
