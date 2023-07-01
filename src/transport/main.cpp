#include <binding/http/common.h>
#include <binding/http/server.h>
#include <binding/http/router.h>

/// proof of concept of the api that we need to build.

int main() {
    binding:http::http_context context;
    context.port = 9000;
    context.tls = true;
    context.host = "127.0.0.1";

    auto router = binding::http::make_router()
    router.GET("/", [](binding::http::response_writer* writer, binding::http::request*,  binding::http::params& params){
    });
    router.GET("/get", [](binding::http::response_writer* resp, binding::http::request* req) {
        resp->json["origin"] = req->client_addr.ip;
        resp->json["url"] = req->url;
        resp->json["args"] = req->query_params;
        resp->json["headers"] = req->headers;
        return 200;
    });
    auto server = binding::http::make_server(context, router);
    server->listen_serve()   
}