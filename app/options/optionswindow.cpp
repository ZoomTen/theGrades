#include "optionswindow.h"
#include "ui_optionswindow.h"

struct OptionsPrivate{
};

Options::Options(QWidget* parent) : QWidget(parent), ui(new Ui::Options){
    ui->setupUi(this);

    d = new OptionsPrivate();
}

Options::~Options(){
    delete d;
    delete ui;
}
