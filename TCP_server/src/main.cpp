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
    //Create a socket
    int listening = socket(AF_INET,SOCK_STREAM,0);
    if(listening== -1)
    {
        std::cerr<<"Can't create a socket!\n";
        return -1;
    }


    //bind the socket to IP/Port
    sockaddr_in hint;

    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000); 
    
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);


    //mark the socket for listening 
    if(bind(listening, (struct sockaddr*) &hint, sizeof(hint)) == -1)
    {
        std::cerr<<"Can't bind to IP/Port \n";
        return -2;
    }

    if(listen(listening,SOMAXCONN) == -1)
    {
        std::cerr<<"Can't listen! \n";
        return -3;
    }


    //to accept a call from the client
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    
    int clientSocket = accept(listening,
                              (struct sockaddr*) &client,
                              &clientSize);

    if (clientSocket == -1)
    {
        std::cerr<<"Problem with Client connecting! \n";
        return -4;
    }

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];



    memset(host,0,NI_MAXHOST);
    memset(service,0,NI_MAXSERV);




    int result = getnameinfo((struct sockaddr*)&client,
                             sizeof(client),
                             host,
                             NI_MAXHOST,
                             service,
                             NI_MAXSERV,
                             0);
    if (result)
    {
        std::cout<< host <<" connected on "<< service << "\n";
    }
    else
    {
        inet_ntop(AF_INET,&client.sin_addr,host,NI_MAXHOST);
        std::cout<< host <<" connected on "<< ntohs(client.sin_port)<<"\n";
    }

    //close the listening socket
    close(listening); // we do this AFTER our one client has connected... since its a simple tutorial


    char buf[4096];
    while(true)
    {
        //clear the buffer
        memset(buf,0,4096);
        //wait for client data
        int bytesRecv = recv(clientSocket,buf,4096,0);
        if (bytesRecv == -1)
        {
            std::cerr<<" There was/is a connection issue \n";
            break;
        }

        if (bytesRecv == 0)
        {
            std::cout<< "The client disconnected \n";
            break;
        }
        //Display message
        std::cout<<" received: "<<std::string(buf,0,bytesRecv)<<"\n";
        
        //Resend message to client
        send(clientSocket,buf,bytesRecv +1 ,0);
    }
    close(clientSocket);

    return 123;
}