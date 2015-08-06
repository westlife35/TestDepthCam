// Parse and modify *.ini files
#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <map>
#include <string.h>
using namespace std;

int split_string(char str[], char** toks);

class ConfigFile {

public:
  std::map<string,int> content_;

public:
  static ConfigFile* getInstance() {
    if (!instance_) instance_ = new ConfigFile;
    return instance_;
  }
  bool load_txt(string const& configFile,int& displayMode,int& recordMode,int &nNumOfFrameToRec,int &nNumOfColorFrameToSave );

private:
  ConfigFile();

  static ConfigFile* instance_;

 protected:
  string trim(string const& source, char const* delims = " \t\r\n");
  void add_entry(string key, int value);
};

#endif
