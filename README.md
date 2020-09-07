# QDownload: File downloader for QT applications

This project provides an implementation of a so-called **QDownloader**, which enables to download data from remote servers.



## Installation

1. Add `network` at the beginning of your `.pro` file:

   ```
   QT += network
   ```

2. Copy-paste the content of the `./download` directory in your project

3. Include `QDownloader` in the header of files in which you want to download files:

   ```c++
   #include "path/to/download/QDownloader.h"
   ```

   

If you want to be more familiar with QDownload before adding it to your own project, this project contains a minimal example that illustrates the way a `QDownloader` can be used to download files.

*This project has been tested with Qt 5.12.8 on a Linux machine. It should work with newer versions of Qt and on Windows or Mac OS machines but might not work with older versions of Qt.*



## Usage

Retrieving a file from the Web is pretty straightforward. In order to download the content of `targetUrl` and write it in a file named `targetFile`, you have to do the following:

```c++
QDownloader *downloader = new QDownloader(this);
downloader->download(targetUrl, targetFile);
```

A single `QDownloader` can perform multiple downloads: you don't have to instantiate a new `QDownloader` each time you want to download a new file.

The downloading operation is run asynchronously. A `downloadTerminated` signal is sent by the `QDownloader` object when the download is complete. Therefore, **YOU MUST AVOID** structures like this:

```c++
QDownloader *downloader(this);
QFile targetFile(fileName);
downloader->download(targetUrl, targetFile);

targetFile.open();
// do stuff with retrieved file
```

In fact, calling `downloader->download` only send the download request. Then, if you try to perform operations on `targetFile` just after sending the download request, the content of the file won't be the expected content since the download operation is not over.

The right way to perform operations on the downloaded files is to use signals and slots:

```c++
QDownloader *downloader(this);
connect(downloader, &QDownloader::downloadTerminated,
        this, &MyClass::mySlot);

QFile targetFile(fileName);
downloader->download(targetUrl, targetFile);

...
    
void mySlot(QDownload *download) {
    if (download->success()) {
        QFile targetFile(download->targetFile());
        targetFile.open();
        // do stuff with retrieved file
    }
    else {
        qDebug() << download->error();  // print the error as a human-readable string
    }
    delete download;
}
```

This asynchronous behavior enables the application not to be "blocked" while you are downloading large files for example.



## More details about QDownload objects

The `QDownload` class aims at storing all relevant information about a downloading operation (url, target file, eventual error, download progress, etc.) A new `QDownload` object is created each time `QDownloader::download` is called and each `QDownloader` signal return the corresponding `QDownload` object as argument, which enables to easily retrieve information about a download after it is finished.

Information about a download can be retrieved with the following functions:

- `targetUrl()` returns the target URL of the download.
- `targetFile()` returns the target file of the download.
- `error()` returns the error encountered during the download as a human-readable string. If no error occurred, it equals `"No error"`.
- `success()` indicates whether the downloading operation has been successful or not.

`QDownload` objects are supposed to be accessed only in slots connected with `QDownloader` signals. Therefore only those read-only methods should be directly called. In particular, `QDownload` signals are automatically connected to `QDownloader` ones, and you thus should never directly connect `QDownload` signals to your own slots. Only connect `QDownloader` signals to your own slots.





Please don't hesitate to raise issues if you encounters some errors or if you have any question about QDownload.

