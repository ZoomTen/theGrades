#ifndef ADD_COMPONENT_H
#define ADD_COMPONENT_H

#include <QWidget>

namespace Ui{
    class AddComponent;
}

struct AddComponentPrivate;
class AddComponent : public QWidget{
    Q_OBJECT

    public:
        explicit AddComponent(QWidget* parent = nullptr,
                              bool addOrEdit = New,
                              QList<QVariant> values = {});
        ~AddComponent();

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
        void sendNewComponent(bool isNew, int id, QString name, double weight, double grade);

    private:
        Ui::AddComponent* ui;
        AddComponentPrivate* d;

    private slots:
        void on_doneButton_clicked();
};

#endif
