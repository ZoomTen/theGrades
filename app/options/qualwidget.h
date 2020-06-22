#ifndef QUALWIDGET_H
#define QUALWIDGET_H

#include <QWidget>

namespace Ui{
    class QualWidget;
}

struct QualWidgetPrivate;
class QualWidget : public QWidget{
    Q_OBJECT

    public:
        explicit QualWidget(QWidget* parent = nullptr);
        ~QualWidget();

        QList<QVariant> getEverything();

        void setData(QString, double, double, double);

    private:
        Ui::QualWidget* ui;
        QualWidgetPrivate* d;

    private slots:
        void on_deleteButton_pressed();
};

#endif
