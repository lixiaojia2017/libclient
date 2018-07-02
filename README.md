# libclient
The cross-platform client side application of [**libserver**](https://github.com/zx1239856/libserver), offering ease-to-use and user-friendly interface.

Tested on Ubuntu and Windows 10

## 2018 Spring

**O**bject-**O**riented **P**rogramming Project

See [contributors](https://github.com/lixiaojia2017/libclient/graphs/contributors) here

## How to build

This application requires Qt 5.8 or higher to build. Presumably you are using a GUI operating system for this application, so you must have installed Qt Creator. In this case, open the *.pro project file and build it using Qt Creator.

If you prefer to build with command line, you can go as follows:

```bash
qmake && make
```

## Usage

This is a GUI application, just launch it after build! Do not tell me you can't use it.

## Third-party libraries or projects involved

[AES256 encryption and decryption](https://github.com/jacekc3/AES256) A simple library used for crypto

[nlohmann json](https://github.com/nlohmann/json) STL-like JSON library

[Qt-PDFViewer](https://github.com/zx1239856/Qt-pdfViewer) Modified Wrapper for pdf.js, supporting bookmark function

