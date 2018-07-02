#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include <QThread>

// worker thread to load encrypted file, prevent UI blocking

class fileLoader : public QThread
{
  Q_OBJECT
public:
  enum mode{encrypt,decrypt};
private:
  mode currMode;
  QString path;
  QByteArray src;
public:
  fileLoader(QObject *parent = nullptr);
  void setPath(const QString path);
  void setByteArray(const QByteArray &arr);
  void load();
  void run()override;
signals:
  void process(int proc);
  void onFinish(const QByteArray result);
};

#endif // FILELOADER_H
