#ifndef QDOWNLOAD_H
#define QDOWNLOAD_H

#include <QFile>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

class QDownload : public QObject
{
    Q_OBJECT

public:
    explicit QDownload(QObject *parent = nullptr);
    explicit QDownload(const QUrl &url, const QFile &file, QObject *parent = nullptr);


    QUrl targetUrl() const;
    QFile targetFile() const;
    QString error() const;

    void setTargetUrl(const QUrl &url);
    void setTargetFile(const QFile &file);


    void get() const;

signals:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal, QDownload *download);
    void finished(QDownload *download);

private slots:
    void sendDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void finishDownload(QNetworkReply *reply);

private:
    void writeDownloadedData(const QByteArray data);

    QNetworkAccessManager *m_manager;
    QString m_error;

    QFile m_targetFile;
    QUrl m_targetUrl;
};

#endif // QDOWNLOAD_H
