#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


int main()
{   
    //create a socket
    int sock = socket(AF_INET,SOCK_STREAM,0);

    if(sock == -1)
    {
        return 1;
    }

    int port = 54000;
    
    std::string ipAddress = "127.0.0.1";

    //creating the hint structure
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port=htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //connet to the server on the socket
    int connectRes = connect(sock, 
                            (struct sockaddr*) &hint,
                            sizeof(hint));
    if (connectRes == -1)
    {
        return 1;
    }

    char buf[4096];
    std::string userInput;

    //do while loop:
    do
    {   
        //take user input 
        std::cout<<"Enter lines of text to send to the server (message terminates when you press enter)\n";
        getline(std::cin,userInput);

        //send to server
        int sendRes = send(sock,userInput.c_str(),userInput.size() +1,0);

        if(sendRes == -1)
        {
            std::cout<<"Could not send to server! \r\n";
            continue;
        }

        //wait and receive response from server
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);

        //print the data received from the server
        std::cout<<" SERVER>> "<<std::string(buf,bytesReceived)<<"\r\n";
    }
    while(true);

    close(sock);



    return 123;
}
