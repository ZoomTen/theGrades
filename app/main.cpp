#define APP_VERSION "0.01"

// UI includes
#include "mainwindow.h"

// Qt includes
#include <QDir>
#include <QStandardPaths>

// the-libs includes
#include <tsettings.h>
#include <tapplication.h>

// settings
#include <tsettings.h>


int main(int argc, char* argv[]) {
    tApplication a(argc, argv);

    // application name
#ifdef T_BLUEPRINT_BUILD
    a.setApplicationName("theGrades-Blueprint");
    a.setDesktopFileName("com.zumid.theGrades");
#else
    a.setApplicationName("theGrades");
    a.setDesktopFileName("com.zumid.theGrades");
#endif

    // version
    a.setApplicationVersion("0.01");

    // app icons
    a.setApplicationIcon(QIcon::fromTheme("theGrades", QIcon(":/icons/theGrades.svg")));

    // splash screen graphic
    a.setAboutDialogSplashGraphic(a.aboutDialogSplashGraphicFromSvg(":/icons/theGrades-aboutside.svg"));

    // generic name
    a.setGenericName(QApplication::tr("Grade logging application"));

    // license
    a.setApplicationLicense(tApplication::Gpl3OrLater);

    // copyright
    a.setCopyrightHolder("Zumi Daxuya");
    a.setCopyrightYear("2020");

    // suite name
    a.setOrganizationName("theSuite Contrib");

    // set share path
    QString sharePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (QDir(sharePath).exists()) {
        a.setShareDir(sharePath); // use local share dir.
    } else {
        a.setShareDir("/usr/share/theGrades/"); // use global system dir (LINUX)
    }

    // set defaults file
    QString defaultsPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    defaultsPath += "/defaults.conf";
    tSettings::registerDefaults(defaultsPath);   // use local config dir
    tSettings::registerDefaults("/etc/theGrades/defaults.conf"); // use global conifg dir (LINUX)

    // setup i18n
    a.installTranslators();

    // run app
    MainWindow w;
    w.show();

    return a.exec();
}
