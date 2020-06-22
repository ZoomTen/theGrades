#ifndef CALCTAB_H
#define CALCTAB_H

#include <QWidget>

namespace Ui{
    class CalcOptions;
}

struct CalcOptionsPrivate;
class CalcOptions : public QWidget{
    Q_OBJECT

    public:
        explicit CalcOptions(QWidget* parent = nullptr);
        ~CalcOptions();

    private:
        Ui::CalcOptions* ui;
        CalcOptionsPrivate* d;

    private slots:
        void on_qualCheckbox_toggled(bool checked);
};

#endif
