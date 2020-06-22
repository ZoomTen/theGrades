#ifndef CALC_H
#define CALC_H

// this is a bog standard cpp object

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


    private:
        CalcPrivate* d;
};

#endif // CALC_H
