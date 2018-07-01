#include "crow_all.h"
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace boost::filesystem;

int main()
{
  
  try
  {
    path p{"/Users/raphael/Desktop/crow/dist"};
    p /= "my_file.txt";
    ofstream the_file{p};
    the_file << "Hello my face!\n";
  }
  catch (filesystem_error &e)
  {
    std::cerr << e.what() << '\n';
  }

  crow::SimpleApp app;
  CROW_ROUTE(app, "/")([](){
    return "Hello world";
  });

  CROW_ROUTE(app, "/static/<path>")
  ([](
    const crow::request& req,
    std::string the_path
  ){
    path local_path{"/Users/raphael/Desktop/crow/dist/static"};
    path file_path = local_path /= the_path;

    std::cout << file_path << "\n";
    boost::filesystem::ifstream this_file{file_path};


    if (!this_file.is_open()) { return crow::response{""}; }
    std::string the_string((std::istreambuf_iterator<char>(this_file)), (std::istreambuf_iterator<char>() ) );

    return crow::response{the_string};
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