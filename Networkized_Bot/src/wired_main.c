#include "../inc/wired_main.h"

int sockfd = 0;
extern char* username;
char* channel;
int dumpActivated = 0;
FILE *saveFile = NULL;
//int readInputForLexer( char *buffer, int *numBytesRead, int maxBytesToRead );



int main(int argc, char** argv) {

    char type;
    char hostname_or_adress[40];

    printf("Enter i for specifying a IP adress, enter h for a hostname to connect :\n");
    scanf("%c", &type);

    srand(time(NULL));

    struct sockaddr_in serv_addr;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error, could not create socket.\n");
        return 1;
    }

    int port;
    printf("Enter the port.\n");
    scanf("%d", &port);


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if(type == 'i')
    {
        printf("Enter the IP adress.\n");
        scanf("%s", hostname_or_adress);
        serv_addr.sin_addr.s_addr = inet_addr(hostname_or_adress);
    }
    else if (type == 'h')
    {
        printf("Enter the hostname.\n");
        scanf("%s", hostname_or_adress);
        serv_addr.sin_addr.s_addr = inet_addr(hostname_to_ip(hostname_or_adress));
    }
    else 
    {
        printf("Invalid argument.\n");
        return 1;
    }

    char* user_channel;
    printf("Enter the channel you want to join.\n");
    scanf("%s", user_channel);



    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nError : Connect failed.\n");
        return 1;
    }

    write(sockfd, "NICK Lainbot\n", sizeof("NICK Lainbot\n")-1);
    write(sockfd, "USER Lainbot 8 x : Battlestar\n", sizeof("USER Lainbot 8 x : Battlestar\n")-1);
    char join_mess[40];
    sprintf(join_mess, "JOIN %s\n", user_channel);
    write(sockfd, join_mess, strlen(join_mess));

    while(1)
    {
        yyparse();

    }
    return 0;
}

int readInputForLexer( char *buffer, int *numBytesRead, int maxBytesToRead ) {

    char* globalInputText;
    char wireBuff[1024];
    memset(wireBuff, '\0', sizeof(wireBuff));
    read(sockfd, wireBuff, sizeof(wireBuff));

    globalInputText = strdup(wireBuff);

    int numBytesToRead = maxBytesToRead;
    int bytesRemaining = strlen(globalInputText);
    int i;
    if ( numBytesToRead > bytesRemaining ) { numBytesToRead = bytesRemaining; }
    for ( i = 0; i < numBytesToRead; i++ ) {
        buffer[i] = globalInputText[i];
    }
    *numBytesRead = numBytesToRead;

    if(dumpActivated)
        fprintf(saveFile, "%.*s\n", *numBytesRead-1, buffer);
    return 0;
}

void netprint(char* in_mess)
{
    char message[200];
    sprintf(message, "PRIVMSG %s :%s", channel, in_mess);
    in_mess = strdup(message);
    if (dumpActivated)
        fprintf(saveFile, "%s", in_mess);
    write(sockfd, in_mess, strlen(in_mess));
}

void reply_greetings()
{
    char message[100];
    switch(rand() % 5)
    {
        case 0:
            sprintf(message, "Hello, %s! How are you doing?\n", username);
            break;

        case 1:
            sprintf(message, "%s : Hi.\n", username);
            break;

        case 2:
            sprintf(message, "%s : Greetings!\n", username);
            break;

        case 3:
            sprintf(message, "Ahoy, %s.\n", username);
            break;

        case 4:
            sprintf(message, "Welcome, %s.\n", username);
            break;
    }

    char* out = strdup(message);
    netprint(out);
}

void irc_disconnect()
{
    netprint("Instruction to leave recieved, immediate execution.\n");
    write(sockfd, "QUIT Quit_Command_Recieved\n", sizeof("QUIT Quit_Command_Recieved\n")-1);
    close(sockfd);
    if(saveFile)
        fclose(saveFile);
    exit (0);
}

void list_help()
{
    netprint("I, Lain, am a experimental bot using pattern recognition in order to understand and execute orders. I'm not in final state, and I hope I'll be able to help you when finished.");
    netprint("I'll be concieved to handle operating tasks, banning annoying people, and all that will be programmed into me.");
    netprint("I respond to greetings in may different forms, even if I may miss some of them. I'm still learning.");
    netprint("I respond to insults, not only those directed against me.");
    netprint("More interesting, I'm able to save the conversation into a file. The syntax for this is save|load|monitor(ing)?|dump. I'll create files myself.");
    netprint("In case you're living in a cave, I can too display the current time in my timezone.");
}

void getTime(char time_now[100])
{
    time_t now;
    time(&now);

    sprintf(time_now, "%s", ctime(&now));
}


void startDump()
{
    saveFile = fopen("Lainbot-conversation-dump", "a");
    if (saveFile == NULL)
    {
        netprint("I was not able to open the file. The operation coule not complete.\n");
        return;
    }

    char time[100];

    getTime(time);
    
    fprintf(saveFile, "\n\n\tBeginning save at %s.\n", time);

    dumpActivated = 1;

}

void endDump()
{
    dumpActivated = 0;

    if(saveFile)
    fclose(saveFile);

    printf("Fin d'enregistrement.");
}

