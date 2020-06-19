#ifndef GRADES_H
#define GRADES_H

#include <QWidget>

namespace Ui{
    class Grades;
}

struct GradesPrivate;
class Grades : public QWidget{
    Q_OBJECT

    public:
        explicit Grades(QWidget* parent = nullptr);
        ~Grades();

    private:
        Ui::Grades* ui;
        GradesPrivate* d;

    signals:
        void spawnAddOrEditDialog(bool isNew, int id);

    private slots:
        void on_addClassButton_clicked();

        void updateListing();
        void onAddOrEditSpawned(bool isNew, int id);
};

#endif
