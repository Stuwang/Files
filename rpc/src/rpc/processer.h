#ifndef RPC_PROCESSER_H__
#define RPC_PROCESSER_H__

#include <string>
#include <fucntional>

namespace rpc {

typedef std::function<void(const std::string& req, std::string* resp)>
    ProcesserFunc;

class Processer {
public:
    virtual ~Server() {}

    virtual int Register(const std::string& name, const ProcesserFunc* p) = 0;

    virtual int Process(const std::string& name,
                        const std::string& req,
                        std::string* resp) = 0;
};


}   // namespace rpc

#endif   // RPC_PROCESSER_H__