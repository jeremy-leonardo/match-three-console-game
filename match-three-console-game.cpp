
// Jeremy Leonardo - T068

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

const int HEART = 3;
const int CLOVER = 5;
const int SPADE = 6;
const int DIAMOND = 4;
const int MUSIC = 14;
const int MASK = 2;

char map[20][20];
int mapvalue[20][20];
long current_score = 0;
int current_progress = 0;
int temp_combo_count = 0;
int temp_removed_token_count = 0;
char keypress = NULL;
int obstacle_count = 0;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct pdata{
	char name[50];
	char pass[50];
	int diff;
	int speed;
}player_data;

void splashScreen(){
	puts("");
//	printf("                  - Jewel Quest - \n\n");
	printf("\n");
	
	printf("     ___                   _ _____                 _   \n"); Sleep(100);
	printf("    |_  |                 | |  _  |               | |  \n"); Sleep(100);
	printf("      | | _____      _____| | | | |_   _  ___  ___| |_ \n"); Sleep(100);
	printf("      | |/ _ \\ \\ /\\ / / _ \\ | | | | | | |/ _ \\/ __| __|\n"); Sleep(100);
	printf("  /\\__/ /  __/\\ V  V /  __/ \\ \\/' / |_| |  __/\\__ \\ |_ \n"); Sleep(100);
	printf("  \\____/ \\___| \\_/\\_/ \\___|_|\\_/\\_\\\\__,_|\\___||___/\\__|\n"); Sleep(100);
                                                     
    printf("\n");
             
    printf("                  _____ ___    __   ___  \n"); Sleep(50);
    printf("                 (_   _) _ \\  / /  /   \\ \n"); Sleep(50);
    printf("                   | || | | |/ /_  \\ O / \n"); Sleep(50);
    printf("                   | || | | | '_ \\ / _ \\ \n"); Sleep(50);
    printf("                   | || |_| | (_) | (_) )\n"); Sleep(50);
    printf("                   |_| \\___/ \\___/ \\___/    \n\n"); Sleep(50);
	                                   
									        
	printf("                 - By Jeremy Leonardo T068 - \n\n"); Sleep(50);
	printf("                Press SPACE to continue . . . \n\n\n"); 
	printf("          For Maximum Experience, use Legacy Console"); 
	
	do{
		keypress = getch();
	}while(keypress!=' ');
	
	system("cls");
	printf("\n\n\n");
	
	printf("                           Control\n");
	printf("                              W\n");
	printf("                              ^\n");
	printf("                          A < O > D\n");
	printf("                              v\n");
	printf("                              S\n\n"); Sleep(50);

	printf("                Press SPACE to continue . . . \n\n\n");
	
	do{
		keypress = getch();
	}while(keypress!=' ');
	
}

bool checkName(char inp_name[]){
	
	char name[50], pass[50];
	int diff, speed;
	
	FILE *re = fopen("player.txt","r");
	
	while(!feof(re)){
		fscanf(re,"%[^#]s",name);
		fscanf(re,"#");
		fscanf(re,"%[^#]s",pass);
		fscanf(re,"#");
		fscanf(re,"%d",&diff);
		fscanf(re,"#");
		fscanf(re,"%d",&speed);
		fscanf(re,"\n");
		if(strcmp(name,inp_name)==0){
			return true; // name exist
		}
	}
	if(feof(re)){
		return false; // name doesn't exist
	}
	
	fclose(re);
}

bool loadPlayerData(char inp_name[], char inp_pass[]){
	
	char name[50], pass[50];
	int diff, speed;
	
	FILE *re = fopen("player.txt","r");
	
	while(!feof(re)){
		fscanf(re,"%[^#]s",name);
		fscanf(re,"#");
		fscanf(re,"%[^#]s",pass);
		fscanf(re,"#");
		fscanf(re,"%d",&diff);
		fscanf(re,"#");
		fscanf(re,"%d",&speed);
		fscanf(re,"\n");
		if(strcmp(name,inp_name)==0 && strcmp(pass,inp_pass)==0){
			strcpy(player_data.name,name);
			strcpy(player_data.pass,pass);
			player_data.diff = diff;
			player_data.speed = speed;
			return true; // name exist
		}
	}
	if(feof(re)){
		return false; // name doesn't exist
	}
	
	fclose(re);
}

void savePlayerData(char inp_name[], char inp_pass[], int inp_diff, int inp_speed){
	
	FILE *wr = fopen("player.txt","a");
	
	fprintf(wr,"%s#%s#%d#%d\n",inp_name,inp_pass,inp_diff,inp_speed);
	
	fclose(wr);
	
}

void cursorTo(int column, int line){

    
	COORD coord;
    coord.X = column;
    coord.Y = line;

    SetConsoleCursorPosition(hConsole, coord);
}

void gameCursorTo(int column, int line){

    
	COORD coord;
    coord.X = column+6;
    coord.Y = line+4;

    SetConsoleCursorPosition(hConsole, coord);
}

bool initialMapCheck(){
	
	bool triplets_exist = false;
	
	// CHECK AND DELETE IF 3 IN A ROW EXIST
	int samecount=1;
	for(int i=0; i<15; i++){
		samecount=1;
		for(int j=0; j<14; j++){
			if(map[i][j]==map[i][j+1] && map[i][j]!='#' && map[i][j]!=' '){
				samecount++;
			}
			else if (samecount>=3){
				// CHANGE samecount NUMBER OF MAP CHAR BEFORE I J to OTHER
				int y = i;
				int x = j;
				for(int k=0; k<samecount; k++){
					map[y][x] = ' ';
					triplets_exist = true;
					x--;
				}
				
				samecount = 1;
			}
			else{
				samecount =1;
			}
			if (samecount>=3 && j==13){
				// CHANGE samecount NUMBER OF MAP CHAR BEFORE I J to OTHER
				int y = i;
				int x = j+1;
				for(int k=0; k<samecount; k++){
					map[y][x] = ' ';
					triplets_exist = true;
					x--;
				}
				samecount = 1;
			}
		}
	}
	
	// CHECK AND DELETE IF 3 IN A ROW EXIST
	samecount=1;
	for(int i=0; i<15; i++){
		samecount=1;
		for(int j=0; j<14; j++){
			if(map[j][i]==map[j+1][i] && map[j][i]!='#' && map[j][i]!=' '){
				samecount++;
			}
			else if (samecount>=3){
				
				//CHANGE samecount NUMBER OF MAP CHAR BEFORE I J to OTHER
				int y = j;
				int x = i;
				for(int k=0; k<samecount; k++){
					map[y][x] = ' ';
					triplets_exist = true;
					y--;
				}
				
				samecount = 1;
			}else{
				samecount =1;
			}
			if (samecount>=3 && j==13){
				//CHANGE samecount NUMBER OF MAP CHAR BEFORE I J to OTHER
				int y = j+1;
				int x = i;
				for(int k=0; k<samecount; k++){
					map[y][x] = ' ';
					triplets_exist = true;
					y--;
				}
			}
		}
	}
	return triplets_exist;
}

void loadMapData(){
	FILE *re = fopen("map.txt","r");
	for(int i=0; i<15; i++){
		fscanf(re,"%[^\n]\n",map[i]);
	}
	fscanf(re,"%d",&obstacle_count);
	fclose(re);
}

void initializeMap(){
	
	// RESET MAPVALUE
	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			mapvalue[i][j]=0;
		}
	}
	
	// LOAD MAP DATA FROM FILE
	loadMapData();
	
	// CHANGE '-' TO SYMBOLS (RANDOM)
	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			int rand_ch = rand()%player_data.diff;
			if(map[i][j]=='-'){
				if(rand_ch == 0) map[i][j]=HEART;
				else if(rand_ch == 1) map[i][j]=CLOVER;
				else if(rand_ch == 2) map[i][j]=SPADE;
				else if(rand_ch == 3) map[i][j]=DIAMOND;
				else if(rand_ch == 4) map[i][j]=MUSIC;
				else if(rand_ch == 5) map[i][j]=MASK;
			}
		}
	}
	
	bool triplet_exist = false;
	do{
		triplet_exist = initialMapCheck();
		for(int i=0; i<15; i++){
			for(int j=0; j<15; j++){
				int rand_ch = rand()%player_data.diff;
				if(map[i][j]==' '){
					if(rand_ch == 0) map[i][j]=HEART;
					else if(rand_ch == 1) map[i][j]=CLOVER;
					else if(rand_ch == 2) map[i][j]=SPADE;
					else if(rand_ch == 3) map[i][j]=DIAMOND;
					else if(rand_ch == 4) map[i][j]=MUSIC;
					else if(rand_ch == 5) map[i][j]=MASK;
				}
			}
		}
	}while(triplet_exist);
	
}

void swap(int x1, int y1, int x2, int y2){
	
	char temp = map[y1][x1];
	map[y1][x1] = map[y2][x2];
	map[y2][x2] = temp;
	
}

bool canSwap(){
	bool swappable = false;
	
	// CHECK AND DELETE IF 3 IN A ROW EXIST
	int samecount=1;
	for(int i=0; i<15; i++){
		samecount=1;
		for(int j=0; j<14; j++){
			if(map[i][j]==map[i][j+1] && map[i][j]!='#' && map[i][j]!=' '){
				samecount++;
			}
			else if (samecount>=3){
				// CHANGE samecount NUMBER OF MAP CHAR BEFORE I J to OTHER
				int y = i;
				int x = j;
				for(int k=0; k<samecount; k++){
					if(y+1>=0 && y+1<15 && map[y+1][x]=='#') map[y+1][x]=' ';
					if(y-1>=0 && y-1<15 && map[y-1][x]=='#') map[y-1][x]=' ';
					if(x+1>=0 && x+1<15 && map[y][x+1]=='#') map[y][x+1]=' ';
					if(x-1>=0 && x-1<15 && map[y][x-1]=='#') map[y][x-1]=' ';
					map[y][x] = ' ';
					if(mapvalue[y][x]==0) current_score += 50;
					mapvalue[y][x] = 1;
					swappable = true;
					x--;
					current_score++;
					temp_removed_token_count++;
				}
				temp_combo_count++;
				samecount = 1;
			}else{
				samecount =1;
			}
			if (samecount>=3 && j==13){
				// CHANGE samecount NUMBER OF MAP CHAR BEFORE I J to OTHER
				int y = i;
				int x = j+1;
				for(int k=0; k<samecount; k++){
					if(y+1>=0 && y+1<15 && map[y+1][x]=='#') map[y+1][x]=' ';
					if(y-1>=0 && y-1<15 && map[y-1][x]=='#') map[y-1][x]=' ';
					if(x+1>=0 && x+1<15 && map[y][x+1]=='#') map[y][x+1]=' ';
					if(x-1>=0 && x-1<15 && map[y][x-1]=='#') map[y][x-1]=' ';
					map[y][x] = ' ';
					if(mapvalue[y][x]==0) current_score += 50;
					mapvalue[y][x] = 1;
					swappable = true;
					x--;
					current_score++;
					temp_removed_token_count++;
				}
				temp_combo_count++;
			}
		}
	}
	
	// CHECK AND DELETE IF 3 IN A ROW EXIST
	samecount=1;
	for(int i=0; i<15; i++){
		samecount=1;
		for(int j=0; j<14; j++){
			if(map[j][i]==map[j+1][i] && map[j][i]!='#' && map[j][i]!=' '){
				samecount++;
			}
			else if (samecount>=3){
				
				//CHANGE samecount NUMBER OF MAP CHAR BEFORE I J to OTHER
				int y = j;
				int x = i;
				for(int k=0; k<samecount; k++){
					if(y+1>=0 && y+1<15 && map[y+1][x]=='#') map[y+1][x]=' ';
					if(y-1>=0 && y-1<15 && map[y-1][x]=='#') map[y-1][x]=' ';
					if(x+1>=0 && x+1<15 && map[y][x+1]=='#') map[y][x+1]=' ';
					if(x-1>=0 && x-1<15 && map[y][x-1]=='#') map[y][x-1]=' ';
					map[y][x] = ' ';
					if(mapvalue[y][x]==0) current_score += 50;
					mapvalue[y][x] = 1;
					swappable = true;
					y--;
					current_score++;
					temp_removed_token_count++;
				}
				temp_combo_count++;
				samecount = 1;
			}else{
				samecount =1;
			}
			if (samecount>=3 && j==13){
				// CHANGE samecount NUMBER OF MAP CHAR BEFORE I J to OTHER
				int y = i;
				int x = j+1;
				for(int k=0; k<samecount; k++){
					if(y+1>=0 && y+1<15 && map[y+1][x]=='#') map[y+1][x]=' ';
					if(y-1>=0 && y-1<15 && map[y-1][x]=='#') map[y-1][x]=' ';
					if(x+1>=0 && x+1<15 && map[y][x+1]=='#') map[y][x+1]=' ';
					if(x-1>=0 && x-1<15 && map[y][x-1]=='#') map[y][x-1]=' ';
					map[y][x] = ' ';
					if(mapvalue[y][x]==0) current_score += 50;
					mapvalue[y][x] = 1;
					swappable = true;
					x--;
					current_score++;
					temp_removed_token_count++;
				}
				temp_combo_count++;
			}
		}
	}
	return swappable;

}

void printMapAndGame(){
	
	system("cls"); puts("");
	printf("   Score: %ld   Progress:  %d%%\n\n",current_score,current_progress);
	printf("     ");
	for(int i=0; i<17; i++) printf("%c",219);
	puts("");
//		for(int i=0; i<15; i++) printf("     %c%s%c\n",219,map[i],219);
	int color;
	for(int i=0; i<15; i++){
		SetConsoleTextAttribute(hConsole, 7);
		printf("     %c",219);
		for(int j=0; j<15; j++){
			if(map[i][j] == HEART){
				color = 4;
				if(mapvalue[i][j]==1){
					color = 100;
				}
			} 
			else if(map[i][j] == CLOVER){
				color = 2;
				if(mapvalue[i][j]==1){
					color = 98;
				}
			} 
			else if(map[i][j] == SPADE){
				color = 1;
				if(mapvalue[i][j]==1){
					color = 97;
				}
			} 
			else if(map[i][j] == DIAMOND){
				color = 15;
				if(mapvalue[i][j]==1){
					color = 103;
				}
			}
			else if(map[i][j] == MUSIC){
				color = 13;
				if(mapvalue[i][j]==1){
					color = 101;
				}
			} 
			else if(map[i][j] == MASK){
				color = 11;
				if(mapvalue[i][j]==1){
					color = 107;
				}
			} 
			else if(map[i][j] == '#'){
				color = 7;
				if(mapvalue[i][j]==1){
					color = 110;
				}
			} 
			else if(map[i][j] == ' '){
				color = 7;
				if(mapvalue[i][j]==1){
					color = 110;
				}
			} 
			SetConsoleTextAttribute(hConsole, color);
			printf("%c",map[i][j]);
		}
		SetConsoleTextAttribute(hConsole, 7);
		printf("%c\n",219);
	}
	printf("     ");
	for(int i=0; i<17; i++) printf("%c",219);
}

bool fallDown(){
	bool fall = false;
	for(int i=0; i<15; i++){
		for(int j=0; j<14; j++){
			if((map[j][i]!='#' && map[j][i]!=' ')&& map[j+1][i]==' '){
				swap(i,j,i,j+1);
//				printf("\n%d,%d <-> %d,%d",i,j,i,j+1);
				fall = true;
			}
		}
	}
	return fall;
}

void regenerateTop(){
	for(int i=0; i<15; i++){
		if(map[0][i]==' '){
			
			int rand_ch = rand()%player_data.diff;
			if(rand_ch == 0) map[0][i]=HEART;
			else if(rand_ch == 1) map[0][i]=CLOVER;
			else if(rand_ch == 2) map[0][i]=SPADE;
			else if(rand_ch == 3) map[0][i]=DIAMOND;
			else if(rand_ch == 4) map[0][i]=MUSIC;
			else if(rand_ch == 5) map[0][i]=MASK;
			
		}
	}
}

void calculateProgress(){
	int gold_counter = 0;
	const float gold_mult = 2.25;
	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			if(mapvalue[i][j]==1){
				gold_counter++;
			}
		}
	}
	current_progress = (int)(gold_counter/gold_mult);
	
}

void startGame(){
	
	int gameCursorX = 0;	
	int gameCursorY = 0;	
	
	current_progress = 0;
	current_score = 0;
	temp_combo_count = 0;
	temp_removed_token_count = 0;
	
	initializeMap();
	
	// PLAY LOOP
	do{
		// PRINT MAP AND GAME
		printMapAndGame();
		
		// MOVE CURSOR
		do{
			keypress = getch();
			if(keypress=='w' && gameCursorY!=0) gameCursorY--;
			else if(keypress=='s' && gameCursorY!=14) gameCursorY++;
			else if(keypress=='a' && gameCursorX!=0) gameCursorX--;
			else if(keypress=='d' && gameCursorX!=14) gameCursorX++;
			gameCursorTo(gameCursorX,gameCursorY);
		}while(keypress != ' ' && keypress!='q');
		
		int temp_CursorX=-1;
		int temp_CursorY=-1;
		
		if(keypress == ' '){
			temp_CursorX = gameCursorX;
			temp_CursorY = gameCursorY;
			keypress = getch();
			if(keypress=='w' && gameCursorY!=0) gameCursorY--;
			else if(keypress=='s' && gameCursorY!=14) gameCursorY++;
			else if(keypress=='a' && gameCursorX!=0) gameCursorX--;
			else if(keypress=='d' && gameCursorX!=14) gameCursorX++;
			
			if(keypress!='q'){
				swap(temp_CursorX,temp_CursorY,gameCursorX,gameCursorY);
				if(!canSwap()){
					swap(temp_CursorX,temp_CursorY,gameCursorX,gameCursorY);
					gameCursorX = temp_CursorX;
					gameCursorY = temp_CursorY;
				} 
				else{				
					do{
						regenerateTop();
						calculateProgress();
						printMapAndGame();
						Sleep(player_data.speed);
					}while(fallDown() || canSwap());
				}
				current_score += temp_removed_token_count * temp_combo_count;
				temp_removed_token_count = 0;
				temp_combo_count = 0;
				if(current_progress==100){
					cursorTo(25,6);
					printf("You Win !");
					current_score += 5000;
					getch();
					keypress = 'q';
				}
			}
		}

	}while(keypress !='q');
	
	cursorTo(21,19);
	
}

void getNameInput(){
	
	char inp_name[50] = "";
	do{
		system("cls"); puts("");
		printf("  Jewel Quest\n");
		printf("  ===========\n\n");
		
		printf("  Input your name [4..12]:\n");
		printf("  >> ");
		
		scanf("%[^\n]s",inp_name); getchar();
		
		if(strlen(inp_name)<4){
			printf("\n    Error: Too short . . .");
			getch();
		}else if(strlen(inp_name)>12){
			printf("\n    Error: Too long . . .");
			getch();
		}
		
	}while(strlen(inp_name)<4 || strlen(inp_name)>12);
	
	strcpy(player_data.name,inp_name);
	
}

bool registerPlayer(){
	
	char inp_pass[50] = "";
	char reinp_pass[50] = "";
	
	// REGISTER PROMPT
		
	int want_to_register = 1;
	do{
		
		system("cls");
		puts("");
		printf("  Name haven't registered . . .\n");
		printf("  Do you want to register?\n\n");

		if(want_to_register == 1) printf("  >> Yes\n");
		else printf("     Yes\n");
		if(want_to_register == 0) printf("  >> No\n");
		else printf("     No\n");
		
		keypress = getch();
		
		if(keypress=='w'){
			want_to_register = 1;
		}else if(keypress=='s'){
			want_to_register = 0;
		}
		
		
	}while(keypress!=' ');
	if(want_to_register==0)return false;
	
	// GET inp_pass AND SAVE player_data TO FILE IF NAME NOT EXIST 
	if(want_to_register){
		
		do{
		
			// GET inp_pass
			do{
				system("cls"); puts("");
				printf("  Jewel Quest\n");
				printf("  ===========\n\n");
				
				printf("  Input your password [4..12]:\n");
				printf("  >> ");
				
				scanf("%[^\n]s",inp_pass); getchar();
				
				if(strlen(inp_pass)<4){
					printf("\n    Error: Too short . . .");
					getch();
				}else if(strlen(inp_pass)>12){
					printf("\n    Error: Too long . . .");
					getch();
				}
				
			}while(strlen(inp_pass)<4 || strlen(inp_pass)>12);
			
			
			
			// RE-INPUT PASS
			do{
				system("cls"); puts("");
				printf("  Jewel Quest\n");
				printf("  ===========\n\n");
				
				printf("  Re-Input your password [4..12]:\n");
				printf("  >> ");
				
				scanf("%[^\n]s",reinp_pass); getchar();
				
				if(strlen(reinp_pass)<4){
					printf("\n    Error: Too short . . .");
					getch();
				}else if(strlen(reinp_pass)>12){
					printf("\n    Error: Too long . . .");
					getch();
				}
				
			}while(strlen(reinp_pass)<4 || strlen(reinp_pass)>12);
			
		}while(strcmp(reinp_pass,inp_pass)!=0);
		
		
		// SAVE player_data TO TXT
		strcpy(player_data.pass,inp_pass);
		player_data.diff = 5;
		player_data.speed = 500;
		savePlayerData(player_data.name,player_data.pass,player_data.diff,player_data.speed);
		
		return true;	
	}
	return false;
}

bool getExistingPlayerPass(){
	
	bool pass_correct = false;
	char inp_pass[50] = "";
	
	do{
	
		do{
			system("cls"); puts("");
			printf("  Jewel Quest\n");
			printf("  ===========\n\n");
			
			printf("  Input your password [4..12]:\n");
			printf("  >> ");
			
			scanf("%[^\n]s",inp_pass); getchar();
			
			if(strlen(inp_pass)<4){
				printf("\n    Error: Too short . . .");
				getch();
			}else if(strlen(inp_pass)>12){
				printf("\n    Error: Too long . . .");
				getch();
			}
			
		}while(strlen(inp_pass)<4 || strlen(inp_pass)>12);
			
		pass_correct = loadPlayerData(player_data.name,inp_pass); 
		if(!pass_correct){
			printf("\n    Error: Incorrect Password . . .");
			getch();
			return false;
		}else{
			strcpy(player_data.pass,inp_pass);
			return true;
		}
		
	}while (!pass_correct);
}

void saveMapData(){
	FILE *wr = fopen("map.txt","w");
	for(int i=0; i<15; i++){
		fprintf(wr,"%s\n",map[i]);
	}
	fprintf(wr,"%d",obstacle_count);
	fclose(wr);
}

void floodFill(int x, int y){
	if(map[x][y]=='-')mapvalue[x][y] = 1;
	if(y+1<15 && mapvalue[x][y+1] == 0 && map[x][y+1] == '-') floodFill(x,y+1);
	if(y-1>=0 && mapvalue[x][y-1] == 0 && map[x][y-1] == '-') floodFill(x,y-1);
	if(x-1>=0 && mapvalue[x-1][y] == 0 && map[x-1][y] == '-') floodFill(x-1,y);
	if(x+1<15 && mapvalue[x+1][y] == 0 && map[x+1][y] == '-') floodFill(x+1,y);
}

bool floodFillMap(){
	
	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			mapvalue[i][j]=0;
		}
	}
	floodFill(0,0);
	floodFill(0,14);
	floodFill(14,0);
	floodFill(14,14);
	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			if(mapvalue[i][j]==0 && map[i][j]=='-'){
				return false;
			}
		}
	}
	return true;
}

void customizeMap(){
	
	loadMapData();
	int gameCursorY = 0;
	int gameCursorX = 0;
	
	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			mapvalue[i][j]=0;
		}
	}
	
	do{
		do{
			
			system("cls"); puts("");
			printf("     Jewel Quest\n     ===========\n");
			printf("     ");
			for(int i=0; i<17; i++) printf("%c",219);
			puts("");
			for(int i=0; i<15; i++){
				printf("     %c",219);
				for(int j=0; j<15; j++){
					if(map[i][j]=='-') printf("%c",' ');
					else printf("%c",map[i][j]);
				}
				printf("%c\n",219);
			}
			printf("     ");
			for(int i=0; i<17; i++) printf("%c",219);
			
			// MOVE CURSOR
			do{
				keypress = getch();
				if(keypress=='w' && gameCursorY!=0) gameCursorY--;
				else if(keypress=='s' && gameCursorY!=14) gameCursorY++;
				else if(keypress=='a' && gameCursorX!=0) gameCursorX--;
				else if(keypress=='d' && gameCursorX!=14) gameCursorX++;
				gameCursorTo(gameCursorX,gameCursorY);
			}while(keypress != ' ' && keypress!='q');
			if (keypress == ' ' ){
				if(map[gameCursorY][gameCursorX] == '-' && obstacle_count<15){
					map[gameCursorY][gameCursorX] = '#';
					obstacle_count++;
				}
				else if(map[gameCursorY][gameCursorX] == '#' && obstacle_count>=0){
					map[gameCursorY][gameCursorX] = '-';
					obstacle_count--;
				}
				else if(obstacle_count==15){
					cursorTo(25,6);
					SetConsoleTextAttribute(hConsole, 4);
					printf("There is no more obstacle");
					SetConsoleTextAttribute(hConsole, 7);
					getch();
					gameCursorTo(gameCursorX,gameCursorY);
				}
			}
			
			if(keypress=='q'){
				if(floodFillMap()==false){
					system("cls"); puts("");
					printf("     Jewel Quest\n     ===========\n");
					printf("     ");
					for(int i=0; i<17; i++) printf("%c",219);
					puts("");
					for(int i=0; i<15; i++){
						printf("     %c",219);
						for(int j=0; j<15; j++){
							if(map[i][j]=='-' && mapvalue[i][j]==0){
								printf("%c",' ');
							} 
							else if(map[i][j]=='-' && mapvalue[i][j]==1) {
								SetConsoleTextAttribute(hConsole, 96);
								printf("%c",' ');
								SetConsoleTextAttribute(hConsole, 7);
							}
							else printf("%c",map[i][j]);
						}
						printf("%c\n",219);
					}
					printf("     ");
					for(int i=0; i<17; i++) printf("%c",219);
					
					cursorTo(25,6);
					SetConsoleTextAttribute(hConsole, 4);
					printf("Flood Fill failed . . . ");
					SetConsoleTextAttribute(hConsole, 7);
					getch();
					gameCursorTo(gameCursorX,gameCursorY);
				}
			}
			
		}while(keypress!='q');
	
	}while(!floodFillMap());
	saveMapData();
	
}

void highscore(){
	char temp_name[100] = "";
	long temp_score = 0;
	FILE *re = fopen("highscores.txt","r");
	
	system("cls"); puts("");
	printf("     Jewel Quest\n     ===========\n");
	if(player_data.diff==4) printf("                       EASY\n");
	else if(player_data.diff==5)	printf("                      MEDIUM\n");
	else if(player_data.diff==6)	printf("                       HARD\n");
	printf("     --------------------------------------\n");
	printf("     | No | %-20s | %-6s |\n","Name","Score");
	printf("     --------------------------------------\n");
	if(player_data.diff==4){
		for(int i=0; i<10; i++){
			fscanf(re,"%[^#]#%ld\n",temp_name,&temp_score);
			printf("     | %2d | %-20s | %-6ld |\n",i+1,temp_name,temp_score);
		}
	}
	else if(player_data.diff==5){
		for(int i=0; i<10; i++){
			fscanf(re,"%[^#]#%ld\n",temp_name,&temp_score);
		}
		for(int i=0; i<10; i++){
			fscanf(re,"%[^#]#%ld\n",temp_name,&temp_score);
			printf("     | %2d | %-20s | %-6ld |\n",i+1,temp_name,temp_score);
		}
	}
	else if(player_data.diff==6){
		for(int i=0; i<10; i++){
			fscanf(re,"%[^#]#%ld\n",temp_name,&temp_score);
		}
		for(int i=0; i<10; i++){
			fscanf(re,"%[^#]#%ld\n",temp_name,&temp_score);
		}
		for(int i=0; i<10; i++){
			fscanf(re,"%[^#]#%ld\n",temp_name,&temp_score);
			printf("     | %2d | %-20s | %-6ld |\n",i+1,temp_name,temp_score);
		}
	}
	printf("     --------------------------------------\n");
	fclose(re);
	getch();
}

void startMenu(){
	int chosen_start_menu = 1;
		
	do{
		
		do{
			
			system("cls"); puts("");
			printf("  Jewel Quest\n");
			printf("  ===========\n\n");
	
			if(chosen_start_menu == 1) printf("  >> Start Game\n");
			else printf("     Start Game\n");
			if(chosen_start_menu == 2) printf("  >> Customize Map\n");
			else printf("     Customize Map\n");
			if(chosen_start_menu == 3) printf("  >> High Score\n");
			else printf("     High Score\n");
			if(chosen_start_menu == 4) printf("  >> Return to Title\n");
			else printf("     Return to Title\n");
			
			keypress = getch();
			
			if(keypress=='w' && chosen_start_menu!=1){
				chosen_start_menu--;
			}else if(keypress=='s' && chosen_start_menu!=4){
				chosen_start_menu++;
			}
			
		}while(keypress!=' ');
		
		switch(chosen_start_menu){
			case 1:
				startGame();
				break;
			case 2:
				customizeMap();
				break;
			case 3:
				highscore();
				break;
		}
		
	}while(chosen_start_menu != 4);
			
}

void rules(){
	do{
		system("cls"); puts("");
		printf("  Jewel Quest\n");
		printf("  ===========\n");
		puts("");
		puts("");
		printf("  \"Truth, like gold, is to be obtained not by its growth,\n");
		printf("        but by washing away from it all that is not gold.\"\n");
		puts("");
		puts("");
		printf("                                            - Leo Tolstoy\n");
		puts("");
		puts("");
//		printf("                                               Page 1 of 8 >\n");
		
		keypress = getch();
		
	}while(keypress!=' ');
	
}

void options(){
	
	int speed_opt = player_data.speed;
	int diff_opt = player_data.diff;
	int chosen = 1;
	
	do{
		
		system("cls"); puts("");
		printf("  Jewel Quest\n");
		printf("  ===========\n");
		puts("");
		if(chosen==1 && speed_opt==250) printf("  >> Speed      : <  Fast  >\n");
		else if(chosen==1 && speed_opt==500) printf("  >> Speed      : < Normal >\n");
		else if(chosen==1 && speed_opt==750) printf("  >> Speed      : <  Slow  >\n");
		else if(chosen!=1 && speed_opt==250) printf("     Speed      : <  Fast  >\n");
		else if(chosen!=1 && speed_opt==500) printf("     Speed      : < Normal >\n");
		else if(chosen!=1 && speed_opt==750) printf("     Speed      : <  Slow  >\n");
		if(chosen==2 && diff_opt==4) printf("  >> Difficulty : <  Easy  >\n");
		else if(chosen==2 && diff_opt==5) printf("  >> Difficulty : < Medium >\n");
		else if(chosen==2 && diff_opt==6) printf("  >> Difficulty : <  Hard  >\n");
		else if(chosen!=2 && diff_opt==4) printf("     Difficulty : <  Easy  >\n");
		else if(chosen!=2 && diff_opt==5) printf("     Difficulty : < Medium >\n");
		else if(chosen!=2 && diff_opt==6) printf("     Difficulty : <  Hard  >\n");
		if(chosen==3) printf("  >> Return to Title\n");
		else if(chosen!=3) printf("     Return to Title\n");
		
		keypress = getch();
		
		
		if(keypress=='a' && chosen==1 && speed_opt!=250){
			speed_opt -= 250;
		}
		else if(keypress=='d' && chosen==1 && speed_opt!=750){
			speed_opt += 250;
		}
		else if(keypress=='a' && chosen==2 && diff_opt!=4){
			diff_opt --;
		}
		else if(keypress=='d' && chosen==2 && diff_opt!=6){
			diff_opt ++;
		}
		else if(keypress=='w' && chosen!=1){
			chosen--;
		}
		else if(keypress=='s' && chosen!=3){
			chosen++;
		}
		
	}while(keypress!=' ' || chosen!=3);
	
	player_data.diff = diff_opt;
	player_data.speed = speed_opt;
	
	// REPLACE DIFF AND SPEED
	pdata temp[200];
	
	FILE *plr = fopen("player.txt","r");
	int index = 0;
	while(!feof(plr)){
		fscanf(plr,"%[^#]#%[^#]#%d#%d\n",temp[index].name,temp[index].pass,&temp[index].diff,&temp[index].speed);
		index++;
	}
	fclose(plr);
	
	FILE *plw = fopen("player.txt","w");
	int i = 0;
	while(strcmp(temp[i].name,player_data.name)!=0){
		fprintf(plw,"%s#%s#%d#%d\n",temp[i].name,temp[i].pass,temp[i].diff,temp[i].speed);
		i++;
	}
	fprintf(plw,"%s#%s#%d#%d\n",temp[i].name,temp[i].pass,player_data.diff,player_data.speed);
	i++;
	while(i<index){
		fprintf(plw,"%s#%s#%d#%d\n",temp[i].name,temp[i].pass,temp[i].diff,temp[i].speed);
		i++;
	}
	fclose(plw);
		
}

void mainMenu(){
	
	int chosen_main_menu = 1;
	do{
		
		do{
			
			system("cls"); puts("");
			printf("  Jewel Quest\n");
			printf("  ===========\n\n");
			
			if(chosen_main_menu == 1) printf("  >> Start\n");
			else printf("     Start\n");
			if(chosen_main_menu == 2) printf("  >> Options\n");
			else printf("     Options\n");
			if(chosen_main_menu == 3) printf("  >> Rules\n");
			else printf("     Rules\n");
			if(chosen_main_menu == 4) printf("  >> Quit\n");
			else printf("     Quit\n");
			
			keypress = getch();
			
			if(keypress=='w' && chosen_main_menu!=1){
				chosen_main_menu--;
			}else if(keypress=='s' && chosen_main_menu!=4){
				chosen_main_menu++;
			}
			
		}while(keypress!=' ');
		
		switch(chosen_main_menu){
			case 1:
				startMenu();
				break;
			case 2:
				options();
				break;
			case 3:
				rules();
				break;
		}
		
	}while(chosen_main_menu!=4);
	
}

int main(){
	
	srand(time(NULL));
	
	splashScreen();
	bool registered = false;
	bool success_login = false;
	do{
		getNameInput();
		bool name_exist = checkName(player_data.name);
		if(!name_exist){
			registered = registerPlayer();
		}
		else if(name_exist){
			success_login = getExistingPlayerPass();
		}
	}while(!registered && !success_login);
	
	mainMenu();
	
	return 0;
}

