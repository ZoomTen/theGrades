#include "edit.h"
#include "ui_edit.h"

#include "addcomponent.h"

#include <QDebug>

struct EditOrNewPrivate{
    int id;
    QList<QTreeWidgetItem> glist;
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

    //qInfo() << d->glist.first().text(0); // fetch data
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
    AddComponent* cwindow = new AddComponent();
    connect(cwindow, &AddComponent::sendNewComponent,
            this,    &EditOrNew::catchNewComponent);
    cwindow->show();
}

void EditOrNew::catchNewComponent(QString name, double weight, double grade){
    QTreeWidgetItem *data = new QTreeWidgetItem(ui->gradeList);
    data->setText(0, name);
    data->setText(1, QString::number(weight)+"%");
    data->setText(2, QString::number(grade));
    d->glist.append(*data);
    ui->gradeList->addTopLevelItem(data);
}
