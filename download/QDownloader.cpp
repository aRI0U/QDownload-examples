#include "QDownloader.h"

QDownloader::QDownloader(QObject *parent) : QObject(parent)
{

}


void QDownloader::download(const QUrl url, QFile &file) {
    qDebug() << url << file.fileName();
}

void QDownloader::download(const QUrl url, const QString file) {
    QFile f(file);
    download(url, f);
}
