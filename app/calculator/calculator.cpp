#include "calculator.h"
#include <QList>

struct CalcPrivate{
    double score;

    double gpaCounter;
    double gpaSum;
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
