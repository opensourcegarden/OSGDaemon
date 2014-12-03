TARGET = osgd
CXX = g++
TEST_TARGET = osgdtest

INCLUDES = \
-I/boost/boost
-I/usr/include/boost \
-I/usr/local/include \
-I/usr/include \
-I/usr/include/jsoncpp \
-IOperations \
-IOperations/tests \
-IHardwareAbstraction \
-IHardwareAbstraction/tests \
-ITcpServer \
-ITcpServer/tests \

LDFLAGS = \
-lboost_thread \
-lboost_regex \
-lboost_filesystem \
-lboost_date_time \
-lboost_system \
-lpthread \
-ljsoncpp \

LINKS = \
-L/usr/include \
-L/usr/include/boost \
-L/usr/local/lib \
-L/usr/lib \
-L/usr/include/jsoncpp \

CPPFILES = \
$(wildcard HardwareAbstraction/*.cpp) \
$(wildcard Operations/*.cpp) \
$(wildcard TcpServer/*.cpp) \
$(wildcard Operations/tests/*.cpp) \
$(wildcard HardwareAbstraction/tests/*.cpp) \
$(wildcard TcpServer/tests/*.cpp) \

OBJS = $(CPPFILES:.cpp=.o)



UTILITY = \
-std=c++11 \

TEST_CLASSES = \
Operations/tests/AbstractOperationTests.cpp \
# Operations/tests/ExecutionTreeParserTests.cpp \
# TcpServer/tests/TcpServerTests.cpp \
# Operations/tests/OperationsManagerTests.cpp \
# Operations/tests/DigitalPinOperationTests.cpp  \
# Operations/tests/DigitalReadOperationTests.cpp  \
# Operations/tests/DigitalWriteOperationTests.cpp  \
# Operations/tests/CompositeOperationsTests.cpp \
# HardwareAbstraction/tests/BasicArduinoTests.cpp \

TEST_OBJS = $(TEST_CLASSES:.cpp=.o)

all: $(CPPFILES) $(TARGET)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CXX)  $(OBJS) $(LDFLAGS) $(LINKS)  -lboost_unit_test_framework $(INCLUDES) $(UTILITY) -o $@  

$(TARGET): $(OBJS)
	$(CXX) main.cpp $(LDFLAGS) $(LINKS) $(INCLUDES) $(UTILITY) -o $@
.cpp.o:
	$(CXX) $(LDFLAGS) $(LINKS) $(INCLUDES) $(UTILITY) -c $< -o $@
# build: $(OBJS)

clean: $(OBJS)
	rm -rf $(OBJS)


