#ifndef CALC_H
#define CALC_H

#include <QMap>
#include <QVariant>

struct CalcPrivate;
class Calc{
    public:
        Calc();
        ~Calc();

        void addWeightedScore(double score, double weight);
        void clearScore();

        void addWeightedGPA(double score, double weight);
        void clearGPA();

        double getFinalScore();
        double getGPA();

        QMap<QString, QVariant> findQualitativeGrade(double grade);

    private:
        CalcPrivate* d;
};

#endif // CALC_H
