#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QWidget>

namespace Ui{
    class Options;
}

struct OptionsPrivate;
class Options : public QWidget{
    Q_OBJECT

    public:
        explicit Options(QWidget* parent = nullptr);
        ~Options();

    private:
        Ui::Options* ui;
        OptionsPrivate* d;

    private slots:
        void on_optionTabs_currentRowChanged(int row);
        void resizeEvent(QResizeEvent *e);
};

#endif
