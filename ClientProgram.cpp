#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>

using namespace std;

int main()
{
char Terminator[1024] = "Terminate";
int MaximumSize = 1024;
char userName[MaximumSize];
int PortNumber;
char RequestUserName[1024];
char ServerHost[MaximumSize];
char PublicKey[1024];



cout<<"Enter a server host name : ";
cin>>ServerHost;
cout<<"Enter server port number : ";
cin>>PortNumber;

//creating a client variable
int client;
struct sockaddr_in server_addr;


char hostName[MaximumSize];

//cheacks if host name is valid
gethostname(hostName , MaximumSize);
if(strcmp(hostName, ServerHost) != 0){

  cout<<"server name is incorrect Bye, Hostname should be "<<hostName<<endl;

  return (-1);
}

struct hostent *hp = gethostbyname(hostName);

if(hp == NULL){

  errno = ECONNREFUSED;
   return (-1);
}



memset(&server_addr,0, sizeof(server_addr));
memcpy((char *)&server_addr.sin_addr,hp->h_addr,hp->h_length);


server_addr.sin_family = hp->h_addrtype;

server_addr.sin_port = htons(PortNumber);


if ((client = socket(hp->h_addrtype,SOCK_STREAM,0)) < 0)
    return(-1);
  if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0){

  }


cout<<"Enter User name : \n";
cin>>RequestUserName;
    //sends the username store in RequestUserName to the server with a maximum character of 1024
    send(client, RequestUserName, 1024 , 0);

    //recieve result from the server and store it in publicKey with a maximum of 1024 characters
    recv(client, PublicKey,1024, 0);

    //prints the username  and the publuc key
    cout<<"the Public key for the user << "<<RequestUserName <<" is :"<< PublicKey<< endl;

    // this while loop continues tpo make request and stay connected on the server untill Terminate is typed
    while(strcmp(RequestUserName,Terminator) != 0){

     cout<<"Enter User name : \n";
     cin>>RequestUserName;


    send(client, RequestUserName, 1024 , 0);
    recv(client, PublicKey,1024, 0);


    cout<<"the Public key for the user << "<<RequestUserName <<" is :"<< PublicKey<< endl;



    }
    //close the connection with the server
    //small letter client should have been name the server 
    close(client);

 return 0;
}
