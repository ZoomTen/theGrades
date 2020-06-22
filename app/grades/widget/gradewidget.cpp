#include "gradewidget.h"
#include "ui_gradewidget.h"

#include "../edit/edit.h"
#include "../grades.h"

#include <QMenu>
#include <QContextMenuEvent>
#include <QDebug>

#include <tmessagebox.h>

struct GradesWidgetPrivate{
    int id;
};

GradeWidget::GradeWidget(QWidget* parent, int id) : QWidget(parent), ui(new Ui::GradeWidget){
    ui->setupUi(this);

    d = new GradesWidgetPrivate();

    d->id=id;
}

GradeWidget::~GradeWidget(){
    delete d;
    delete ui;
}

int GradeWidget::getId(){
    return d->id;
}

void GradeWidget::setData(QString className, int credits, double calcScore){
    ui->classLabel->setText(className);
    ui->creditsLabel->setText(tr("%1 credit(s)").arg(QString::number(credits)));
    ui->gradeLabel->setText(QString::number(calcScore));
}

void GradeWidget::contextMenuEvent(QContextMenuEvent* e){
    QMenu* menu = new QMenu();

    menu->addSection(tr("Class"));
    menu->addAction(ui->actionEdit);
    menu->addAction(ui->actionRemove);

    qDebug() << "theGrades: Selected ID " << d->id;    // display selected widget's ID
    connect(menu, &QMenu::aboutToHide,
            menu, &QMenu::deleteLater); // uninstantiate menu
    menu->popup(e->globalPos()); // open menu on right click
}

void GradeWidget::on_actionEdit_triggered() {
    emit spawnAddOrEditDialog(false, d->id);
}

void GradeWidget::on_actionRemove_triggered() {
    tMessageBox* removeprompt = new tMessageBox(this);
    removeprompt->setIcon(tMessageBox::Question);
    removeprompt->setStandardButtons(tMessageBox::Yes | tMessageBox::No);
    removeprompt->setDefaultButton(tMessageBox::No);
    removeprompt->setWindowTitle(tr("Remove class?"));
    removeprompt->setText(tr("Do you want to remove this class?"));
    int value = removeprompt->exec();
    if (value == tMessageBox::Yes){
        qDebug() << "theGrades: Selected YES on remove class prompt.";
        emit doRemove(d->id);
    }
}
