#include "exchange.hpp"
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <errno.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <netdb.h>
// #include <netinet/in.h>
// #include <errno.h>
#include <fstream>
#include <iostream>

// Should support test mode or just regular functioning mode 
int main(int argc, char* argv[]) {
  Exchange& exchange = Exchange::getInstance();
  std::string input;
  std::ifstream stocks;
  if (argc == 3) {
    stocks.open(argv[1]);
    if (stocks.is_open()) {
      while (std::getline(stocks, input)) { 
        exchange.processOrderBookAndStockCreationMessage(input);
      }
    }
    stocks.close();
    std::ifstream orders;
    orders.open(argv[2]);
    if (orders.is_open()) {
      while (std::getline(orders, input)) { 
        exchange.processOrderMessage(input);
        std::cout << exchange.to_string() << std::endl;
        std::cout << "=============================================================" << std::endl;
      }
    }
  }
  
  
  // Initialize Things 
  // if (argc == 1) {
  //   Exchange& exchange = Exchange::getInstance();
  //   int sock_fd, status, new_fd, numbytes, yes = 1;
  //   struct addrinfo hints, *servinfo, *p;
  //   char buffer[256];
  //   struct sockaddr_storage client_addr;
  //   socklen_t sin_size;
  
  //   memset(&hints, 0, sizeof(hints));
  //   hints.ai_family = AF_UNSPEC;
  //   hints.ai_socktype = SOCK_STREAM;
  //   hints.ai_flags = AI_PASSIVE;

  //   if ((status = getaddrinfo(NULL, argv[1], &hints, &servinfo) != 0)) {
  //     std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
  //     exit(1);
  //   }

  //   for (p = servinfo; p != NULL; p = p->ai_next) {
  //     if ((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
  //       perror("server: socket");
  //       continue;
  //     }

  //     if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
  //       perror("setsockopt");
  //       exit(1);
  //     }

  //     if (bind(sock_fd, p->ai_addr, p->ai_addrlen) == 1) {
  //       close(sock_fd);
  //       perror("server: bind");
  //       continue;
  //     }
  //     break;
  //   }

  //   freeaddrinfo(servinfo);

  //   if (p == NULL) {
  //     fprintf(stderr, "server: failed to bind\n");
  //     exit(1);
  //   }

  //   if (listen(sock_fd, 10) == -1) { 
  //     perror("listen");
  //     exit(1);
  //   }

  //   while (1) {
  //     sin_size = sizeof(client_addr);
  //     new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
  //     if (new_fd == -1) {
  //       perror("accept");
  //       continue;
  //     }

  //     if (!fork()) {
  //       close(sock_fd);
  //       int numbytes;
  //       while ((numbytes = recv(new_fd, buffer, 256, 0)) > -1) {
  //         if (numbytes == 0) {
  //           break;
  //         }
  //         // Need detection
  //         // Designate a specific end character for end of transmission from client
  //         if (buffer[0] == '\n') {
  //           exit(0);
  //         } else {
  //           std::cout << buffer << std::endl;
  //         }
  //       }
  //       close(new_fd);
  //       exit(0);
  //     }
  //     close(new_fd);
  //   }
  // } else if (argc == 2){
  //   // Investor
  //   int sock_fd, status, new_fd, numbytes, yes = 1;
  //   struct addrinfo hints, *servinfo, *p;
  //   char buffer[256];
  //   struct sockaddr_storage client_addr;
  //   socklen_t sin_size;
  
  //   memset(&hints, 0, sizeof(hints));
  //   hints.ai_family = AF_UNSPEC;
  //   hints.ai_socktype = SOCK_STREAM;
  //   hints.ai_flags = AI_PASSIVE;

  //   if ((status = getaddrinfo(NULL, argv[1], &hints, &servinfo) != 0)) {
  //     std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
  //     exit(1);
  //   }

  //   for (p = servinfo; p != NULL; p = p->ai_next) {
  //     if ((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
  //       perror("server: socket");
  //       continue;
  //     }

  //     if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
  //       perror("setsockopt");
  //       exit(1);
  //     }

  //     if (bind(sock_fd, p->ai_addr, p->ai_addrlen) == 1) {
  //       close(sock_fd);
  //       perror("server: bind");
  //       continue;
  //     }
  //     break;
  //   }

  //   freeaddrinfo(servinfo);

  //   if (p == NULL) {
  //     fprintf(stderr, "server: failed to bind\n");
  //     exit(1);
  //   }

  //   if (listen(sock_fd, 10) == -1) { 
  //     perror("listen");
  //     exit(1);
  //   }

  // } 
  return 0;  
}