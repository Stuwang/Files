#include "rpc/server/Connection.h"

namespace rpc {

Connection::Connection() : is_writing_(false) {}

Connection::Connection(uv_loop_t* loop) {}

Connection::~Connection() {}


void Connection::Process(const char* data, const size_t len) {}

void Connection::Write(const char* data, size_t len) {
    if (len == 0) {
        return;
    }
    if (!is_writing_) {
        assert(write_buf_.size() == 0);
        write_buf_.append(data, len);
        uv_buf_t wrbuf = uv_buf_init(write_buf_.data(), write_buf_.size());
        write_->data = this;
        uv_write(write_, this, &wrbuf, 1, Connection::echo_write);
    } else {
    }
}

void Connection::ReadCallback() {}

// static
void Connection::alloc_cb(uv_handle_t* c, size_t size, uv_buf_t* buf) {
    Connection* connection = static_cast<Connection*>(c);
    buf->base = connection->read_buf_.data();
    buf->len = connection->read_buf_.suze();
}

void Connection::read_cb(uv_stream_t* client,
                         ssize_t nread,
                         const uv_buf_t* buf) {
    Connection* connection = static_cast<Connection*>(client);
    connection->read_buf_.resize(buf->len);
    connection->ReadCallback();
}

void Connection::write_cb(uv_write_t* req, int status) {
    // TODO
    LOG() << "Write ok %s\n";
}

void Connection::close_cb(uv_handle_t* client) {
    // TODO
    LOG() << "close %s\n";
}

}   // rpc