#ifndef GRADEWIDGET_H
#define GRADEWIDGET_H

#include <QWidget>

namespace Ui{
    class GradeWidget;
}

struct GradesWidgetPrivate;
class GradeWidget : public QWidget{
    Q_OBJECT

    public:
        explicit GradeWidget(QWidget* parent = nullptr, int id = 0);
        ~GradeWidget();

        int getId();
        void setData(QString className, int credits, QVariant calcScore);

    signals:
        void spawnAddOrEditDialog(bool isNew, int id);
        void doRemove(int id);

    private:
        Ui::GradeWidget* ui;
        GradesWidgetPrivate* d;
        void contextMenuEvent(QContextMenuEvent* e);

    private slots:
        void on_actionEdit_triggered();
        void on_actionRemove_triggered();
};

#endif
