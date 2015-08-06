/*****************************************************************************
*                                                                            *
*  OpenNI 2.x Alpha                                                          *
*  Copyright (C) 2012 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of OpenNI.                                              *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/
#include <OpenNI.h>
#include "Viewer.h"

#include <string.h>
#include <iostream>
#include <sstream>
#include "configfile.h"
using namespace std;

//#define NELEMS( X ) (sizeof(X)/sizeof(X[0]))

//bool load_txt(string const& configFile);

//string displayMode;
int displayMode;
//string recordMode;
int recordMode;
string numOfFrameToRec;
string numOfColorFrameToSave;

int nNumOfFrameToRec;
int nNumOfColorFrameToSave;

int main(int argc, char** argv)
{
        ConfigFile *pConfigFile=ConfigFile::getInstance();

        //read the config
        if(argc!=2)
        {
               cout<<endl<<"usage: ./simple-viewer-recoder [path of config.txt]"<<endl;
               return 0;
        }

//        if( !load_txt(argv[1]) )
//        {
//            printf("load text config file failed \n");
//            return 0;
//        }
	pConfigFile->load_txt( argv[1],displayMode,recordMode,nNumOfFrameToRec,nNumOfColorFrameToSave);

	//opencv the cam
	openni::Status rc = openni::STATUS_OK;

	openni::Device device;
	openni::VideoStream depth, color;
	const char* deviceURI = openni::ANY_DEVICE;
//	if (argc > 1)
//	{
//		deviceURI = argv[1];
//	}

	//cout<<"URI:"<<deviceURI<<endl;

	rc = openni::OpenNI::initialize();

	printf("After initialization:\n%s\n", openni::OpenNI::getExtendedError());

	rc = device.open(deviceURI);
	if (rc != openni::STATUS_OK)
	{
		printf("SimpleViewer: Device open failed:\n%s\n", openni::OpenNI::getExtendedError());
		openni::OpenNI::shutdown();
		return 1;
	}

	rc = depth.create(device, openni::SENSOR_DEPTH);
	if (rc == openni::STATUS_OK)
	{
		rc = depth.start();
		if (rc != openni::STATUS_OK)
		{
			printf("SimpleViewer: Couldn't start depth stream:\n%s\n", openni::OpenNI::getExtendedError());
			depth.destroy();
		}
	}
	else
	{
		printf("SimpleViewer: Couldn't find depth stream:\n%s\n", openni::OpenNI::getExtendedError());
	}

	rc = color.create(device, openni::SENSOR_COLOR);
	if (rc == openni::STATUS_OK)
	{
		rc = color.start();
		if (rc != openni::STATUS_OK)
		{
			printf("SimpleViewer: Couldn't start color stream:\n%s\n", openni::OpenNI::getExtendedError());
			color.destroy();
		}
	}
	else
	{
		printf("SimpleViewer: Couldn't find color stream:\n%s\n", openni::OpenNI::getExtendedError());
	}

	if (!depth.isValid() || !color.isValid())
	{
		printf("SimpleViewer: No valid streams. Exiting\n");
		openni::OpenNI::shutdown();
		return 2;
	}

	SampleViewer sampleViewer("Simple Viewer", device, depth, color,displayMode);

	rc = sampleViewer.init(argc, argv);
	if (rc != openni::STATUS_OK)
	{
		openni::OpenNI::shutdown();
		return 3;
	}
	//if(recordMode=="autoRec")
	if(recordMode==1)
	{
	  sampleViewer.startRecording(nNumOfFrameToRec,nNumOfColorFrameToSave);
	  cout<<"startRec"<<endl;
	}
	sampleViewer.run();
}

//bool load_txt(string const& configFile) {
//  printf("load text config file.\n");
//  FILE* file = fopen(configFile.c_str(), "r");

//  if (!file || feof(file)) return false;

//  char buf[1024];
//  string line;
////  string recordMode;
////  string numOfFrameToRec;
////  string numOfColorFrameToSave;
//  int posEqualOld;
//  int posEqual;
//  while (fgets(buf, NELEMS(buf), file)) {
//    line = buf;
//    //if (line.length() < 3) continue;

//    if (line[0] == '#') continue;
//    if (line[0] == ';') continue;

//    //remove the /r
////    if(line[line.length()-1]=='\r')
////    {
////        cout<<"sss"<<endl;
////        line=line.substr(0,line.length()-1);
////    }
//    line=line.substr(0,line.length()-1);
//    // only space are allowed to separate variable name and value
//    posEqual = line.find(' ');
//    if (posEqual == -1)
//    {
//        cout<<"wrong config"<<endl;
//        fclose(file);
//        return false;
//    }

//    displayMode = line.substr(0, posEqual);
//    cout<<"modeDis: ["<<displayMode<<"]"<<endl;
//    posEqualOld=posEqual;
//    posEqual = line.find(' ',posEqualOld + 1);
//    if(posEqual==-1)
//    {
////        cout<<"wrong config"<<endl;
////        fclose(file);
////        return false;
//        recordMode=line.substr(posEqualOld+1);
//    }
//    recordMode = line.substr(posEqualOld+1, posEqual-posEqualOld-1);
//    cout<<"modeRec: ["<<recordMode<<"]"<<endl;
//    if(recordMode=="autoRec")
//    {
//        posEqualOld=posEqual;
//        posEqual = line.find(' ',posEqualOld + 1);

//        if(posEqual==-1)
//        {
//            cout<<"wrong config"<<endl;
//            fclose(file);
//            return false;
//        }
//        numOfFrameToRec = line.substr(posEqualOld+1, posEqual-posEqualOld-1);
//        posEqualOld=posEqual;
//        posEqual = line.find(' ',posEqualOld + 1);

//        if(posEqual!=-1)
//        {
//            cout<<"wrong config"<<endl;
//            fclose(file);
//            return false;
//        }
//        numOfColorFrameToSave=line.substr(posEqualOld+1, posEqual-posEqualOld-1);
//        cout<<"numOfFrameToRec: ["<<numOfFrameToRec<<"]"<<endl;
//        cout<<"numOfColorFrameToSave: ["<<numOfColorFrameToSave<<"]"<<endl;
//        stringstream ss;
//        ss<<numOfFrameToRec;
//        ss>>nNumOfFrameToRec;
//        ss.clear();
//        ss<<numOfColorFrameToSave;
//        ss>>nNumOfColorFrameToSave;
//        if(nNumOfFrameToRec<0 || nNumOfColorFrameToSave<0)
//        {
//            cout<<"wrong config"<<endl;
//            fclose(file);
//            return false;
//        }
//        fclose(file);
//        return true;
//    }
//    if(recordMode=="selfRec")
//    {
//        fclose(file);
//        return true;
//    }
//    cout<<"wrong config"<<endl;
//    fclose(file);
//    return false;
//  }
//  fclose(file);
//  return false;
//}

