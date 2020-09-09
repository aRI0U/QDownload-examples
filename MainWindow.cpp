#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_downloader(new QDownloader(this)),
      m_urlEdit(new QLineEdit(this)),
      m_fileEdit(new QLineEdit(this)),
      m_progressBar(new QProgressBar(this)),
      m_downloadStatus(new QLabel(this))
{
    QGridLayout *layout = new QGridLayout;

    layout->addWidget(new QLabel("Target URL:"), 0, 0, Qt::AlignRight);
    m_urlEdit->setMinimumWidth(300);
    layout->addWidget(m_urlEdit, 0, 1, Qt::AlignLeft);

    layout->addWidget(new QLabel("Target file:"), 1, 0, Qt::AlignRight);
    m_fileEdit->setMinimumWidth(300);
    layout->addWidget(m_fileEdit, 1, 1, Qt::AlignLeft);

    QPushButton *button = new QPushButton("&Download");
    layout->addWidget(button, 2, 0, 1, 2, Qt::AlignCenter);

    m_progressBar->setRange(0, 1);
    layout->addWidget(m_progressBar, 3, 0, 1, 2, Qt::AlignCenter);

    layout->addWidget(new QLabel("Download status:"), 4, 0, Qt::AlignRight);
    layout->addWidget(m_downloadStatus, 4, 1, Qt::AlignLeft);

    QWidget *mainWidget = new QWidget(this);
    mainWidget->setLayout(layout);

    setCentralWidget(mainWidget);

    connect(button, &QPushButton::clicked,
            this, &MainWindow::download);

    connect(m_downloader, &QDownloader::downloadProgress,
            this, &MainWindow::displayProgress);

    connect(m_downloader, &QDownloader::downloadTerminated,
            this, &MainWindow::displayDownloadStatus);
}

MainWindow::~MainWindow() {}


void MainWindow::download() {
    m_downloader->download(m_urlEdit->text(), m_fileEdit->text());
}


void MainWindow::displayProgress(qint64 bytesReceived, qint64 bytesTotal) {
    m_progressBar->setMaximum(bytesTotal > 0 ? bytesTotal : 0);
    m_progressBar->setValue(bytesReceived);
}

void MainWindow::displayDownloadStatus(QDownload *download) {
    m_downloadStatus->setText(download->error());
}
