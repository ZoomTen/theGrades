#include "addcomponent.h"
#include "ui_addcomponent.h"
#include "edit.h"
#include <tmessagebox.h>

AddComponent::AddComponent(QWidget* parent) : QWidget(parent), ui(new Ui::AddComponent){
    ui->setupUi(this);
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
        emit sendNewComponent(ui->componentName->text(),
                              ui->weightValue->value(),
                              ui->gradeValue->value()
                            );

        close();
    }
    error->deleteLater();
}
