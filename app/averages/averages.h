#ifndef AVERAGES_H
#define AVERAGES_H

#include <QWidget>

namespace Ui{
    class Averages;
}

class Averages : public QWidget{
    Q_OBJECT

    public:
        explicit Averages(QWidget* parent = nullptr);
        ~Averages();

    private:
        Ui::Averages* ui;
};

#endif
