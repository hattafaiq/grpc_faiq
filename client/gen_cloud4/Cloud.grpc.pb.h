// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: Cloud.proto
#ifndef GRPC_Cloud_2eproto__INCLUDED
#define GRPC_Cloud_2eproto__INCLUDED

#include "Cloud.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace Cloud {

class protokol_1 final {
 public:
  static constexpr char const* service_full_name() {
    return "Cloud.protokol_1";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status initial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::Cloud::pesan_server* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Cloud::pesan_server>> Asyncinitial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Cloud::pesan_server>>(Asyncinitial_dataRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Cloud::pesan_server>> PrepareAsyncinitial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Cloud::pesan_server>>(PrepareAsyncinitial_dataRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void initial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client* request, ::Cloud::pesan_server* response, std::function<void(::grpc::Status)>) = 0;
      virtual void initial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client* request, ::Cloud::pesan_server* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Cloud::pesan_server>* Asyncinitial_dataRaw(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Cloud::pesan_server>* PrepareAsyncinitial_dataRaw(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status initial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::Cloud::pesan_server* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Cloud::pesan_server>> Asyncinitial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Cloud::pesan_server>>(Asyncinitial_dataRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Cloud::pesan_server>> PrepareAsyncinitial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Cloud::pesan_server>>(PrepareAsyncinitial_dataRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void initial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client* request, ::Cloud::pesan_server* response, std::function<void(::grpc::Status)>) override;
      void initial_data(::grpc::ClientContext* context, const ::Cloud::pesan_client* request, ::Cloud::pesan_server* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::Cloud::pesan_server>* Asyncinitial_dataRaw(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::Cloud::pesan_server>* PrepareAsyncinitial_dataRaw(::grpc::ClientContext* context, const ::Cloud::pesan_client& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_initial_data_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status initial_data(::grpc::ServerContext* context, const ::Cloud::pesan_client* request, ::Cloud::pesan_server* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_initial_data : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_initial_data() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_initial_data() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status initial_data(::grpc::ServerContext* /*context*/, const ::Cloud::pesan_client* /*request*/, ::Cloud::pesan_server* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestinitial_data(::grpc::ServerContext* context, ::Cloud::pesan_client* request, ::grpc::ServerAsyncResponseWriter< ::Cloud::pesan_server>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_initial_data<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_initial_data : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_initial_data() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::Cloud::pesan_client, ::Cloud::pesan_server>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::Cloud::pesan_client* request, ::Cloud::pesan_server* response) { return this->initial_data(context, request, response); }));}
    void SetMessageAllocatorFor_initial_data(
        ::grpc::MessageAllocator< ::Cloud::pesan_client, ::Cloud::pesan_server>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::Cloud::pesan_client, ::Cloud::pesan_server>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_initial_data() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status initial_data(::grpc::ServerContext* /*context*/, const ::Cloud::pesan_client* /*request*/, ::Cloud::pesan_server* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* initial_data(
      ::grpc::CallbackServerContext* /*context*/, const ::Cloud::pesan_client* /*request*/, ::Cloud::pesan_server* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_initial_data<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_initial_data : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_initial_data() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_initial_data() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status initial_data(::grpc::ServerContext* /*context*/, const ::Cloud::pesan_client* /*request*/, ::Cloud::pesan_server* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_initial_data : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_initial_data() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_initial_data() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status initial_data(::grpc::ServerContext* /*context*/, const ::Cloud::pesan_client* /*request*/, ::Cloud::pesan_server* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestinitial_data(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_initial_data : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_initial_data() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->initial_data(context, request, response); }));
    }
    ~WithRawCallbackMethod_initial_data() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status initial_data(::grpc::ServerContext* /*context*/, const ::Cloud::pesan_client* /*request*/, ::Cloud::pesan_server* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* initial_data(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_initial_data : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_initial_data() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::Cloud::pesan_client, ::Cloud::pesan_server>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::Cloud::pesan_client, ::Cloud::pesan_server>* streamer) {
                       return this->Streamedinitial_data(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_initial_data() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status initial_data(::grpc::ServerContext* /*context*/, const ::Cloud::pesan_client* /*request*/, ::Cloud::pesan_server* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status Streamedinitial_data(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::Cloud::pesan_client,::Cloud::pesan_server>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_initial_data<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_initial_data<Service > StreamedService;
};

class protokol_2 final {
 public:
  static constexpr char const* service_full_name() {
    return "Cloud.protokol_2";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status kirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::Cloud::mes_server* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Cloud::mes_server>> Asynckirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Cloud::mes_server>>(Asynckirim_dataRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Cloud::mes_server>> PrepareAsynckirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::Cloud::mes_server>>(PrepareAsynckirim_dataRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void kirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client* request, ::Cloud::mes_server* response, std::function<void(::grpc::Status)>) = 0;
      virtual void kirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client* request, ::Cloud::mes_server* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Cloud::mes_server>* Asynckirim_dataRaw(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::Cloud::mes_server>* PrepareAsynckirim_dataRaw(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status kirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::Cloud::mes_server* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Cloud::mes_server>> Asynckirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Cloud::mes_server>>(Asynckirim_dataRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Cloud::mes_server>> PrepareAsynckirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::Cloud::mes_server>>(PrepareAsynckirim_dataRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void kirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client* request, ::Cloud::mes_server* response, std::function<void(::grpc::Status)>) override;
      void kirim_data(::grpc::ClientContext* context, const ::Cloud::mes_client* request, ::Cloud::mes_server* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::Cloud::mes_server>* Asynckirim_dataRaw(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::Cloud::mes_server>* PrepareAsynckirim_dataRaw(::grpc::ClientContext* context, const ::Cloud::mes_client& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_kirim_data_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status kirim_data(::grpc::ServerContext* context, const ::Cloud::mes_client* request, ::Cloud::mes_server* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_kirim_data : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_kirim_data() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_kirim_data() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status kirim_data(::grpc::ServerContext* /*context*/, const ::Cloud::mes_client* /*request*/, ::Cloud::mes_server* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestkirim_data(::grpc::ServerContext* context, ::Cloud::mes_client* request, ::grpc::ServerAsyncResponseWriter< ::Cloud::mes_server>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_kirim_data<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_kirim_data : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_kirim_data() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::Cloud::mes_client, ::Cloud::mes_server>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::Cloud::mes_client* request, ::Cloud::mes_server* response) { return this->kirim_data(context, request, response); }));}
    void SetMessageAllocatorFor_kirim_data(
        ::grpc::MessageAllocator< ::Cloud::mes_client, ::Cloud::mes_server>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::Cloud::mes_client, ::Cloud::mes_server>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_kirim_data() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status kirim_data(::grpc::ServerContext* /*context*/, const ::Cloud::mes_client* /*request*/, ::Cloud::mes_server* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* kirim_data(
      ::grpc::CallbackServerContext* /*context*/, const ::Cloud::mes_client* /*request*/, ::Cloud::mes_server* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_kirim_data<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_kirim_data : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_kirim_data() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_kirim_data() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status kirim_data(::grpc::ServerContext* /*context*/, const ::Cloud::mes_client* /*request*/, ::Cloud::mes_server* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_kirim_data : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_kirim_data() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_kirim_data() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status kirim_data(::grpc::ServerContext* /*context*/, const ::Cloud::mes_client* /*request*/, ::Cloud::mes_server* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestkirim_data(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_kirim_data : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_kirim_data() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->kirim_data(context, request, response); }));
    }
    ~WithRawCallbackMethod_kirim_data() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status kirim_data(::grpc::ServerContext* /*context*/, const ::Cloud::mes_client* /*request*/, ::Cloud::mes_server* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* kirim_data(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_kirim_data : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_kirim_data() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::Cloud::mes_client, ::Cloud::mes_server>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::Cloud::mes_client, ::Cloud::mes_server>* streamer) {
                       return this->Streamedkirim_data(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_kirim_data() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status kirim_data(::grpc::ServerContext* /*context*/, const ::Cloud::mes_client* /*request*/, ::Cloud::mes_server* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status Streamedkirim_data(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::Cloud::mes_client,::Cloud::mes_server>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_kirim_data<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_kirim_data<Service > StreamedService;
};

}  // namespace Cloud


#endif  // GRPC_Cloud_2eproto__INCLUDED