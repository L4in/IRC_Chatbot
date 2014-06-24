#include "../inc/wired_main.h"

int sockfd = 0;
extern char* username;
char* channel;
char* userhost;
int dumpActivated = 0;
int barrel[9];
int roulette_actualChamber;
int chamberNumber;
FILE *saveFile = NULL;
//int readInputForLexer( char *buffer, int *numBytesRead, int maxBytesToRead );



int main(int argc, char** argv) {

    /* User interface for parameters */

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


    /*
     * Socket opening
     */

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nError : Connect failed.\n");
        return 1;
    }

    /*
     * IRC protocol : nick, ID and join channel
     */

    write(sockfd, "NICK Lainbot\n", sizeof("NICK Lainbot\n")-1);
    write(sockfd, "USER Lainbot 8 x : Battlestar\n", sizeof("USER Lainbot 8 x : Battlestar\n")-1);
    char join_mess[40];
    sprintf(join_mess, "JOIN %s\n", user_channel);
    write(sockfd, join_mess, strlen(join_mess));

    //Initializing the russian roulette
    int i;
    for (i = 0; i < 9; i ++)
    {
        barrel[i] = 0;
    }
    roulette_actualChamber = 0;
    chamberNumber = 6;
    while(1)
    {
        yyparse();

    }
    return 0;
}

/*
 * Returns the system time
 */

void getTime(char time_now[100])
{
    time_t now;
    time(&now);

    sprintf(time_now, "%s", ctime(&now));
}

/*
 * Mystical function to get input from socket and dump conversation if needed
 */

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

/*
 * Send the message into the channel and eventually saves what have been said
 */

void netprint(char* in_mess)
{
    char message[200];
    sprintf(message, "PRIVMSG %s :%s", channel, in_mess);
    in_mess = strdup(message);
    if (dumpActivated)
        fprintf(saveFile, "%s", in_mess);
    write(sockfd, in_mess, strlen(in_mess));
}

/*
 * Randomly respond to a hail
 */

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

/*
 * Notify the channel for deconnection and then disconnect
 */

void irc_disconnect()
{
    netprint("Instruction to leave recieved, immediate execution.\n");
    write(sockfd, "QUIT :Quit_Command_Recieved\n", sizeof("QUIT :Quit_Command_Recieved\n")-1);
    close(sockfd);
    if(saveFile)
    {
        char time[100];

        getTime(time);

        fprintf(saveFile, "\n\tEnding save at %s.\n", time);
        fclose(saveFile);
    }

    exit (0);
}

/* 
 * Shows an about message
 */

void list_help()
{
    netprint("I, Lain, am a experimental bot using pattern recognition in order to understand and execute orders. I'm not in final state, and I hope I'll be able to help you when finished.\n");
    netprint("I'll be concieved to handle operating tasks, banning annoying people, and all that will be programmed into me.\n");
    netprint("I respond to greetings in may different forms, even if I may miss some of them. I'm still learning.\n");
    netprint("I respond to insults, not only those directed against me.\n");
    netprint("More interesting, I'm able to save the conversation into a file. The syntax for this is save|load|monitor(ing)?|dump. I'll create files myself.\n");
    netprint("In case you're living in a cave, I can too display the current time in my timezone.\n");}

    /*
     * Start the dump of a conversation.
     */
void startDump()
{
    if(saveFile)
    {
        netprint("I'm already recording.\n");
        return;
    }
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

/*
 * Stops dumping
 */

void endDump()
{
    if(saveFile == NULL)
    {
        netprint("I'm not recording at the moment.\n");
        return;
    }

    dumpActivated = 0;

    char time[100];


    getTime(time);

    fprintf(saveFile, "\n\tEnding save at %s.\n", time);

    if(saveFile != NULL)
        fclose(saveFile);

    saveFile == NULL;

    netprint("I'm not recording anymore.\n");

    printf("Fin d'enregistrement.");
}

/*
 * Wait 30 seconds before unbanning a russian roulette player
 */

void *paused_unban(void * banned_user)
{
    sleep(30);
    netprint("\001ACTION Swings magic wand\001\n");

    char message[100];
    sprintf(message, "MODE %s -b %s\n", channel, (char*)banned_user);
    write(sockfd, message, strlen(message));

}

void empty_barrel()
{
    int i;
    int bulletNumber = 0;
    for(i = 0; i < chamberNumber; i ++)
    {
        if (barrel[i] == 1)
        {
            barrel[i] = 0;
            bulletNumber ++;
        }
    }

    char message[50];
    sprintf(message, "\001ACTION %i round(s) fall on the floor.\001\n", bulletNumber);
    netprint(message);
}

void load_russian_roulette()
{
    barrel[rand()%chamberNumber] = 1;
    netprint("\001ACTION Reload the gun\001\n");
    //printf("\nBarrel state : %d %d %d %d %d %d\nActual barrel state :%d\n", barrel[0], barrel[1], barrel[2], barrel[3], barrel[4], barrel[5], roulette_actualChamber);


}

void weapon_swap(int desired_number)
{
    switch(desired_number)
    {
        case 5:
            netprint("\001ACTION empty, clean and store the revolver\001\n");
            empty_barrel();
            netprint("\001ACTION ready a Smith & Wesson Model 500 (5 chambers)\001\n");
            chamberNumber = 5;
            break;
        case 6:
            netprint("\001ACTION empty, clean and store the revolver\001\n");
            empty_barrel();
            netprint("\001ACTION ready a Mateba (6 chambers)\001\n");
            chamberNumber = 6;
            break;
        case 7:
            netprint("\001ACTION empty, clean and store the revolver\001\n");
            empty_barrel();
            netprint("\001ACTION ready a Nagant M1895 (7 chambers)\001\n");
            chamberNumber = 7;
            break;
        case 9:
            netprint("\001ACTION empty, clean and store the revolver\001\n");
            empty_barrel();
            netprint("\001ACTION ready a LeMat (9 chambers)\001\n");
            chamberNumber = 9;
            break;
        default:
            netprint("\001ACTION is unable to find the correct revolver\001\n");
            break;
    }
}

void roll_barrel()
{
    roulette_actualChamber = rand()%chamberNumber;
    netprint("\001ACTION Spins the barrel\001\n");
}

void fire_russian_roulette()
{
    if (barrel[roulette_actualChamber] == 1)
    {
        barrel[roulette_actualChamber] = 0;

        netprint("\001ACTION *BANG*\001\n");

        char message[100];
        sprintf(message, "MODE %s +b %s\n", channel, username);
        write(sockfd, message, strlen(message));
        sprintf(message, "KICK %s %s BANG\n", channel, username);
        write(sockfd, message, strlen(message));
        pthread_t threadReference;
        pthread_create(&threadReference, NULL, paused_unban, (void *) username);

    }
    else
    {
        netprint("\001ACTION *Click*\001\n");
    }

    roulette_actualChamber ++;

    if(roulette_actualChamber >= chamberNumber)
    {
        roulette_actualChamber = 0;
    }

}
