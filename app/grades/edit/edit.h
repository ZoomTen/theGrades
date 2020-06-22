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
        explicit EditOrNew(QWidget* parent = nullptr, bool Type = Edit, int id = 0);
        ~EditOrNew();

        enum Type{
            Edit,
            New
        };

        enum Alisases{
            ComponentID,
            ComponentName,
            ComponentWeight,
            ComponentValue
        };

    signals:
        void done();
        void classAdded();

    private:
        Ui::EditOrNew* ui;
        EditOrNewPrivate* d;

    private slots:
        void on_title_backButtonClicked();
        void on_gradeButton_clicked();
        void on_classButton_clicked();

        void on_actionEdit_triggered();
        void on_actionRemove_triggered();

        void catchNewComponent(bool isNew, int id, QString name, double weight, double grade);

        void editComponentContextMenu(const QPoint &p);
};

#endif
