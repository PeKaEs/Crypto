#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "FileEnc.hpp"
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

void showUsage(char *entry){
cout << "Usage: " << entry << " [-m] ENC_MODE [-c] KEYSTORE_FILE_PATH [-p] KEYSTORE_PASSWORD [-k] KEY_IDENTIFIER [-f] PATH_TO_FILE [-s] special_mode (optional) {dec, eo, ch}" << endl;
}

bool areEveryArgsSpecified(string encMode,string keystorePath,string keyIdentifier,string filePath, string keyStorePass){
  if (encMode == "" || keystorePath == "" || keyIdentifier == "" || filePath == "" || keyStorePass == "")
    return false;
  return true;
}

int main(int argc, char *argv[])
{
    string encMode, keystorePath, keyIdentifier, specMode, filePath, keyStorePass;
    encMode= keystorePath= keyIdentifier= specMode= filePath= keyStorePass="";

    FileEnc encEngine;

    for (int i = 1; i < argc; i++) {
        if (string("-m") == argv[i]) {
            if (i < argc - 1) {
                encMode = argv[i + 1];
                i++;
            }
        } else if (string("-c") == argv[i]) {
          if (i < argc - 1) {
            keystorePath = argv[i + 1];
            i++;
          }
        } else if (string("-k") == argv[i]) {
          if (i < argc - 1) {
            keyIdentifier = argv[i + 1];
            i++;;
          }
        } else if (string("-s") == argv[i]) {
          if (i < argc - 1) {
            specMode = argv[i + 1];
            i++;
          }
        } else if (string("-f") == argv[i]) {
          if (i < argc - 1) {
            filePath = argv[i + 1];
            i++;
          }
        } else if (string("-p") == argv[i]) {
          if (i < argc - 1) {
            keyStorePass = argv[i + 1];
            i++;
          }
        } else {
            showUsage(argv[0]);
            return 0;
        }
    }
    if (!areEveryArgsSpecified(encMode, keystorePath, keyIdentifier, filePath, keyStorePass)) {
        showUsage(argv[0]);
        return 0;
    }

    encEngine.set_encMode(encMode);
    encEngine.set_keystorePath(keystorePath);
    encEngine.set_keyIdentifier(keyIdentifier);
    encEngine.set_specMode(specMode);
    encEngine.set_filePath(filePath);
    encEngine.set_keyStorePassword(keyStorePass);

    encEngine.debugInfo();

    encEngine.run();

    return 0;
}
