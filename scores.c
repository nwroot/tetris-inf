#include "scores.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int score;
	char user_name[50];

}score;

void writeScore(score *pts){
	int score = pts->score;
	char name[50];
	for(int i=0; i<50; ++i){
		name[i] = pts->user_name[i];
	}

	FILE *fptr;
	fptr = fopen("/home/usuario/tetris-inf/puntajes.txt","r+");
	
	char info[10][50];
	for(int i=0; i<10; ++i){
		for(int j=0; j<50;++j){
			info[i][j] = 0;
		}
	}
	char *fil[10];
	for(int i=0; i<10; ++i){
		fil[i] = &info[i][0];
	}
	for(int i=0; i<10; ++i){
		fgets(fil[i], 50, fptr);
	}

	char info_names[10][50];
	

	char info_scores[10][50];

	for(int i=0; i<10; ++i){
		for(int j=0; j<50;++j){
			info_scores[i][j] = 0;
			info_names[i][j] = 0;
		}
	}

	for(int i=0; i<10; ++i){
		for(int j=0; j<50; ++j){
			if(info[i][j]>=48 && info[i][j]<=57){
				info_scores[i][j] = info[i][j]; 
			}else{
				info_names[i][j] = info[i][j];
			}
		}
	}

	int info_numscores[10];
	char *ptscores[10];
	for(int i=0; i<10; ++i){
		ptscores[i] = &info_scores[i][0];
	}
	for(int i=0; i<10; ++i){
		info_numscores[i] = atoi(ptscores[i]);
	}

	//TEST
	for(int i=0; i<10; ++i){
		for(int j=0; j<50; ++j){
			printf("%c", info_names[i][j]);
		}
	}
	

	for(int i=0; i<10; ++i){
		int posmenor = i;
		for(int j=i+1; j<10;++j){
			if(info_numscores[j]<info_numscores[posmenor]){
				posmenor = j;
			}
		}
		int s = info_numscores[posmenor];
		char m[50];
		for(int k=0; k<50; ++k){
			m[k] = info_names[posmenor][k];
		}

		info_numscores[posmenor] = info_numscores[i];
		for(int k=0; k<50; ++k){
			info_names[posmenor][k] = info_names[i][k];
		}

		info_numscores[i] = s;
		for(int k=0; k<50; ++k){
			info_names[i][k] = m[k];
		}
	}


	fclose(fptr);

	if(info_numscores[0]<score){
		info_numscores[0] = score;
		for(int i=0; i<10; ++i){
			info_names[0][i] = name[i];
		}
	}


	for(int i=0; i<10; ++i){
		int posmenor = i;
		for(int j=i+1; j<10;++j){
			if(info_numscores[j]<info_numscores[posmenor]){
				posmenor = j;
			}
		}
		int s = info_numscores[posmenor];
		char m[50];
		for(int k=0; k<50; ++k){
			m[k] = info_names[posmenor][k];
		}

		info_numscores[posmenor] = info_numscores[i];
		for(int k=0; k<50; ++k){
			info_names[posmenor][k] = info_names[i][k];
		}

		info_numscores[i] = s;
		for(int k=0; k<50; ++k){
			info_names[i][k] = m[k];
		}
	}

	char *pnames[10];
	for(int i=0; i<10; ++i){
		pnames[i] = &info_names[i][0];
	}


	if(remove("puntajes.txt")==0){
		FILE *f;
		f = fopen("puntajes.txt","w");
		for(int i=0; i<10; ++i){
			if(info_numscores[i]){
				for(int j=0; j<50; ++j){
					fprintf(f, "%c", info_names[i][j]);
				}
			 fprintf(f, "%d %s \n", info_numscores[i], pnames[i]);
			}
		}
		fclose(f);
	}else{
		printf("error");
	}

	
	//testing area
	for(int i=0; i<10; ++i){
		for(int j=0; j<50; ++j){
			printf("%c", info_names[i][j]);
		}
	}
	
	//end testing area
	
	//fprintf(fptr, "%d %s", score, name);	
	//fprintf(fptr, "\n");

	
}

void showScore(score *punt){
	
	FILE *fptr;
	fptr = fopen("/home/usuario/tetris-inf/puntajes.txt","r+");
	
	char info[10][50];
	for(int i=0; i<10; ++i){
		for(int j=0; j<50;++j){
			info[i][j] = 0;
		}
	}
	char *fil[10];
	for(int i=0; i<10; ++i){
		fil[i] = &info[i][0];
	}
	for(int i=0; i<10; ++i){
		fgets(fil[i], 50, fptr);
	}

	char info_names[10][50];
	char *pnames[10];
	for(int i=0; i<10; ++i){
		pnames[i] = &info_names[i][0];
	}

	char info_scores[10][50];

	for(int i=0; i<10; ++i){
		for(int j=0; j<50;++j){
			info_scores[i][j] = 0;
			info_names[i][j] = 0;
		}
	}

	for(int i=0; i<10; ++i){
		for(int j=0; j<50; ++j){
			if(info[i][j]>=48 && info[i][j]<=57){
				info_scores[i][j] = info[i][j]; 
			}else{
				info_names[i][j] = info[i][j];
			}
		}
	}

	int info_numscores[10];
	char *ptscores[10];
	for(int i=0; i<10; ++i){
		ptscores[i] = &info_scores[i][0];
	}
	for(int i=0; i<10; ++i){
		info_numscores[i] = atoi(ptscores[i]);
	}

	for(int i=0; i<10; ++i){
		int posmenor = i;
		for(int j=i+1; j<10;++j){
			if(info_numscores[j]<info_numscores[posmenor]){
				posmenor = j;
			}
		}
		int s = info_numscores[posmenor];
		char m[50];
		for(int k=0; k<50; ++k){
			m[k] = info_names[posmenor][k];
		}

		info_numscores[posmenor] = info_numscores[i];
		for(int k=0; k<50; ++k){
			info_names[posmenor][k] = info_names[i][k];
		}

		info_numscores[i] = s;
		for(int k=0; k<50; ++k){
			info_names[i][k] = m[k];
		}
	}


	for(int i=0; i<10; ++i){
		punt[i].score = info_numscores[i];
		for(int j=0; j<50; ++j){
			punt[i].user_name[j] = info_names[i][j];
		}
	}

	fclose(fptr);

}


/*
//Testing area 2

int main(){
	score pj1;
	pj1.score = 10;
	for(int i=0; i<50; ++i){
		pj1.user_name[i] = 0;
	}
	score *pt = &pj1;
	scanf("%[^\n]%*c", pj1.user_name);
	score list[10];
	score *pl = list;
	writeScore(pt);
	/*
	showScore(pl);
	for(int i=0; i<10; ++i){
		if(list[i].score !=0){
			printf("%d", list[i].score);
			for(int j=0; j<50; ++j){
				printf("%c", list[i].user_name[j]);
			}
		}
	}
	
}

*/