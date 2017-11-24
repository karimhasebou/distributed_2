cmake_minimum_required(VERSION 2.8)

project (distributed_2)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRECT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_FILE “/usr/local/Cellar/qt/5.9.1/lib/cmake/Qt5Widgets”)

set(NAME_SRC ApplicationStart.cpp 
Marshalling/MarshallingManager.cpp 
Marshalling/MarshalledMessage.cpp 
MySocket.cpp 
Message.cpp 
UDPSocket.cpp 
CustomObjects/CustomInt.cpp 
CustomObjects/CustomBool.cpp 
CustomObjects/CustomString.cpp
CustomObjects/CustomVector.cpp
Pages/LoginPage.cpp
Pages/HomePage.cpp)

set (NAME_HEADERS Marshalling/MarshallingManager.h 
Marshalling/MarshalledMessage.h 
MySocket.h
Message.h 
UDPSocket.h 
CustomObjects/CustomInt.h 
CustomObjects/CustomBool.h 
CustomObjects/CustomString.h
CustomObjects/CustomVector.h
Pages/LoginPage.h
Pages/HomePage.h)

qt5_wrap_ui(UI_HEADRES Forms/HomePage.ui Forms/LoginPage.ui)

add_executable(distributed_2 ${NAME_SRC} ${NAME_HEADERS} ${UI_HEAADERS})

target_link_libraries(distributed_2 Qt5::Core Qt5::Gui Qt5::Widgets)