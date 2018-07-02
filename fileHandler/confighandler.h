#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <QtCore>
#include <QMap>
#include "3rd-party/json.hpp"
/*
 * Copyright: Zhang Xiang, zx1239856@gmail.com
 *
 * class used to handle configs
 *
 * Auto remember server address used last time
 * and store user passwords if remember pwd is checked
 */

class configHandler
{
public:
  configHandler();
  QString getPassword(const QString uname)const;
  QString getServerAddr()const;
  void setServerAddr(const QString addr);
  void setPassword(const QString uname,const QString pwd);
  void removePassword(const QString uname);
  ~configHandler();
private:
  nlohmann::json configs;
  void readFromFile();
  void saveConfig();
};

#endif // CONFIGHANDLER_H
