#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#define DELAY 1					
#define RATE 100

enum range {					
	easy = 100,
	medium = 200,
	hard = 300,
	step = 25,				
	top = 10					
};
	
enum level{
	zero = 0,						
	first = 1,
	second = 2,
	third = 3
};

struct person					
{	
    char name[16];
    int points;
};

struct interface{
	char translateTask[RATE];
	char answer[RATE];
	char correct[RATE];
	char incorrect[RATE];
	char correctAnswer[RATE];
	char fault[RATE];
	char currentScore[RATE];
	char congratulations[RATE];
	char anykey[RATE];
	char thankyou[RATE];
	char originalSentence[RATE];
	char replaceTask[RATE];
	char scorePassGame[RATE];
	char scoreboardPrint[RATE];
	char enterName[RATE];
	char totalPlayer[RATE];
	char anykeyMenu[RATE];
	char scoreboardScore[RATE];
	char sorryFound[RATE];
	char startGame[RATE];
	char scoreboard[RATE];
	char exit[RATE];
	char choice[RATE];
	char goodbye[RATE];
	char errorTryAgain[RATE];
	char back[RATE];
};

typedef struct interface Interface;

typedef struct person Person;

void languageChoiceMenu();
void timeDelay();  																				
void selectMenu(Interface language, char *translates, char *sentences, char *origSentences); 				
void toNextLevel(int score, int level, Interface language, char *translates, char *sentences, char *origSentences); 															
void firstLevel(int score, Interface language, char *translates, char *sentences, char *origSentences); 																
void secondLevel(int score, Interface language, char *translates, char *sentences, char *origSentences);												
void showScoreBoard(int score, int level, Interface language);										
void WriteBinFile(char *FileName, Person person);													
Person *ReadFile(char *FileName, int *fileSize);													
Interface fillStructure(char *fileName);												
void SortScoreboard(Person *players, int size);														
void PrintScoreBoard(Person *players, int size, Interface language);								
void getPositionFromBoard(Person *players, int size, int score, Interface language);				
void fillArray(FILE *, char words[][30], char translate[][30], int size);							
int translateLvl(char words[][30], char translate[][30], int size, int *array, Interface language, int score);	
int replaceLvl(FILE *, FILE *, int array[], int score, int i, size_t SIZE, Interface language, char *sentences, char *origSentences);		
char *returnSentence(int i, char *name);															
char *str_replace(char *orig, char *rep, char *with);												
void genRandom( int arr_size, int *parr, int range_min, int range_max );							
size_t countLines(FILE *);																			

int main(){
	
	SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
	
	languageChoiceMenu();
	
	return 0;
}

void languageChoiceMenu(){
	
	Interface language;
	
	char choice;
	system("cls");
	printf("Виберіть мову, яку би ви хотіли вивчати:\n");
	printf("Англійська(1)\n");
	printf("Іспанська(2)\n");
	printf("Німецька(3)\n");
	printf("Ваш вибір:");
	choice = getch();
	switch(choice){
		case '1':{
			char *fileName = "english/englishInterface.txt";
			char *translates = "english/translates.txt";
			char *sentences = "english/sentences.txt";
			char *origSentences = "english/sentences(ukr).txt";
			Interface language;
			language = fillStructure(fileName);
			selectMenu(language, translates, sentences, origSentences);
			break;
		}
		case '2':{
			char *fileName = "spanish/spanishInterface.txt";
			char *translates = "spanish/translates.txt";
			char *sentences = "spanish/sentences.txt";
			char *origSentences = "spanish/sentences(ukr).txt";
			Interface language;
			language = fillStructure(fileName);
			selectMenu(language, translates, sentences, origSentences);
			break;
		}
		case '3':{
			char *fileName = "germany/germanyInterface.txt";
			char *translates = "germany/translates.txt";
			char *sentences = "germany/sentences.txt";
			char *origSentences = "germany/sentences(ukr).txt";
			Interface language;
			language = fillStructure(fileName);
			selectMenu(language, translates, sentences, origSentences);
			break;
		}
		default:{
			printf("Помилка спробуйте ще раз");
			languageChoiceMenu();
			break;
		}
	}

}

void selectMenu(Interface language, char *translates, char *sentences, char *origSentences){
	int score = 0, level = zero;
	char choice;
	system("cls");
	printf(language.startGame);
	printf("\n");
	printf(language.scoreboard);
	printf("\n");
	printf(language.exit);
	printf("\n");
	printf(language.back);
	printf("\n");
	
	printf(language.choice);
	choice = getch();

	switch(choice){
		case '1': {
			firstLevel(score, language, translates, sentences, origSentences);
		}
		case '2': {
			toNextLevel(score, level, language, translates, sentences, origSentences);
			break;
		}
		case '3':{
			printf(language.goodbye);
			exit(0);
			break;
		}
//		case '5':{
//			score = 200;
//			secondLevel(score, language, translates, sentences, origSentences);
//			break;
//		}
		case '4':{
			languageChoiceMenu();
			break;
		}
		default:{
			printf(language.errorTryAgain);
			selectMenu(language, translates, sentences, origSentences);
			break;
		}
	}	
	
}

void toNextLevel(int score, int level, Interface language, char *translates, char *sentences, char *origSentences){
	
	switch(level){
		case zero:
			if(score == 0){
				showScoreBoard(score, level, language);
				selectMenu(language, translates, sentences, origSentences);
			}
			else printf("Error.");
		case first:
			if(score<easy) {
				showScoreBoard(score, level, language);
				selectMenu(language, translates, sentences, origSentences);
			}
			else {
				firstLevel(score, language, translates, sentences, origSentences);
			} 			 
		case second:
			if(score<medium) {
				showScoreBoard(score, level, language);
				selectMenu(language, translates, sentences, origSentences);
			}
			else secondLevel(score, language, translates, sentences, origSentences);
		
		case third:
			if(score<hard) {
				showScoreBoard(score, level, language);
				selectMenu(language, translates, sentences, origSentences);
			}
			else showScoreBoard(score, level, language);  //level 4
	}
}

void firstLevel(int score, Interface language, char *translates, char *sentences, char *origSentences){

	FILE *fp;
	fp = fopen (translates, "r");
    if(fp == NULL) {
		printf("No such file or directory.");
	}
    int size = countLines(fp);
    fclose(fp);
    
    char words[size][30];
    char translate[size][30];
    int randomNums[size], minRange = 1, maxRange = size/2;
    
    genRandom(size/2, randomNums, minRange, maxRange);
    
    fp = fopen (translates, "r");
    if(fp == NULL) {
		printf("No such file or directory.");
	}
	
    fillArray(fp, words, translate, size);
    fclose(fp);
    
    if (score < 100)
	{
    	score = translateLvl(words, translate, size, randomNums, language, score);
 		toNextLevel(score, first, language, translates, sentences, origSentences);
	}
	else
	{
		score = translateLvl(translate, words, size, randomNums, language, score);
 		toNextLevel(score, second, language, translates, sentences, origSentences);
	}
	
}

int translateLvl(char words[][30], char translate[][30], int size, int *array, Interface language, int score){
	int i = 1, j = 0, key;
	char answer[30];
	system("cls");
	int range;
	if (score == 0) {
		range = 100;
	}
	else{
		range = 200;
	}
    while(score < range){
    	printf(language.translateTask, words[array[j]]);
    	printf("\n");
    	printf(language.answer);
    	scanf("%s", &answer);
    	if(strcmp (answer, translate[array[j]])==0) {
    		score += step;
    		printf(language.correct);
    		
		}
		else{
			printf(language.incorrect);
			printf("\n");
			printf(language.correctAnswer, translate[array[j]]);
		}
		i++;
		timeDelay();
		if(i>size/2) {
    		printf(language.fault);
    		printf("\n");
    		timeDelay();
    		break;
		}
		if(score < range) printf(language.currentScore, score, easy);
		if(score >= range) {
			printf(language.congratulations);
			printf("\n");
			sleep(1);
			timeDelay();
			break;
		}
		timeDelay();
    	printf(language.anykey);
    	printf("\n");
    	key = getch();
    	system("cls");
    	if(key == 27) {
    		printf(language.thankyou); 
    		timeDelay();
			break;
		}
    	j++;
	}
	
	return score;
}

void fillArray(FILE *fp, char words[][30], char translate[][30], int size){

	int i,j = 1,k = 1;
    
    for(i=1;i<=size*2;i++){
		if(i%2 != 0){
			fscanf(fp, "%s", words[j]);
			j++;
		}
		if(i%2 != 0){
			fscanf(fp, "%s", translate[k]);
			k++;
		}
		i++;
	}

}

void secondLevel(int score, Interface language, char *translates, char *sentences, char *origSentences){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); 
	
	FILE *fp = fopen(sentences, "r");
	if(fp == NULL) {
		printf("No such file or directory.");
	}
	FILE *fp_ukr = fopen(origSentences, "r");
	if(fp_ukr == NULL) {
		printf("No such file or directory.");
	}
	int SIZE = countLines(fp);
	
	SIZE = SIZE - 1;
	
	int randomNums[SIZE], minRange = 1, maxRange = SIZE;
	int *nums_p = randomNums;
    genRandom(SIZE, nums_p, minRange, maxRange);
	int j = 0, i = 2;

	score = replaceLvl(fp, fp_ukr, randomNums, score, i, SIZE, language, sentences, origSentences);
	fclose(fp);
	fclose(fp_ukr);

	toNextLevel(score,third, language, translates, sentences, origSentences);
}

int replaceLvl(FILE *fp, FILE *fp_ukr, int array[], int score, int i, size_t SIZE, Interface language, char *sentences, char *origSentences){
	
	char answer[10];
	int count = 1, letterCount = 0;
	system("cls");
	while(score < hard){
		printf(language.originalSentence);
		char *ukrString = returnSentence(array[i-2], origSentences);
		puts (ukrString);
		free (ukrString);
		printf(language.replaceTask);
	
		char *string = returnSentence(array[i-2], sentences);
	
		char *rep[] = {"a","b","c","d","e","f","g","h","i","k","l","m","n","o","p","r","q","s","t","u","v","w","x","y","z"};
		char *with = "_";
		while(1){
			srand(time(NULL));	
			letterCount = rand()%25;
			if(puts(str_replace(string, rep[letterCount], with))==0) break;
			else continue;
			letterCount++;
		}
		printf (language.answer);
		scanf("%s", &answer);
		
		int j;
		
		for(j=0; j<sizeof(answer)-1; j++)
		{
   			if(answer[j]>'A' && answer[j]<'Z') answer[j]+='z'-'Z';
    		if(answer[j]>'А' && answer[j]<'Я') answer[j]+='я'-'Я';
		}
		
		if(strcmp(answer,rep[letterCount]) == 0) {
			printf(language.correct);
			score += step; 
		}	
		else {
			printf(language.incorrect);
			printf(language.correctAnswer, rep[letterCount]);
		}
		count++;
		timeDelay();
		if(count>SIZE) {
			printf(language.fault);
			timeDelay();
			break;
		}
		if(score < hard) printf(language.scorePassGame, score, hard);
		if(score >= hard) {
			printf(language.congratulations);
			sleep(1);
			timeDelay();
			break;
		}
		timeDelay();
		printf(language.anykey);
		char key;
		key = getch();
		system("cls");
		if(key == 27) {
    		printf(language.thankyou); 
			return score;
		}
		i++;
	}

	return score;
}

char *returnSentence (int i, char *name){
	FILE* filePointer = fopen (name, "r");
    char sentences[256][256];
    char* pointer;
    pointer = sentences[i-1];
 	int j;

    while(!feof(filePointer))
    {
    	fscanf(filePointer, " %[^\n]", sentences[j]);
//        fgets(sentences[j], 100, filePointer);
        j++;
    }
    
    char* s = malloc(strlen(pointer)+1);
    strcpy(s,pointer);
	fclose(filePointer);
 	return s;
}

char *str_replace(char *orig, char *rep, char *with) {
    char *result; 
    char *ins;    
    char *tmp;    
    int len_rep;  
    int len_with; 
    int len_front; 
    int count;    

    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; 
    if (!with)
        with = "";
    len_with = strlen(with);

    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }
	if(count==0) return 0;
    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; 
    }
    strcpy(tmp, orig);

    return result;
}

void WriteBinFile(char *FileName, Person person){
	
	FILE *fp = fopen(FileName, "ab");
	
	if (!fp)
    {
        perror("Error opening the file. \n");
        exit(EXIT_FAILURE);
    }
	
	fwrite(&person, sizeof(Person), 1,fp);
	
	fclose(fp);
}

Person *ReadFile(char *FileName, int *fileSize){
	
	int i = 0, size = 0;
	FILE *fp = fopen(FileName, "rb");
	
	if (!fp)
    {
        perror("Error opening the file. \n");
        exit(EXIT_FAILURE);
    }
	
	Person *players = malloc(sizeof(Person)*100);
	
	while (1) {
    	fread(&players[i], sizeof(Person), 1, fp);
    	if(feof(fp)) {
      	break;
    	}
//    	printf("Name: %s\n", players[i].name);
//		printf("Points: %i\n", players[i].points);
		i++;
		size++;
  	}
  	*fileSize = size;
	fclose(fp);
	return players;
}

void SortScoreboard(Person *players, int size){
	
	int i=0,j=0;
	bool didSwap;
	Person temp;
	
	do{
		didSwap = false;
		for(i = 0; i <size-1; i++)
		{
			if(players[i].points < players[i+1].points)
			{
				temp = players[i];
				players[i] = players[i+1];
				players[i+1] = temp;
				didSwap = true;
			}
		}
	}while(didSwap);
	
}

void PrintScoreBoard(Person *players, int size, Interface language){
	int i;
	
	for(i=0;i<top && i<size;i++){
		printf("\n");
		printf(language.scoreboardPrint, i+1,players[i].name, players[i].points);
		printf("\n");
	}
}

void showScoreBoard(int score, int level, Interface language){
	
	char *FileName = "person.dat";
	Person *person = malloc(sizeof(Person)*100);
	char name[25];
	system("cls");
	if(level != zero){
		printf(language.enterName);
		scanf("%s", &name);
		Person writeTemp;
		writeTemp.points = score;
		strcpy(writeTemp.name,name);
		WriteBinFile(FileName, writeTemp);
		printf("\n");
	}
	int *size = malloc(sizeof(int)*1);
	person = ReadFile(FileName, size);

	printf(language.totalPlayer, *size);
	SortScoreboard(person, *size);
	
	if(level != zero){
		getPositionFromBoard(person, *size, score, language);
	}
	printf("\n");
    PrintScoreBoard(person, *size, language);
    printf("\n");
    sleep(2);
    printf(language.anykeyMenu);
    fflush(stdin);
    getch();
    system("cls");
    free(person);
}

void getPositionFromBoard(Person *players, int size, int score, Interface language){
	
	int i,flag;
	
	for(i=0; i<size; i++)
	{	
		if(players[i].points==score)
		{
			flag = 1;
			break;
		}
	}
	
	int count,j=0;
	for(count=0;count<size;count++)
	{
		if(players[count].points==score) j++;
	}
	printf("\n");
	if(flag == 1)
  	{
  		printf("\n");
  		printf(language.scoreboardScore, score, i + j);

	}
	else
	{
		printf("\n");
		printf(language.sorryFound, score);

	}
}

void timeDelay(){
	sleep(DELAY);
	system("cls");
}

size_t countLines(FILE *fp) {

   size_t count = 0;

   while(! feof(fp) && !ferror(fp)) {
         fscanf(fp, "%*[^\n]%*c");
         count++;
   }
   if (ferror(fp))
        printf("Error of reading.\n");

   return count;
}

void genRandom( int arr_size, int *parr, int range_min, int range_max ) {
	
	srand( time( NULL ) );
	int i, arr2_size, index, range_width;
	int *parr2= NULL;
 
 
/* Check arguments */
	range_width= range_max-range_min+1;
	if ( range_width<1 || arr_size<0 || arr_size>range_width ) {
    	    fprintf( stderr, "gen_random_uniq(): Invalid arguments\n" ); exit( 1 );
	}
	if ( arr_size == 0 ) { return; }
 
 
/* Alloc */
	parr2= (int*)malloc( range_width*sizeof(int) );
	if ( parr2 == NULL ) {
		fprintf( stderr, "gen_random_uniq(): No enough memory\n" ); exit( 1 ); 
	}
 
/* Init */
	for ( i= 0; i<range_width; i++ ) {
    	parr2[i]= range_min+i;
	}
 
/* Loop */
	arr2_size= range_width;
	for ( i= 0; i<arr_size; i++ ) {
    	index= rand()%arr2_size;
   		parr[i]= parr2[index];
    	arr2_size--;
    	parr2[index]= parr2[arr2_size];
	}
 
/* Free */
	if ( parr2 != NULL ) { free( parr2 ); parr2= NULL; }
 
} 

Interface fillStructure(char *fileName){
	
	Interface language;
	
	strcpy(language.translateTask, returnSentence(1, fileName));
	strcpy(language.answer, returnSentence(2, fileName));
	strcpy(language.correct, returnSentence(3, fileName));
	strcpy(language.incorrect, returnSentence(4, fileName));
	strcpy(language.correctAnswer, returnSentence(5, fileName));
	strcpy(language.fault, returnSentence(6, fileName));
	strcpy(language.currentScore, returnSentence(7, fileName));
	strcpy(language.congratulations, returnSentence(8, fileName));
	strcpy(language.anykey, returnSentence(9, fileName));
	strcpy(language.thankyou, returnSentence(10, fileName));
	strcpy(language.originalSentence, returnSentence(11, fileName));
	strcpy(language.replaceTask, returnSentence(12, fileName));
	strcpy(language.scorePassGame, returnSentence(13, fileName));
	strcpy(language.scoreboardPrint, returnSentence(14, fileName));
	strcpy(language.enterName, returnSentence(15, fileName));
	strcpy(language.totalPlayer, returnSentence(16, fileName));
	strcpy(language.anykeyMenu, returnSentence(17, fileName));
	strcpy(language.scoreboardScore, returnSentence(18, fileName));
	strcpy(language.sorryFound, returnSentence(19, fileName));
	strcpy(language.startGame, returnSentence(20, fileName));
	strcpy(language.scoreboard, returnSentence(21, fileName));
	strcpy(language.exit, returnSentence(22, fileName));
	strcpy(language.choice, returnSentence(23, fileName));
	strcpy(language.goodbye, returnSentence(24, fileName));
	strcpy(language.errorTryAgain, returnSentence(25, fileName));
	strcpy(language.back, returnSentence(26, fileName));

	return language;
}

