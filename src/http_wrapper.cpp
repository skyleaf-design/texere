#include "lib/crow_all.h"
#include "texere.hpp"
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <unordered_set>

using namespace boost::filesystem;

int main()
{
  crow::SimpleApp app;
  std::mutex users_busy;;
  std::unordered_set<crow::websocket::connection*> users;

  // Real-time web socket.

  CROW_ROUTE(app, "/listen")
    .websocket()
    .onopen([&](crow::websocket::connection& conn){
      CROW_LOG_INFO << "new websocket connection";
      std::lock_guard<std::mutex> _(users_busy);
      users.insert(&conn);
    })
    .onclose([&](crow::websocket::connection& conn, const std::string& reason){
      CROW_LOG_INFO << "websocket connection closed: " << reason;
      std::lock_guard<std::mutex> _(users_busy);
      users.erase(&conn);
    })
    .onmessage([&](crow::websocket::connection& /*conn*/, const std::string& data, bool is_binary){
      std::lock_guard<std::mutex> _(users_busy);
      for(auto u:users)
        if (is_binary)
          u->send_binary(data);
        else
          u->send_text(data);
    })
  ;


  CROW_ROUTE(app, "/")([](){
    return "Hello world";
  });

  // Static client file server.

  CROW_ROUTE(app, "/static/<path>")
  ([](
    const crow::request& req,
    const std::string the_path
  ){
    std::cout << "Hey, we are here" << std::endl;
    // NOTE: you must cd to the '/dist' directory for the current directory to work.
    path file_path = boost::filesystem::current_path() /= boost::filesystem::path{"static"} /= the_path;
    std::cout << file_path << std::endl;
    boost::filesystem::ifstream this_file{file_path};
    if (!this_file.is_open()) { return crow::response{""}; }

    std::string the_string((std::istreambuf_iterator<char>(this_file)), (std::istreambuf_iterator<char>() ) );
    crow::response res{the_string};
    return res;
  });

  // Entity REST API.

  CROW_ROUTE(app, "/note/<int>")
  ([](
    const crow::request& req,
    const int id
  ){
    std::cout << "Is this the muffin man??" << "\n";
    // GET, POST (search), PUT, PATCH, DELETE
    return crow::response{"Schlomo Vaknin."};
  }); 



  CROW_ROUTE(app, "/params")
  ([](const crow::request& req){
    std::ostringstream os;
    os << "Params: " << req.url_params << "\n\n"; 
    os << "The key 'foo' was " << (req.url_params.get("foo") == nullptr ? "not " : "") << "found.\n";
    if(req.url_params.get("pew") != nullptr) {
        double countD = boost::lexical_cast<double>(req.url_params.get("pew"));
        os << "The value of 'pew' is " <<  countD << '\n';
    }
    auto count = req.url_params.get_list("count");
    os << "The key 'count' contains " << count.size() << " value(s).\n";
    for(const auto& countVal : count) {
        os << " - " << countVal << '\n';
    }
    return crow::response{os.str()};
  }); 

  // Static content route for public assets
  // Websocket route for heartbeat
  // REST API route for Note entity CRUD

  app.port(18080).multithreaded().run();
}