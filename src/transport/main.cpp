#include <binding/http/common.h>
#include <binding/http/server.h>
#include <binding/http/router.h>


int main() {
    binding:http::http_context context;
    auto router = binding::http::make_router()
    router.add(binding::, "/", [](binding::http::response_writer& writer, binding::http::request&,  binding::http::params params){
    });
    auto server = binding::http::make_server(context, router);
    server.listen_serve()   
}
