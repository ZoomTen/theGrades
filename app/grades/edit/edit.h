#ifndef EDIT_OR_NEW_H
#define EDIT_OR_NEW_H

#include <QWidget>

namespace Ui{
    class EditOrNew;
}

struct EditOrNewPrivate;
class EditOrNew : public QWidget{
    Q_OBJECT

    public:
        explicit EditOrNew(QWidget* parent = nullptr, bool type = Edit, int id = 0);
        ~EditOrNew();

        enum Type{
            Edit,
            New
        };

    signals:
        void done();
        void classAdded(); // temporary

    private:
        Ui::EditOrNew* ui;
        EditOrNewPrivate* d;

    private slots:
        void on_title_backButtonClicked();
        void on_gradeButton_clicked();
        void on_classButton_clicked();

        void catchNewComponent(QString name, double weight, double grade);
};

#endif
