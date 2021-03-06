// window
#include "mainwindow.h"
#include "ui_mainWindow.h"

#include "options/optionswindow.h"

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

    if (tCsdGlobal::windowControlsEdge() == tCsdGlobal::Left) {
       ui->leftCsdLayout->addWidget(csd_widget);
    } else {
        ui->rightCsdLayout->addWidget(csd_widget);
    }

    // icon menu
    QMenu* menu = new QMenu(this);

    menu->addAction(ui->actionOption);  // Options

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

    connect(ui->grades, SIGNAL(updateAverages()),
            ui->averages,    SLOT(updateAverages())); // shoddily link the grades and averages windows
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

// options
void MainWindow::on_actionOption_triggered() {
    Options* optionwindow = new Options();
    connect(optionwindow,    SIGNAL(settingsChanged()),
            ui->averages,    SLOT(updateAverages())); // update averages on settings change
    connect(optionwindow,    SIGNAL(settingsChanged()),
            ui->grades,    SLOT(updateListing())); // update grades on settings change
    optionwindow->show();
}

// help actions
void MainWindow::on_actionSources_triggered() {
    // open source code page
    QDesktopServices::openUrl(QUrl("http://github.com/ZoomTen/theGrades"));
}

void MainWindow::on_actionFileBug_triggered() {
    // open issue tracker
    QDesktopServices::openUrl(QUrl("http://github.com/ZoomTen/theGrades/issues"));
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
