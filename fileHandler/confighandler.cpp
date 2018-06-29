#include "3rd-party/json.hpp"
#include "confighandler.h"
#include "backend/token.h"
#include "3rd-party/aes256.h"
#include <map>
#include <QDir>

using json = nlohmann::json;

configHandler::configHandler():configs(json({}))
{
  readFromFile();
}

QString configHandler::getPassword(const QString uname) const
{
  auto it = configs["user"].find(uname.toStdString());
  if(it!= configs["user"].end())
    {
      std::string str = it.value();
      return QString(str.c_str());
    }
  else return QString("");
}

QString configHandler::getServerAddr()const
{
  std::string str = configs["server"];
  return QString(str.c_str());
}

void configHandler::setServerAddr(const QString addr)
{
  configs["server"]=addr.toStdString();
}

void configHandler::setPassword(const QString uname,const QString pwd)
{
  configs["user"][uname.toStdString()] = pwd.toStdString();
}

void configHandler::removePassword(const QString uname)
{
  auto it = configs["user"].find(uname.toStdString());
  if(it!=configs["user"].end())
    {
      configs["user"].erase(it);
    }
}

configHandler::~configHandler()
{
  saveConfig();
}
/// Private handlers

void configHandler::readFromFile()
{
  QString path = "./config/conf.dat";
  QFileInfo conf(path);
  if(conf.isFile())
  {
      QFile file(path);
      if (file.open(QIODevice::ReadOnly))
      {
          // read json
          QByteArray buffer = file.read(file.bytesAvailable());
          QString &&key = keyGenerator();
          std::string &&stdkey = key.toStdString();
          // decode
          std::string buf(buffer.begin(),buffer.end());
          std::string &&decoded = sAes256Decrypt(buf,stdkey);
          std::vector<uint8_t> content(decoded.begin(),decoded.end());
          try
          {
            configs = json::from_cbor(content);
          }
          catch(...)
          {
            qDebug() << "Warning. Interpret config failed.";
          }
          // process json
          // type check
          if(configs.find("user")==configs.end() || !configs["user"].is_object())
            {
              configs["user"]={};
            }
          file.close();
        }
      else
        {
          configs["user"]={};
        }
      if(configs.find("server")==configs.end())
        {
          configs["server"]=std::string("");
        }
    }
  else
    {
      configs["user"]={};
      configs["server"]=std::string("");
    }
}

void configHandler::saveConfig()
{
  auto buf = json::to_cbor(configs);
  std::string strbuf(buf.begin(),buf.end());
  // encode
  QString key = keyGenerator();
  std::string &&stdkey = key.toStdString();
  std::string &&ebuf = sAes256Encrypt(strbuf,stdkey);
  QDir dir;
  dir.mkdir("config");
  QString path = "./config/conf.dat";
  QFile file(path);
  if(file.open(QIODevice::WriteOnly))
    {
      file.write(ebuf.data(),ebuf.size());
      file.close();
    }
}

QString configHandler::keyGenerator()
{
  QStorageInfo storage = QStorageInfo::root();
  QString raw = QString::number(storage.blockSize()) + storage.name();
  return token::getMD5(raw);
}
