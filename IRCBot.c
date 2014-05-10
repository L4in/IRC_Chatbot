/***
 *	TODO :
 *	- personnaliser les messages
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/***
 * 
***/
void answerSomething(char *string) {
	printf("%s\n", string);
}

/***
 * 
***/
void answerHello() {
	printf("Hello !\n");
}

/***
 * 
***/
void answerInsult(char *string) {
	printf("%s\n", string);
}

/***
 * 
***/
void timeToDoSomething(int hour) {
	if((hour > 12) && (hour < 13))		printf("I'm starving ! bye\n"); // Lunch
	else if((hour > 20) && (hour < 21))	printf("I'm starving ! bye\n"); // Dinner
	else return ; // Default case

	exit(-1); // Exit chat
}

/***
 * 
***/
void getTime(int size, char format[], time_t timeInit, struct tm date) {
	// On récupère la date et l'heure actuelles.
	time(&timeInit);
	date = *localtime(&timeInit);

	// On remplit la chaîne avec le format choisi, puis on l'affiche.
	strftime(format, size, "We're %A the %d %B %Y and it's %X.\n", &date);
	timeToDoSomething(date.tm_hour);
}

/***
 * 
***/
void writeLog()  {


}

int main() {
	char format[128] = {0};
	time_t timeInit = NULL;
	struct tm date;

	printf("HelloWorld !!!\n");

	answerHello();
	answerSomething("Merdeuh!");
	printf("PAF1\n");
	getTime(128, format, timeInit, date);
	printf("PAF2\n");
	printf("%s\n", format);

	return 0;
}
