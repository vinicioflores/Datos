#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACUM_SIZE		2048

typedef struct wlist_s
{
	struct wlist_s *next;
	char *word;

} wordfile_t;

wordfile_t *newnode(char *word)
{
	wordfile_t *newn = (wordfile_t *) malloc (sizeof(wordfile_t));
	newn->next = NULL;
	newn->word = (char *) malloc(strlen(word));
	strcpy(newn->word,word);
	return newn;
}

void add(wordfile_t **head, char *word){
	wordfile_t *tmp = *head;
	if( (*head) == NULL){
		(*head) = newnode(word);
	} else {
		while(tmp->next) tmp = tmp->next;
		tmp->next = newnode(word);
	}
}

void delete(wordfile_t **head, char *w2search)
{
	wordfile_t *actual, *last;
	int nofound = 1;

	actual = *head;

	while((actual != NULL) && (nofound)){
		nofound = strcmp(actual->word,w2search);
		if(nofound != 0){
			last = actual;
			actual = actual->next;
		}
	}

	if(actual != NULL){
		if(actual == *head) 
			*head = actual->next;
		else
			last->next = actual->next;
		free(actual->word);
		free(actual);
	}
}

void updateDataInFile(char *name, wordfile_t **head)
{
	wordfile_t *tmp = *head;

	FILE *pf = fopen(name, "w+");

	for(;tmp->next;){
		fprintf(pf,"%s ", tmp->word);
		tmp = tmp->next;
	}

	fclose(pf);
}

void readwords(wordfile_t **head, char *filename)
{
	char c='0';
	int j = 0;

	FILE *pf = fopen(filename, "r");
	if(!pf){printf("Cannot open input file %s\n",filename);system("PAUSE");exit(-1);}
	char acum[MAX_ACUM_SIZE];

	while(c != EOF){
		c = fgetc(pf);
		if(c != ' ' && c != '\n' && c != '\t' && c != '\0' && c != '.' && c != ',' && c != ':' && c != '\r'){
			acum[j] = c;
			j++;
		} else {
			add(head,acum);
			memset(acum,0,MAX_ACUM_SIZE);
			j = 0;
		}
	}
	fclose(pf);
}

void show(wordfile_t **head){
	wordfile_t *tmp = *head;
	for(; tmp; ){
		printf("%s\n",tmp->word);
		tmp = tmp->next;
	}
	puts("");
}

int main(int argc, char **argv){
	wordfile_t *filelist=NULL;
	char comm[MAX_ACUM_SIZE],word[MAX_ACUM_SIZE],filename[MAX_ACUM_SIZE];

	if(!argv[1]){
		printf("Inserte nombre de archivo: ");
		scanf("%s", filename);
	}
	if(argv[1]){ readwords(&filelist,argv[1]); strcpy(filename, argv[1]); }
	else readwords(&filelist,filename);
	show(&filelist);
	fflush(stdout);
	fflush(stdin);
	for(;;){
		memset(comm,0,MAX_ACUM_SIZE);
		memset(word,0,MAX_ACUM_SIZE);
		printf("\tEscriba 'del' para eliminar una palabra, 'add' para agregar o 'exit' para salir: \n %% ");
		scanf("%s", comm);
		if(strcmp(comm,"exit")){ fflush(stdin); fflush(stdout); printf("Inserte palabra a modificar: ");
		scanf("%s", word);  }
		if(strcmp(comm,"del")==0) delete(&filelist,word);
		else if(strcmp(comm,"add")==0) add(&filelist,word);
		else { updateDataInFile(filename,&filelist);exit(0); }
		updateDataInFile(filename,&filelist);
		#ifdef _WIN32
			system("cls");
		#else
			system("clear");
		#endif
		show(&filelist);
	}

	show(&filelist);
	system("PAUSE");
	return 0;
}
