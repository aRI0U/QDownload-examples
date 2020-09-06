#ifndef QDOWNLOADER_H
#define QDOWNLOADER_H

#include <QDebug>
#include <QFile>
#include <QUrl>

class QDownloader : public QObject
{
    Q_OBJECT
public:
    explicit QDownloader(QObject *parent = nullptr);

public slots:
    void download(const QUrl url, QFile &file);
    void download(const QUrl url, const QString file);

signals:

};

#endif // QDOWNLOADER_H
