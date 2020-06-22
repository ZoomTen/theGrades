#include "addcomponent.h"
#include "ui_addcomponent.h"
#include "edit.h"
#include <tmessagebox.h>
#include <QDebug>

struct AddComponentPrivate{
    bool addOrEdit;
    QList<QVariant> values;
};

AddComponent::AddComponent(QWidget* parent,
                           bool addOrEdit,
                           QList<QVariant> values) :
                           QWidget(parent), ui(new Ui::AddComponent){
    ui->setupUi(this);

    d = new AddComponentPrivate();

    d->addOrEdit = addOrEdit;

    if(values.length() != 0){
        d->values = values;
    } else {
        d->values = {0, "", 0.0, 0.0};
    }

    if(addOrEdit){
        qDebug() << "theGrades: New component";
        ui->titleLabel->setText(tr("Add Component"));
    } else {
        qDebug() << "theGrades: Editing component ID" << d->values[ComponentID].toInt();
        ui->titleLabel->setText(tr("Edit Component"));
        ui->componentName->setText(values[ComponentName].toString());
        ui->weightValue->setValue(values[ComponentWeight].toDouble()/.01);
        ui->gradeValue->setValue(values[ComponentValue].toDouble());
    }
}

AddComponent::~AddComponent(){
    delete ui;
}

void AddComponent::on_doneButton_clicked(){
    tMessageBox* error = new tMessageBox(this);
    error->setIcon(tMessageBox::Critical);
    if (ui->componentName->text() == ""){
        error->setWindowTitle(tr("Name undefined!"));
        error->setText(tr("Please enter the component name."));
        error->exec();
    } else if (ui->weightValue->value() == 0){
        error->setWindowTitle(tr("Weight empty!"));
        error->setText(tr("Grade weight can't be 0."));
        error->exec();
    } else{
        emit sendNewComponent(d->addOrEdit,
                              d->values[ComponentID].toInt(),
                              ui->componentName->text(),
                              ui->weightValue->value(),
                              ui->gradeValue->value()
                            );

        close();
    }
    error->deleteLater();
}
