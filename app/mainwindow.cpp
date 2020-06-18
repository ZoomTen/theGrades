// window
#include "mainwindow.h"
#include "ui_mainWindow.h"

// menu items
#include <QMenu>

// opening URLs
#include <QDesktopServices>
#include <QUrl>

// about dialog
#include <taboutdialog.h>

// the-libs CSD
#include <tcsdtools.h>

#include <tstackedwidget.h>

struct MainWindowPrivate {
    tCsdTools csd;
};

MainWindow::MainWindow(QWidget* parent):
  QMainWindow(parent), ui(new Ui::MainWindow) {
    // setup window
    ui->setupUi(this);
    d = new MainWindowPrivate();

    // register CSD actions
    d->csd.installMoveAction(ui->topWidget);
    d->csd.installResizeAction(this);

    // CSD layout
    QWidget* csd_widget = d->csd.csdBoxForWidget(this);
    ui->rightCsdLayout->addWidget(csd_widget);

    if (tCsdGlobal::windowControlsEdge() == tCsdGlobal::Left) {
       ui->leftCsdLayout->addWidget(csd_widget);
    } else {
        ui->rightCsdLayout->addWidget(csd_widget);
    }

    // icon menu
    QMenu* menu = new QMenu(this);

    QMenu* fileMenu = new QMenu(this);
    fileMenu->setTitle(tr("File"));
    fileMenu->addAction(ui->actionNew);  // New
    fileMenu->addAction(ui->actionOpen); // Open
    fileMenu->addSeparator();
    fileMenu->addAction(ui->actionSave);  // Save
    fileMenu->addAction(ui->actionSave_As); // Save As...
    menu->addMenu(fileMenu);                // add File submenu (non-functional)

    QMenu* helpMenu = new QMenu(this);
    helpMenu->setTitle(tr("Help"));
    helpMenu->addAction(ui->actionFileBug); // File a bug
    helpMenu->addAction(ui->actionSources); // Source code link
    helpMenu->addSeparator();
    helpMenu->addAction(ui->actionAbout);   // call About page
    menu->addMenu(helpMenu);                // add Help submenu

    menu->addAction(ui->actionExit);        // Exit item

    ui->menuButton->setIconSize(SC_DPI_T(QSize(24, 24), QSize));
    ui->menuButton->setFixedSize(SC_DPI(42), QWIDGETSIZE_MAX);
    ui->menuButton->setMenu(menu);

    ui->stackedWidget->setCurrentAnimation(tStackedWidget::SlideHorizontal);
}

MainWindow::~MainWindow() {
    // upon unload
    delete d;
    delete ui;
}

/***** actions *****/

// exit
void MainWindow::on_actionExit_triggered() {
    QApplication::exit();
}

// help actions
void MainWindow::on_actionSources_triggered() {
    // open source code page
    QDesktopServices::openUrl(QUrl("http://github.com/ZoomTen/theApp"));
}

void MainWindow::on_actionFileBug_triggered() {
    // open issue tracker
    QDesktopServices::openUrl(QUrl("http://github.com/ZoomTen/theApp/issues"));
}

void MainWindow::on_actionAbout_triggered() {
    // open the library-provided about dialog
    tAboutDialog d;
    d.exec();
}

// resize action
void MainWindow::resizeEvent(QResizeEvent *event) {
}

// tabs
void MainWindow::on_averagesButton_toggled(bool checked){
    if(checked){ui->stackedWidget->setCurrentIndex(0);}
}
void MainWindow::on_gradesButton_toggled(bool checked){
    if(checked){ui->stackedWidget->setCurrentIndex(1);}
}
