#include "addcomponent.h"
#include "ui_addcomponent.h"

AddComponent::AddComponent(QWidget* parent) : QWidget(parent), ui(new Ui::AddComponent){
    ui->setupUi(this);
}

AddComponent::~AddComponent(){
    delete ui;
}
