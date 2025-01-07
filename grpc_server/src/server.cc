#include <grpcpp/grpcpp.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/support/status.h>

#include <memory>

#include "hello.grpc.pb.h"
#include "hello.pb.h"

class ProcessingImpl : public ProcessingServices::Service
{
  ::grpc::Status computeSum(
    ::grpc::ServerContext * context, const ::Point3 * request, ::Numeric * response)
  {
    std::cout << "Called!" << std::endl;
    response->set_value(request->x() + request->y() + request->z());
    return grpc::Status::OK;
  }
};

int main(int argc, char * argv[])
{
  ProcessingImpl service;
  grpc::ServerBuilder builder;
  builder.AddListeningPort("0.0.0.0:9999", grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  server->Wait();

  return 0;
}
