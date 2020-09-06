#include "QDownloader.h"

QDownloader::QDownloader(QObject *parent) : QObject(parent)
{

}


void QDownloader::download(const QUrl url, const QFile &file) {
    QDownload *dl = newTask(url, file);

    connect(dl, &QDownload::finished,
            this, &QDownloader::terminateDownload);

    dl->get();
}

void QDownloader::download(const QUrl url, const QString file) {
    QFile f(file);
    download(url, f);
}


void QDownloader::terminateDownload(QDownload *download) {
    m_tasksList.removeOne(download);
    emit downloadTerminated(download);
}


QDownload *QDownloader::newTask(const QUrl &url, const QFile &file) {
    QDownload *dl = new QDownload(url, file, this);
    m_tasksList.append(dl);
    return dl;
}