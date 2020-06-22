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
