#include "edit.h"
#include "ui_edit.h"

#include "addcomponent.h"

#include <tsettings.h>
#include <tmessagebox.h>

#include <QMenu>

#include <QDebug>

struct EditOrNewPrivate{
    int id;
    bool type;
    tSettings settings;
    QList<QVariant> selectedComponent;
};

EditOrNew::EditOrNew(QWidget* parent, bool type, int id) : QWidget(parent), ui(new Ui::EditOrNew){
    ui->setupUi(this);
    ui->title->setBackButtonShown(true);

    d = new EditOrNewPrivate();
    d->id = id;
    d->type = type;

    QString classKey = QString::number(d->id)+"/";

    if(type){
        // new class, so don't load any data
        ui->classButton->setText(tr("Add Class"));
        ui->title->setText(tr("New Class"));
    } else {
        // edit class, load data from config
        ui->classButton->setText(tr("Edit Class"));
        ui->title->setText(tr("Edit Class"));

        QString className = d->settings.value(classKey+"name").toString();
        int classCreds = d->settings.value(classKey+"credits").toInt();
        QStringList componentNames = d->settings.delimitedList(classKey+"component_names");
        QStringList componentWeights = d->settings.delimitedList(classKey+"component_weights");
        QStringList componentGrades = d->settings.delimitedList(classKey+"component_grades");
        for(int i = 0; i < componentNames.length(); i++){
            QTreeWidgetItem *data = new QTreeWidgetItem(ui->gradeList);
            data->setText(0, componentNames[i]);
            data->setText(1, componentWeights[i]);
            data->setText(2, componentGrades[i]);
            ui->gradeList->addTopLevelItem(data);
        }
        ui->className->setText(className);
        ui->creditsAmount->setValue(classCreds);

    }

    ui->gradeList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->gradeList,&QTreeWidget::customContextMenuRequested,
            this,         &EditOrNew::editComponentContextMenu);
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
    tMessageBox* error = new tMessageBox(this);
    error->setIcon(tMessageBox::Critical);
    int rowCount = ui->gradeList->topLevelItemCount();
    if(ui->className->text() == ""){
        error->setWindowTitle(tr("Class name empty!"));
        error->setText(tr("Please enter your class name."));
        error->exec();
    } else if (rowCount == 0){
        error->setWindowTitle(tr("Grade list empty!"));
        error->setText(tr("Please add some grade components."));
        error->exec();
    } else {
        QString classKey = QString::number(d->id)+"/";
        d->settings.setValue(classKey+"name",
                             QVariant( ui->className->text() )
                            );
        d->settings.setValue(classKey+"credits",
                             QVariant( ui->creditsAmount->value() )
                            );
        QStringList componentNames;
        QStringList componentWeights;
        QStringList componentGrades;
        for(int i=0; i < rowCount; i++){
            QTreeWidgetItem *currentRow = ui->gradeList->topLevelItem(i);
            componentNames.append(currentRow->text(0));
            componentWeights.append(currentRow->text(1));
            componentGrades.append(currentRow->text(2));
        }
        d->settings.setDelimitedList(classKey+"component_names", componentNames);
        d->settings.setDelimitedList(classKey+"component_weights", componentWeights);
        d->settings.setDelimitedList(classKey+"component_grades", componentGrades);
        if(d->type){
            qDebug() << "theGrades: Added ID" << d->id;
        } else {
            qDebug() << "theGrades: Edited ID" << d->id;
        }

        emit classAdded();  // temporary
        emit done();
    }
    error->deleteLater();
}

void EditOrNew::on_gradeButton_clicked(){
    AddComponent* cwindow = new AddComponent();
    connect(cwindow, &AddComponent::sendNewComponent,
            this,    &EditOrNew::catchNewComponent);
    cwindow->show();
}

void EditOrNew::catchNewComponent(bool isNew, int id, QString name, double weight, double grade){
    QTreeWidgetItem* data;
    if(isNew){
        data = new QTreeWidgetItem(ui->gradeList);
    } else {
        data = ui->gradeList->topLevelItem(id);
    }
    data->setText(0, name);
    data->setText(1, QString::number(weight*.01));
    data->setText(2, QString::number(grade));
    if(isNew){
        ui->gradeList->addTopLevelItem(data);
    }
}

void EditOrNew::editComponentContextMenu(const QPoint &p){
    QTreeWidgetItem *componentSelect = ui->gradeList->itemAt( p );
    if(componentSelect != nullptr){
        int componentID = ui->gradeList->indexOfTopLevelItem(componentSelect);
        qDebug() << "theGrades: selected component" << componentSelect->text(0) << ", ID" << componentID;
        d->selectedComponent = {componentID,
                                componentSelect->text(0),
                                componentSelect->text(1),
                                componentSelect->text(2)};
        QMenu* menu = new QMenu();

        menu->addSection("Component");
        menu->addAction(ui->actionEdit);
        menu->addAction(ui->actionRemove);

        connect(menu, &QMenu::aboutToHide,
                menu, &QMenu::deleteLater); // uninstantiate menu
        menu->popup(ui->gradeList->viewport()->mapToGlobal(p)); // viewport() takes into account the header
    }
}

void EditOrNew::on_actionEdit_triggered() {
    AddComponent* cwindow = new AddComponent(nullptr, false, d->selectedComponent);
    connect(cwindow, &AddComponent::sendNewComponent,
            this,    &EditOrNew::catchNewComponent);
    cwindow->show();
    qDebug() << "theGrades: Edit component" << d->selectedComponent[0].toInt() << d->selectedComponent[1].toString();
}

void EditOrNew::on_actionRemove_triggered() {
    qDebug() << "theGrades: Remove component" << d->selectedComponent[0].toInt() << d->selectedComponent[1].toString();
}
