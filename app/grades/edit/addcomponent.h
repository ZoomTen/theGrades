#ifndef ADD_COMPONENT_H
#define ADD_COMPONENT_H

#include <QWidget>

namespace Ui{
    class AddComponent;
}

class AddComponent : public QWidget{
    Q_OBJECT

    public:
        explicit AddComponent(QWidget* parent = nullptr);
        ~AddComponent();

    signals:
        void sendNewComponent(QString name, double weight, double grade);

    private:
        Ui::AddComponent* ui;

    private slots:
        void on_doneButton_clicked();
};

#endif
