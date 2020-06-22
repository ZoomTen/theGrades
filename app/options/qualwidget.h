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

    private:
        Ui::QualWidget* ui;
        QualWidgetPrivate* d;
};

#endif
