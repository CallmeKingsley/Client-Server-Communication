#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <map>


using namespace std;
int maximum = 1024;

//Struct that represent each line
struct information{
  char publicKey[1024];
	char UserName[1024];
};

int ServerImplementation(information info[1024], int PortNumber,int Elementsize){
  int client;
	int server;

  int check;
  char Terminator[1024] = "Terminate";
	char Respond[1024];
	char UserName[1024];
	char ServerResoond[1024];
	char publicKey[1024];
  char RequestedpublicKey[1024];



    struct sockaddr_in server_addr;
    socklen_t size;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0)
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }



    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(PortNumber);


    if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0)
    {
        cout << "=> Error binding connection, the socket has already been established..." << endl;
        return -1;
    }

    size = sizeof(server_addr);
    cout << "=> Looking for clients..." << endl;



    listen(client, 3);



    int clientCount = 1;
    server = accept(client,(struct sockaddr *)&server_addr,&size);


    recv(server, UserName , 1024, 0);


    cout<<" UserName from the Server "<<UserName<<endl;


    cout<<"elements are "<<Elementsize<<endl;
    for(int i = 0; i < Elementsize;i++){


         check = strcmp(info[i].UserName,UserName);

        if(check == 0){

          strcpy(RequestedpublicKey,info[i].publicKey);
          send(server,RequestedpublicKey,1024,0);
         }
    }


    while(strcmp(UserName,Terminator) != 0){

        recv(server, UserName , 1024, 0);
        for(int i = 0; i < Elementsize;i++){


         check = strcmp(info[i].UserName,UserName);

        if(check == 0){

          strcpy(RequestedpublicKey,info[i].publicKey);
          send(server,RequestedpublicKey,1024,0);

         }

    }

    }



    close(client);

   return 0;
}

int getinfo(information info[],string fileName){

    int counter = 0;
    string Line;
    string SecondLine;
    ifstream myfile;
    char publicKey[1024];
	char UserName[1024];


    myfile.open(fileName.c_str());

    while(getline(myfile, Line)){

          if(!Line.empty()&& Line.at(0) != '#'){

            stringstream ss(Line.c_str());


              while(ss>>UserName>>publicKey){

              	strcpy(info[counter].UserName,UserName);
              	strcpy(info[counter].publicKey, publicKey);

                 counter++;
              }
          }

    }
     myfile.close();

    return counter;
}
void checkinginside(int NumElement, information info[]){

    for(int i = 0; i < NumElement;i++){

         cout<<"UserName "<<info[i].UserName<<" password"<<info[i].publicKey<<endl;
    }


}
int main()
{

    int PortNumber;
    string fileName;
    struct information info[1024];
    struct information info2[1024];
    cout<<" Enter a file Name:";
    cin>>fileName;
    cout<<" Enter Server port Number :";
    cin>>PortNumber;

    int numberOfelement = getinfo(info, fileName);

    if(PortNumber > 0){

         ServerImplementation(info,PortNumber,numberOfelement);

    }

	return 0;
}
