#ifndef QDOWNLOADER_H
#define QDOWNLOADER_H

#include <QDebug>
#include <QFile>
#include <QUrl>

#include "QDownload.h"

class QDownloader : public QObject
{
    Q_OBJECT
    typedef QList<QDownload *> QDownloadList;

public:
    explicit QDownloader(QObject *parent = nullptr);

public slots:
    void download(const QUrl url, const QFile &file);
    void download(const QUrl url, const QString file);

signals:
    void downloadTerminated(QDownload *download);

private slots:
    void terminateDownload(QDownload *download);

private:
    QDownload *newTask(const QUrl &url, const QFile &file);

    QDownloadList m_tasksList;
};

#endif // QDOWNLOADER_H
