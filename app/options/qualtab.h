#ifndef QUALTAB_H
#define QUALTAB_H

#include <QWidget>

namespace Ui{
    class QualOptions;
}

struct QualOptionsPrivate;
class QualOptions : public QWidget{
    Q_OBJECT

    public:
        explicit QualOptions(QWidget* parent = nullptr);
        ~QualOptions();

    private:
        Ui::QualOptions* ui;
        QualOptionsPrivate* d;
};

#endif
