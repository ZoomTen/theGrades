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

    private:
        Ui::AddComponent* ui;
};

#endif
