#ifndef RPC_SERVER_CONNECTION_H__
#define RPC_SERVER_CONNECTION_H__

#include <uv.h>
#include "rpc/processer.h"

namespace rpc {

enum class SocketState {
    RECV_SIZE;
    RECV_FRAME;
};

class Connection : public uv_stream_t {
public:
    Connection();

    explicit Connection(uv_loop_t* loop);

    ~Connection();

    void SetProcesser(Processer* p) { p_ = p; }

    void Process(const char* data, const size_t len);

    void Write(const char* data, size_t len);

    void ReadCallback();

private:
    static void alloc_cb(uv_handle_t*, size_t size, uv_buf_t* buf);
    static void read_cb(uv_stream_t* client,
                        ssize_t nread,
                        const uv_buf_t* buf);
    static void write_cb(uv_write_t* req, int status);
    static void close_cb(uv_handle_t* client);


    SocketState receving_state_;
    std::string read_buf_;
    std::string read_extra_buf_;

    bool is_writing_;
    uv_write_t write_;
    std::string write_buf_;
    Processer* p_;
};


}   // namespace rpc

#endif   // RPC_SERVER_CONNECTION_H__