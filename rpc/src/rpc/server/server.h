#ifndef RPC_SERVER_SERVER_H__
#define RPC_SERVER_SERVER_H__

#include <memory>
#include <uv.h>
#include "rpc/processer.h"

namespace rpc {

class Server {
public:
    Server();

    ~Server();

    void UseProcesser(const std::shared_ptr<Processer>& p);

    int Run(const std::string& lisUri);

    // TODO
    void Stop();

private:
    std::shared_ptr<Processer>& processer_;
    uv_loop_t uv_loop_;
    uv_tcp_t accepter_;
};


}   // namespace rpc

#endif   // RPC_SERVER_SERVER_H__