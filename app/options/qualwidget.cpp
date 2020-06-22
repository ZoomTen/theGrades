#include "qualwidget.h"
#include "ui_qualwidget.h"

struct QualWidgetPrivate{
};

QualWidget::QualWidget(QWidget* parent) : QWidget(parent), ui(new Ui::QualWidget){
    ui->setupUi(this);

    d = new QualWidgetPrivate();
}

QualWidget::~QualWidget(){
    delete d;
    delete ui;
}

void QualWidget::on_deleteButton_pressed(){
    deleteLater();
}

void QualWidget::setData(QString name, double lower, double upper, double worth){
    ui->gradeLetter->setText(name);
    ui->lowerLimit->setValue(lower);
    ui->upperLimit->setValue(upper);
    ui->numericWorth->setValue(worth);
}

QList<QVariant> QualWidget::getEverything(){
    return {ui->gradeLetter->text(),
                           ui->lowerLimit->value(),
                           ui->upperLimit->value(),
                           ui->numericWorth->value()};
}
