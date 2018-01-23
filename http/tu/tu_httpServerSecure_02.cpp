#include "httpServer.cpp"
#include <iostream>
#include <csignal>
//
volatile bool goOn = true;
void sighandler(int theSignal) {
  goOn = false;
}
const char* const IP = "192.168.1.12";
// const char* const IP = "127.0.0.1"; 
const uint16_t PORT = 10175;
void printFunc(httpReq& req, httpRes& res) {
  req.print();
  res.setHeader(std::string("Access-Control-Allow-Origin"),std::string("*"));
}
int main() {
  struct sigaction action;
  /* Reset Sigaction. */
  std::memset(&action, 0, sizeof(action));        // Empty mask by default/
  action.sa_handler   = sighandler;           // Set the handler function.
  action.sa_flags     = 0;                    // Remove any flag from sa_flag.
  sigaction(SIGINT, &action, nullptr);

  httpServer server(PORT, IP);
  server.bind();
  server.addRestFunction("",printFunc);
  server.open();
  while(goOn);
  server.close();
}
