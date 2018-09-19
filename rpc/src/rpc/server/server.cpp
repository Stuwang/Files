#include "rpc/server/server/h"

namespace rpc {

Server::Server {
    uv_loop_init(uv_loop_);
    uv_tcp_init(uv_loop_, &accepter_);
}

Server::~Server {}

void Server::UseProcesser(const std::shared_ptr<Processer>& p) {
    processer_ = p;
}

int Server::Run(const std::string& lisUri) {
    // parse listen uri
    std::string addrStr;
    uint16_t port = 0;
    size_t index = lisUri.find(":");
    if (index != string::pos) {
        addr = lisUri.substr(0, index);
    }
    auto portStr = lisUri.substr(index + 1);
    port = atoi(portStr.c_str());
    struct sockaddr_in addr;
    uv_ip4_addr(addrStr.c_str(), port, &addr);

    uv_tcp_bind(&accepter_, (const struct sockaddr*)&addr, 0);

    return 0;
}

}   // namespace rpc


#include <uv.h>
#include <cstring>
#include <iostream>

#include "rpc/base/log.h"

void alloc_cb(uv_handle_t*, size_t size, uv_buf_t* buf) {
    buf->base = (char*)malloc(size);
    buf->len = size;
    memset(buf->base, 0, size);
}

void on_close(uv_handle_t* client) {
    LOG() << "Connection Close";
    free(client);
}

void echo_write(uv_write_t* req, int status) {
    if (status) {
        LOG() << "Write error %s\n" << uv_strerror(status);
    }
    LOG() << "write data ok :" << static_cast<const char*>(req->data);
    if (req->data) {
        free(req->data);
    }
    free(req);
}

void read_cb(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) {
    if (nread < 0) {
        if (buf->base) {
            free(buf->base);
        }
        uv_close((uv_handle_t*)client, on_close);
    } else if (nread > 0) {
        LOG() << "read data : " << static_cast<const char*>(buf->base);
        uv_write_t* req = (uv_write_t*)malloc(sizeof(uv_write_t));
        uv_buf_t wrbuf = uv_buf_init(buf->base, nread);
        req->data = buf->base;
        uv_write(req, client, &wrbuf, 1, echo_write);
    }
}

void on_new_connection(uv_stream_t* server, int status) {
    LOG() << "new connection";
    if (status < 0) {
        LOG() << "New connection error %s\n" << uv_strerror(status);
        // error!
        return;
    }

    printf((const char*)server->data);

    uv_tcp_t* client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        uv_read_start((uv_stream_t*)client, alloc_cb, read_cb);
    } else {
        uv_close((uv_handle_t*)client, on_close);
    }
}

int main(int argc, char** argv) {

    unsigned short port = 0;

    if (argc == 1) {
        port = 8080;
        LOG() << "not set port, use 8080 ";
    } else {
        port = static_cast<unsigned short>(atoi(argv[1]));
    }

    std::ios::sync_with_stdio(false);

    uv_loop_t* loop = (uv_loop_t*)malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    uv_tcp_t server;
    uv_tcp_init(loop, &server);
    server.data = (void*)"what the fuck !!!";
    printf((const char*)server.data);

    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", port, &addr);

    uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    int r = uv_listen((uv_stream_t*)&server, 100, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }
    return uv_run(loop, UV_RUN_DEFAULT);
}
