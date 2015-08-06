CXX = g++

#PLAT_FORM:= `uname -i`
PLAT_FORM= $(shell uname)-$(shell uname -m)

SRC_DIR= src
SRC_FILE= $(SRC_DIR)/main.cpp \
	  $(SRC_DIR)/Viewer.cpp \
	  $(SRC_DIR)/configfile.cpp
	  
  
ifeq ($(PLAT_FORM), Linux-armv7l)
	OPENNI_INCLUDE= OpenNI-Linux-Arm-2.2/Include
	OPENNI_LIBS:= OpenNI-Linux-Arm-2.2/Redist
	BIN_PATH=arm-bin
endif

ifeq ($(PLAT_FORM), Linux-x86_64)
	OPENNI_INCLUDE= OpenNI2/Include
	OPENNI_LIBS:= OpenNI2/Redist
	BIN_PATH=bin
endif

CXXFLAGS+=  -I $(OPENNI_INCLUDE) -I/usr/include/opencv
LDFLAGS+= -L $(OPENNI_LIBS)
LDFLAGS+= -lglut -lGL -lopencv_core -lopencv_highgui -lopencv_imgproc -lOpenNI2 
SIMPLE_VIEWER_RECODER= simple-viewer-recoder

all:$(SIMPLE_VIEWER_RECODER) CPU
	
$(SIMPLE_VIEWER_RECODER):  
	$(CXX) $(SRC_FILE) $(CXXFLAGS)  $(LDFLAGS) -o $(BIN_PATH)/$(SIMPLE_VIEWER_RECODER)  -Wl,-rpath ./ #$(OPENNI_LIBS)
	
CPU:
	$(CXX) $(SRC_DIR)/CPU.cpp -o $(BIN_PATH)/CPU	
	


clean:
	@echo "cleanning project"
	rm -rf $(BIN_PATH)/$(SIMPLE_VIEWER_RECODER) $(BIN_PATH)/CPU
	@echo "clean completed"

.PHONY:clean all
