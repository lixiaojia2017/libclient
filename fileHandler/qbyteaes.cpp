#include "qbyteaes.h"
#include <QStorageInfo>
#include "backend/token.h"
#include "3rd-party/aes256.h"

QByteAes::QByteAes(const std::string k):key(k)
{

}

// static memeber functions

std::vector<uint8_t> QByteAes::Encrypt(std::vector<uint8_t>& src, std::vector<uint8_t>& key)
{
  std::string &&_src = std::string(src.begin(),src.end());
  std::string &&_key = std::string(key.begin(),key.end());
  std::string &&res = sAes256Encrypt(_src,_key);
  return std::vector<uint8_t>(res.begin(),res.end());
}

std::vector<uint8_t> QByteAes::Decrypt(std::vector<unsigned char> &src,std::vector<unsigned char> &key)
{
  std::string &&_src = std::string(src.begin(),src.end());
  std::string &&_key = std::string(key.begin(),key.end());
  std::string &&res = sAes256Decrypt(_src,_key);
  return std::vector<uint8_t>(res.begin(),res.end());
}

std::string QByteAes::Encrypt(std::string& src, std::string &key)
{
  return sAes256Encrypt(src,key);
}

std::string QByteAes::Decrypt(std::string &src, std::string &key)
{
  return sAes256Decrypt(src,key);
}

std::string QByteAes::KeyGen()
{
  QStorageInfo storage = QStorageInfo::root();
  QString raw = QString::number(storage.blockSize()) + storage.name();
  return token::getMD5(raw).toStdString();
}

// non-static memeber functions

std::vector<uint8_t> QByteAes::Encrypt(std::vector<uint8_t>& src)
{
  if(key.empty())key=KeyGen();
  auto &&_key = std::vector<uint8_t>(key.begin(),key.end());
  return Encrypt(src,_key);
}

std::vector<uint8_t> QByteAes::Decrypt(std::vector<uint8_t> &src)
{
  if(key.empty())key=KeyGen();
  auto &&_key = std::vector<uint8_t>(key.begin(),key.end());
  return Decrypt(src,_key);
}

std::string QByteAes::Encrypt(std::string &src)
{
  if(key.empty())key=KeyGen();
  return Encrypt(src,key);
}

std::string QByteAes::Decrypt(std::string &src)
{
  if(key.empty())key=KeyGen();
  return Decrypt(src,key);
}

void QByteAes::setKey(std::string &k)
{
  key = k;
}

