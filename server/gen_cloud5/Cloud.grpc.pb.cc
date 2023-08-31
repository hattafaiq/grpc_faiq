// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: Cloud.proto

#include "Cloud.pb.h"
#include "Cloud.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace Cloud {

static const char* protokol_1_method_names[] = {
  "/Cloud.protokol_1/initial_data",
};

std::unique_ptr< protokol_1::Stub> protokol_1::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< protokol_1::Stub> stub(new protokol_1::Stub(channel, options));
  return stub;
}

protokol_1::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_initial_data_(protokol_1_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status protokol_1::Stub::initial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::Cloud::pesan_server* response) {
  return ::grpc::internal::BlockingUnaryCall< ::Cloud::pesan_client, ::Cloud::pesan_server, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_initial_data_, context, request, response);
}

void protokol_1::Stub::async::initial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client* request, ::Cloud::pesan_server* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::Cloud::pesan_client, ::Cloud::pesan_server, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_initial_data_, context, request, response, std::move(f));
}

void protokol_1::Stub::async::initial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client* request, ::Cloud::pesan_server* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_initial_data_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::Cloud::pesan_server>* protokol_1::Stub::PrepareAsyncinitial_dataRaw(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::Cloud::pesan_server, ::Cloud::pesan_client, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_initial_data_, context, request);
}

::grpc::ClientAsyncResponseReader< ::Cloud::pesan_server>* protokol_1::Stub::Asyncinitial_dataRaw(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncinitial_dataRaw(context, request, cq);
  result->StartCall();
  return result;
}

protokol_1::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      protokol_1_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< protokol_1::Service, ::Cloud::pesan_client, ::Cloud::pesan_server, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](protokol_1::Service* service,
             ::grpc::ServerContext* ctx,
             const ::Cloud::pesan_client* req,
             ::Cloud::pesan_server* resp) {
               return service->initial_data(ctx, req, resp);
             }, this)));
}

protokol_1::Service::~Service() {
}

::grpc::Status protokol_1::Service::initial_data(::grpc::ServerContext* context, const ::Cloud::pesan_client* request, ::Cloud::pesan_server* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* protokol_2_method_names[] = {
  "/Cloud.protokol_2/kirim_data",
};

std::unique_ptr< protokol_2::Stub> protokol_2::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< protokol_2::Stub> stub(new protokol_2::Stub(channel, options));
  return stub;
}

protokol_2::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_kirim_data_(protokol_2_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status protokol_2::Stub::kirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::Cloud::mes_server* response) {
  return ::grpc::internal::BlockingUnaryCall< ::Cloud::mes_client, ::Cloud::mes_server, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_kirim_data_, context, request, response);
}

void protokol_2::Stub::async::kirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client* request, ::Cloud::mes_server* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::Cloud::mes_client, ::Cloud::mes_server, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_kirim_data_, context, request, response, std::move(f));
}

void protokol_2::Stub::async::kirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client* request, ::Cloud::mes_server* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_kirim_data_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::Cloud::mes_server>* protokol_2::Stub::PrepareAsynckirim_dataRaw(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::Cloud::mes_server, ::Cloud::mes_client, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_kirim_data_, context, request);
}

::grpc::ClientAsyncResponseReader< ::Cloud::mes_server>* protokol_2::Stub::Asynckirim_dataRaw(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynckirim_dataRaw(context, request, cq);
  result->StartCall();
  return result;
}

protokol_2::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      protokol_2_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< protokol_2::Service, ::Cloud::mes_client, ::Cloud::mes_server, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](protokol_2::Service* service,
             ::grpc::ServerContext* ctx,
             const ::Cloud::mes_client* req,
             ::Cloud::mes_server* resp) {
               return service->kirim_data(ctx, req, resp);
             }, this)));
}

protokol_2::Service::~Service() {
}

::grpc::Status protokol_2::Service::kirim_data(::grpc::ServerContext* context, const ::Cloud::mes_client* request, ::Cloud::mes_server* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace Cloud
