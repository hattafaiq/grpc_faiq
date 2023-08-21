QT -= gui
QT += core\
      sql

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
HEADERS +=  \
    ambil_data.h \
    data_proses.h \
        gen_cloud2/Cloud.grpc.pb.h \
        gen_cloud2/Cloud.pb.h \
    strk.h

SOURCES += \
        ambil_data.cpp \
        data_proses.cpp \
        gen_cloud2/Cloud.grpc.pb.cc \
        gen_cloud2/Cloud.pb.cc \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../../../../../../kantor/grpc/cmake/build/ -lgrpcpp_channelz -lgrpc++_reflection -lgrpc++_alts \
-lgrpc++_error_details -lgrpc++ -lgrpc_csharp_ext -lgrpc -lgrpc++_unsecure -lgrpc_unsecure -lgrpc_plugin_support -lgpr \
-lupb -laddress_sorting
INCLUDEPATH += $$PWD/../../../../../../kantor/grpc/include/grpcpp
DEPENDPATH += $$PWD/../../../../../../kantor/grpc/include/grpcpp

unix:!macx: LIBS += -L$$PWD/../../../../../../kantor/grpc/cmake/build/third_party/protobuf/ -lprotoc -lprotobuf -lprotobuf-lite
INCLUDEPATH += $$PWD/../../../../../../kantor/grpc/third_party/protobuf/src/google/protobuf
DEPENDPATH += $$PWD/../../../../../../kantor/grpc/third_party/protobuf/src/google/protobuf
