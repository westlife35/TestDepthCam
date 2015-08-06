
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include "configfile.h"

#define NELEMS( X ) (sizeof(X)/sizeof(X[0]))



// initialization of static member (this is a must, otherwise link erro occurs)
ConfigFile* ConfigFile::instance_ = 0;

/* toks[i] = null-terminated char* in str, and delimiters in str are replaced
 * with null */
int split_string(char str[], char** toks) {
  int n = 0;
  char delims[] = " \t\n\r";
  toks[n] = strtok(str, delims);
  while (toks[n] != NULL) toks[++n] = strtok(NULL, delims);
  int y = n - 1;
  n = y + 1;
  return n;
}

ConfigFile::ConfigFile() {}

bool ConfigFile::load_txt(string const& configFile,int& displayMode,int& recordMode,int &nNumOfFrameToRec,int &nNumOfColorFrameToSave ) {

  printf("load text config file.\n");
  FILE* file = fopen(configFile.c_str(), "r");

  if (!file || feof(file))
    return false;

  char buf[1024];
  string line;
  string name;
  string val;
  string inSection;
  int posEqual;
  while (fgets(buf, NELEMS(buf), file)) {
    line = buf;
    if (line.length() < 3) continue;

    if (line[0] == '#') continue;
    if (line[0] == ';') continue;

    if (line[0] == '[') {
      inSection = trim(line.substr(1, line.find(']') - 1));
      continue;
    }

    // only space and tab are allowed to separate variable name and value
    posEqual = line.find(' ');
    if (posEqual == -1) posEqual = line.find('\t');

    name = trim(line.substr(0, posEqual));
    val = trim(line.substr(posEqual + 1));
    stringstream ss;
    int nVal;
    ss<<val;
    ss>>nVal;

    string key = inSection + '/' + name;
    add_entry(key, nVal);
  }
  fclose(file);

  //
  for (std::map<string, int>::const_iterator it = content_.begin();
         it != content_.end(); it++) {
      //std::cout <<"["<< (string)it->first << " " <<it->second <<"]"<<std::endl;
//      switch((string)it->first)
//      {
//        case "dispay/display_mode":
//          displayMode=it->second;
//          break;
//        case "record/record_mode":
//          recordMode=it->second;
//          break;
//        case "record/record_frame":
//          nNumOfFrameToRec=it->second;
//          break;
//        case "record/enable_preview_record_image":
//          nNumOfColorFrameToSave=it->second;
//          break;
//      }
      if((string)it->first=="dispay/display_mode")
      {
          displayMode=it->second;
          continue;
      }
      if((string)it->first=="record/record_mode")
      {
          recordMode=it->second;
          continue;
      }
      if((string)it->first=="record/record_frame")
      {
          nNumOfFrameToRec=it->second;
          continue;
      }
      if((string)it->first=="record/enable_preview_record_image")
      {
          nNumOfColorFrameToSave=it->second;
          continue;
      }
  }


  return true;
}



void ConfigFile::add_entry(string key, int value) {
  content_[key] = value;
}

string ConfigFile::trim(string const& source, char const* delims) {
  string result(source);
  string::size_type index = result.find_last_not_of(delims);
  if (index != string::npos) result.erase(++index);

  index = result.find_first_not_of(delims);
  if (index != string::npos)
    result.erase(0, index);
  else
    result.erase();
  return result;
}
