#ifndef QBYTEAES_H
#define QBYTEAES_H
#include <vector>
#include <string>

class QByteAes
{
  std::string key;
public:
  QByteAes(const std::string key="");
  std::vector<uint8_t> Encrypt(std::vector<uint8_t>& src);
  std::vector<uint8_t> Decrypt(std::vector<uint8_t>& src);
  std::string Encrypt(std::string& src);
  std::string Decrypt(std::string& src);
  void setKey(std::string &key);
  static std::vector<uint8_t> Encrypt(std::vector<uint8_t>& src, std::vector<uint8_t>& key);
  static std::vector<uint8_t> Decrypt(std::vector<uint8_t>& src, std::vector<uint8_t>& key);
  static std::string Encrypt(std::string& src, std::string& key);
  static std::string Decrypt(std::string& src, std::string& key);
  // key generator, using HW information
  static std::string KeyGen();
};

#endif // QBYTEAES_H
