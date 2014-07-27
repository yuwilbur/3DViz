//
//  main.cpp
//  GetRequest
//
//  Created by Anson Liu on 7/27/14.
//  Copyright (c) 2014 Apparent Etch. All rights reserved.
//

#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions

int main(int argc, const char * argv[])
{
    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
    
    // The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
    // to by hints must contain either 0 or a null pointer, as appropriate." When a struct
    // is created in C++, it will be given a block of memory. This memory is not necessary
    // empty. Therefor we use the memset function to make sure all fields are NULL.
    memset(&host_info, 0, sizeof host_info);
    
    std::cout << "Setting up the structs..."  << std::endl;
    
    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
    
    // Now fill up the linked list of host_info structs with google's address information.
    status = getaddrinfo("127.0.0.1", "5000", &host_info, &host_info_list);
    // getaddrinfo returns 0 on succes, or some other value when an error occured.
    // (translated into human readable text by the gai_gai_strerror function).
    if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status) ;
    
    std::cout << "Creating a socket..."  << std::endl;
    int socketfd ; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                      host_info_list->ai_protocol);
    if (socketfd == -1)  std::cout << "socket error " ;
    
    std::cout << "Connect()ing..."  << std::endl;
    status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  std::cout << "connect error" ;
    
    std::cout << "send()ing message..."  << std::endl;
    char *msg = "GET /images/taylor HTTP/1.1\nhost: www.google.com\n\n";
    int len;
    ssize_t bytes_sent;
    len = strlen(msg);
    bytes_sent = send(socketfd, msg, len, 0);
    
    std::string str;
    
    std::cout << "Waiting to recieve data..."  << std::endl;
    ssize_t bytes_recieved;
    char incoming_data_buffer[100];
    bytes_recieved = recv(socketfd, incoming_data_buffer,100, 0);
    
    
    while (bytes_recieved > 0) {
        // If no data arrives, the program will just wait here until some data arrives.
        
        std::cout << bytes_recieved << " bytes recieved :" << std::endl ;
        //std::cout << incoming_data_buffer << std::endl;
        str.append(incoming_data_buffer);
        memset(&incoming_data_buffer, 0, sizeof incoming_data_buffer);
        bytes_recieved = recv(socketfd, incoming_data_buffer,100, 0);
    }
    
    if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
    if (bytes_recieved == -1)std::cout << "recieve error!" << std::endl ;
    
    char* httpbody;
    httpbody = strstr(incoming_data_buffer, "\r\n\r\n");
    if(httpbody) {
        httpbody += 4;
        std::cout << httpbody << std::endl;
    }
    
    //std::cout << str << std::endl;
    
    
    //isolate json array
    std::size_t endFound = str.find("}]");
    std::size_t startFound = str.find("[{");
    if (startFound!=std::string::npos && endFound!=std::string::npos) {
        std::cout << str.substr(startFound, endFound + 2 - startFound) << std::endl;
    }
    
    //json parsing
    std::string* urlArray = (std::string*)malloc(sizeof(std::string)*100);
    
    std::size_t startPos = str.find("\"url\":");
    std::size_t endPos = str.find("\"height\":");
    int i = 0;
    while (startPos!=std::string::npos && endPos!=std::string::npos) {
        urlArray[i] = str.substr(startPos + 8, endPos - 11 - startPos);
        std::cout << str.substr(startPos + 8, endPos - 11 - startPos) << std::endl;
        //str.erase(str.begin(), endPos);
        str = str.substr(endPos + 5, sizeof(str) - endPos);
        i++;
        startPos = str.find("\"url\":");
        endPos = str.find("\"height\":");
    }
    
    
    
    
    
    
}

