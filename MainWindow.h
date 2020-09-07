#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QLineEdit>

#include "download/QDownloader.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void download();

private slots:
    void displayProgress(qint64 bytesReceived, qint64 bytesTotal);
    void displayDownloadStatus(QDownload *download);

private:
    QDownloader *m_downloader;

    QLineEdit *m_urlEdit;
    QLineEdit *m_fileEdit;
    QProgressBar *m_progressBar;

    QLabel *m_downloadStatus;
};
#endif // MAINWINDOW_H
