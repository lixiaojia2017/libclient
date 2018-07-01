#include "fileloader.h"
#include "fileHandler/qbyteaes.h"
#include "3rd-party/aes256.h"
#include <QFile>

const int BATCH = 512*1024;
const int BLOCK = 16;
const int supplement = 3;

fileLoader::fileLoader(QObject *parent):QThread(parent)
{
  currMode = decrypt;
}

void fileLoader::setPath(const QString p)
{
  path = p;
}

void fileLoader::setByteArray(const QByteArray &arr)
{
  src =arr;
  currMode = encrypt;
}

void fileLoader::load()
{
  if(path.isEmpty())
    return;
  else
    this->start();
}

void fileLoader::run()
{
  QFile file(path);
  if(currMode==decrypt)
    {
      if(file.open(QIODevice::ReadOnly))
        {
          src = file.readAll();
        }
      else return;
      file.close();
      std::string &&sInput = src.toStdString();
      std::string sResult;
      std::string &&sKey = QByteAes::KeyGen();
      //partition string (each part of 16 characters)
      int iPartCounter = sInput.size()/BLOCK;
      char** pcInput;

      pcInput = new char *[iPartCounter];
      for(int i=0;i<iPartCounter;i++){
                  pcInput[i] = new char[BLOCK];
      }

          //copying to array (all blocks)
      for(int i =0;i<iPartCounter;i++){
                  copyStringToChar(sInput, BLOCK, i * BLOCK, pcInput[i]);
      }
          aes256_context ctx;
          aes256_init(&ctx, (unsigned char*)sKey.c_str());
      for(int i=0;i<iPartCounter;i++){
                  //decrypting block
          aes256_decrypt_ecb(&ctx,(unsigned char*)pcInput[i]);
          emit process((i+1)*80/iPartCounter);
                  //append block to string
                  for (int j = 0; j < BLOCK; j++) {
                          sResult += pcInput[i][j];
                  }
      }

          //removing char's arrays
      for(int i=0;i<iPartCounter;i++){
          delete[] pcInput[i];
          emit process(80+(i+1)*20/iPartCounter);
      }
      delete[] pcInput;

      //removing supplements
      bool bEndRemoving=false;
      for(int i = sResult.size()-1;i>=0&&!bEndRemoving;i--){
          if(sResult.at(i)==supplement)
              sResult.erase(i,1);
          else bEndRemoving=true;
      }

      emit onFinish(QByteArray(sResult.data(),sResult.length()));
      return;
    }
  else if(currMode==encrypt)
    {
      if(file.open(QIODevice::WriteOnly))
        {
          std::string buffer(src.begin(),src.end());
          qint64 totalSize = buffer.length();
          qint64 encryptedSize = 0;
          QByteAes aes;
          while(totalSize-encryptedSize)
            {
              std::string sub = buffer.substr(encryptedSize,BATCH);
              std::string &&resBuffer=aes.Encrypt(sub);
              encryptedSize+=sub.length();
              file.write(resBuffer.data(),resBuffer.size());
              int proc = encryptedSize*100/totalSize;
              emit process(proc>100?100:proc);
            }
          file.close();
          return;
        }
      else return;
    }
}
