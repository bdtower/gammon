#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include "board.h"

int main(int argc, char *argv[])
{
    Board board;

    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/gammon/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
