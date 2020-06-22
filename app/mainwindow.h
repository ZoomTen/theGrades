#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

struct MainWindowPrivate;
class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    private slots:
        void on_actionExit_triggered();
        void on_actionAbout_triggered();
        void on_actionOption_triggered();
        void on_actionSources_triggered();
        void on_actionFileBug_triggered();
        void resizeEvent(QResizeEvent *event);

        void on_averagesButton_toggled(bool checked);
        void on_gradesButton_toggled(bool checked);
    private:
        Ui::MainWindow* ui;
        MainWindowPrivate* d;
};
#endif // MAINWINDOW_H
