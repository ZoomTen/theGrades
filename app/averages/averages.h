#ifndef AVERAGES_H
#define AVERAGES_H

#include <QWidget>

namespace Ui{
    class Averages;
}

struct AveragesPrivate;
class Averages : public QWidget{
    Q_OBJECT

    public:
        explicit Averages(QWidget* parent = nullptr);
        ~Averages();

    private:
        Ui::Averages* ui;
        AveragesPrivate* d;

    private slots:
        void updateAverages();
};

#endif
