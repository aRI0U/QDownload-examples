#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_downloader(new QDownloader(this)),
      m_urlEdit(new QLineEdit(this)),
      m_fileEdit(new QLineEdit(this))
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

    QWidget *mainWidget = new QWidget(this);
    mainWidget->setLayout(layout);

    setCentralWidget(mainWidget);

    connect(button, SIGNAL(clicked()),
            this, SLOT(download()));
}

MainWindow::~MainWindow() {}


void MainWindow::download() {
    m_downloader->download(m_urlEdit->text(), m_fileEdit->text());
}

