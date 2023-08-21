QT += gui \
      core\
      sql \

CONFIG += c++11 c++14 c++17 console
CONFIG -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#CONFIG += sanitizer sanitize_address
#QMAKE_CXXFLAGS+= -fsanitize=address -fno-omit-frame-pointer -g3 -Wno-deprecated-copy
#QMAKE_CFLAGS+= -fsanitize=address -static-libasan -fno-omit-frame-pointer
#QMAKE_LFLAGS+= -fsanitize=address -static-libasan

HEADERS +=  \
           # helloworld.grpc.pb.h \
           # helloworld.pb.h \
           gen_cloud2/Cloud.grpc.pb.h \
           gen_cloud2/Cloud.pb.h \
            tampil.h \
            treesubwin.h \
            strc.h
           # coba_lagi.h
          

SOURCES +=  \#coba_lagi.cpp \
            tampil.cpp \
            treesubwin.cpp \
            gen_cloud2/Cloud.grpc.pb.cc \
            gen_cloud2/Cloud.pb.cc \
            #helloworld.grpc.pb.cc \
            #helloworld.pb.cc \
            main.cpp

FORMS += \
    tampil.ui

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
