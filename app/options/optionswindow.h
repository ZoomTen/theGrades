#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <tsettings.h>
namespace Ui{
    class Options;
}

//struct OptionsPrivate;
class Options : public QWidget{
    Q_OBJECT

    public:
        explicit Options(QWidget* parent = nullptr);
        ~Options();

    signals:
        void settingsChanged();

    private:
        Ui::Options* ui;
        //OptionsPrivate* d;
        tSettings* settings;

    private slots:
        void on_optionTabs_currentRowChanged(int row);
        void onSettingChanged(QString k, QVariant v);
//        void resizeEvent(QResizeEvent *e);

    protected:
        void closeEvent(QCloseEvent *e);
};

#endif
