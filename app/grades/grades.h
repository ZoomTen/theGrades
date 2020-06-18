#ifndef GRADES_H
#define GRADES_H

#include <QWidget>

namespace Ui{
    class Grades;
}

class Grades : public QWidget{
    Q_OBJECT

    public:
        explicit Grades(QWidget* parent = nullptr);
        ~Grades();

    private:
        Ui::Grades* ui;
};

#endif
