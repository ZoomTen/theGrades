#include "edit.h"
#include "ui_edit.h"

#include "addcomponent.h"

#include <QDebug>

struct EditOrNewPrivate{
    int id;
    QList<QTreeWidgetItem> glist;
    AddComponent cwindow;
};

EditOrNew::EditOrNew(QWidget* parent, bool type, int id) : QWidget(parent), ui(new Ui::EditOrNew){
    ui->setupUi(this);
    ui->title->setBackButtonShown(true);

    d = new EditOrNewPrivate();
    d->id = id;


    if(type){
        ui->classButton->setText(tr("Add Class"));
        ui->title->setText(tr("New Class"));
    } else {
        ui->classButton->setText(tr("Edit Class"));
        ui->title->setText(tr("Edit Class"));
    }

    QTreeWidgetItem *data = new QTreeWidgetItem(ui->gradeList);
    data->setText(0, "Finals");
    data->setText(1, "80%");
    data->setText(2, "4.0");
    d->glist.append(*data);
    ui->gradeList->addTopLevelItem(data);

    qInfo() << d->glist.first().text(0);
}

EditOrNew::~EditOrNew(){
    delete d;
    delete ui;
}

void EditOrNew::on_title_backButtonClicked(){
    emit done();
}

void EditOrNew::on_classButton_clicked(){
    qInfo() << "Done something to ID " << d->id;

    emit classAdded();  // temporary
    emit done();
}

void EditOrNew::on_gradeButton_clicked(){
    d->cwindow.show();
}
