default:
	$(MAKE) CC=gcc CXX=g++ \
		CXXFLAGS='$(CXXFLAGS) -Wall -Wextra -pipe -O3 -g -ffast-math -mtune=generic -flto -std=c++14 -DNDEBUG'  \
		LDFLAGS='$(LDFLAGS) -g' \
		leelagui

debug:
	$(MAKE) CC=gcc CXX=g++ \
		CXXFLAGS='$(CXXFLAGS) -Wall -Wextra -pipe -O0 -g -std=c++14' \
		LDFLAGS='$(LDFLAGS) -g' \
		leelagui

macos:
	$(MAKE) CC=gcc CXX=g++ \
		CXXFLAGS='$(CXXFLAGS) -Wall -Wextra -pipe -O3 -g -ffast-math -mtune=generic -flto -std=c++14 -DNDEBUG'  \
		LDFLAGS='$(LDFLAGS) -g' \
		leelagui Leela.app

clang:
	$(MAKE) CC=clang-4.0 CXX=clang++-4.0 \
		CXXFLAGS='$(CXXFLAGS) -Wall -Wextra -O3 -ffast-math -mtune=generic -flto -std=c++14 -DNDEBUG -Wno-inconsistent-missing-override -Wno-unused-parameter' \
		LDFLAGS='$(LDFLAGS) -flto -fuse-linker-plugin' \
		leelagui

#DYNAMIC_LIBS += -lboost_filesystem -lcaffe -lprotobuf -lglog
#LIBS += -lopenblas
#DYNAMIC_LIBS += -lpthread
#DYNAMIC_LIBS += -lOpenCL
LIBS += -framework Accelerate
#LIBS += -framework OpenCL
#DYNAMIC_LIBS += -lmkl_rt

CAFFE_BASE = /usr/local
CAFFE_INC = $(CAFFE_BASE)/include
CAFFE_LIB = $(CAFFE_BASE)/lib
CXXFLAGS += -I$(CAFFE_INC) -I/usr/local/cuda/include
#CXXFLAGS += -I/opt/intel/mkl/include
#CXXFLAGS += -I/opt/OpenBLAS/include
CXXFLAGS += -Iengine
#CXXFLAGS += -I/System/Library/Frameworks/Accelerate.framework/Versions/Current/Headers
LDFLAGS  += -L$(CAFFE_LIB)
CXXFLAGS += -stdlib=libc++
LDFLAGS  += -stdlib=libc++
#LDFLAGS  += -L/opt/intel/mkl/lib/intel64/
#LDFLAGS  += -L/opt/intel/mkl/lib/ia32/
#LDFLAGS += -L/opt/OpenBLAS/lib
WX_HOME = ~/git/wxWidgets/mac-build

CXXFLAGS += -I.
CPPFLAGS += -MD -MP

sources = engine/Network.cpp engine/AttribScores.cpp engine/FullBoard.cpp engine/KoState.cpp engine/Playout.cpp \
	  engine/TimeControl.cpp engine/UCTSearch.cpp engine/Attributes.cpp engine/Book.cpp \
	  engine/GameState.cpp engine/PNNode.cpp engine/SGFParser.cpp engine/Timing.cpp \
	  engine/Utils.cpp engine/FastBoard.cpp engine/Matcher.cpp engine/PNSearch.cpp \
	  engine/SGFTree.cpp engine/TTable.cpp engine/Zobrist.cpp engine/FastState.cpp engine/GTP.cpp \
	  engine/MCOTable.cpp engine/Random.cpp engine/SMP.cpp engine/UCTNode.cpp engine/NN.cpp \
	  engine/NN128.cpp engine/NNValue.cpp engine/OpenCL.cpp engine/MCPolicy.cpp \
	  AboutDialog.cpp AnalysisWindow.cpp App.cpp CalculateDialog.cpp ClockAdjustDialog.cpp \
	  EngineThread.cpp GUI.cpp MainFrame.cpp NewGameDialog.cpp RatedSizeDialog.cpp \
	  ScoreDialog.cpp ScoreHistogram.cpp SettingsDialog.cpp TBoardPanel.cpp TScorePanel.cpp

objects = $(sources:.cpp=.o)
deps = $(sources:%.cpp=%.d)

-include $(deps)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) `$(WX_HOME)/wx-config --cxxflags` -c -o $@ $<

leelagui: $(objects)
#	$(CXX) $(LDFLAGS) -o $@ $^ -static-libgcc -static-libstdc++ -Wl,-Bstatic $(LIBS) -Wl,-Bdynamic $(DYNAMIC_LIBS) `wx-config --libs --static=yes`
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS) $(DYNAMIC_LIBS) `$(WX_HOME)/wx-config --libs --static=yes`

Leela.app: Info.plist leelagui img/leela.icns
	SetFile -t APPL leelagui
	-mkdir Leela.app
	-mkdir Leela.app/Contents
	-mkdir Leela.app/Contents/MacOS
	-mkdir Leela.app/Contents/Resources
	-mkdir Leela.app/Contents/Resources/English.lproj
	cp Info.plist Leela.app/Contents/
	echo -n 'APPL????' > Leela.app/Contents/PkgInfo
	cp leelagui Leela.app/Contents/MacOS/Leela
	cp img/leela.icns Leela.app/Contents/Resources/

clean:
	-$(RM) leelagui $(objects) $(deps)

.PHONY: clean default debug clang
