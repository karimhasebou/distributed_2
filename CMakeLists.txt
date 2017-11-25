cmake_minimum_required(VERSION 2.8)

project (distributed_2)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRECT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_FILE "/usr/local/Cellar/qt/5.9.1/lib/cmake/Qt5Widgets")

list(APPEND CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(MAR_SRC 
Marshalling/MarshallingManager.cpp 
Marshalling/MarshalledMessage.cpp)

set(UDP_SRC 
UDPLayer/MySocket.cpp
UDPLayer/UDPSocket.cpp
UDPLayer/Message.cpp)

set(RPC_AUTH_SRC
RPC/RpcCallsAuthServer.cpp
RPC/RpcStubAuthServer.cpp)

set(RPC_SRV_SRC
RPC/RPC.cpp
RPC/RpcCallsClient.cpp
RPC/RpcCallsServer.cpp
RPC/RpcStubServer.cpp)

set(PAG_SRC 
Pages/LoginPage.cpp
Pages/HomePage.cpp)

set(CUST_SRC 
CustomObjects/CustomInt.cpp 
CustomObjects/CustomBool.cpp 
CustomObjects/CustomString.cpp
CustomObjects/CustomVector.cpp)

set(DB_SRC Database/DatabaseHandler.cpp)

set(MAR_HDR 
Marshalling/MarshallingManager.h 
Marshalling/MarshalledMessage.h)

set(UDP_HDR 
UDPLayer/MySocket.h
UDPLayer/UDPSocket.h
UDPLayer/Message.h)

set(RPC_HDR
RPC/RPC.h
RPC/RpcCalls.h
RPC/RpcStub.h)

set(PAG_HDR
Pages/LoginPage.h
Pages/HomePage.h)

set(CUST_HDR 
CustomObjects/CustomInt.h 
CustomObjects/CustomBool.h 
CustomObjects/CustomString.h
CustomObjects/CustomVector.h)

set(DB_HDR Database/DatabaseHandler.h)

set(ALL_SRC ${MAR_SRC} ${UDP_SRC} ${CUST_SRC})

set(ALL_HDR ${MAR_HDR} ${UDP_HDR} ${RPC_HDR} ${CUST_HDR})

qt5_wrap_ui(UI_HEADRES Pages/HomePage.ui Pages/LoginPage.ui)

add_executable(application 
ApplicationStart.cpp
RequestHandler.cpp
${ALL_SRC}
${PAG_SRC} 
${RPC_SRV_SRC}
RequestHandler.h
${ALL_HDR} 
${PAG_HDR} 
${UI_HEAADERS})

target_link_libraries(application Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(centralserver 
AuthenticationServer.cpp
${DB_SRC}
${RPC_AUTH_SRC}
RequestHandler.cpp
${ALL_SRC}
${DB_HDR}
RequestHandler.h
${ALL_HDR})

source_group(Marshalling FILES ${MAR_SRC} ${MAR_HDR})
source_group(UDPLayer FILES ${UDP_SRC} ${UDP_HDR})
source_group(RPC FILES ${RPC_AUTH_SRC} ${RPC_SRV_SRC} ${RPC_HDR})
source_group(Pages FILES ${PAG_SRC} ${PAG_HDR})
source_group(CustomObjects FILES ${CUST_SRC} ${CUST_HDR})
source_group(Database FILES ${DB_SRC} ${DB_HDR})

