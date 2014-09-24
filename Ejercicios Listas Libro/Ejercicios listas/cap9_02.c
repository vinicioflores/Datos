#include "cap9.h"


#define MAXBUF			1024

#define CMD_SIZE		 45
#define CMD_EXIT		-13
#define CMD_ADD			-24
#define CMD_DEL			-35

static void proc_cmd(char *command, int *cmd, tda_simple_list_t **head, FILE *inputf)
{
	char word[CMD_SIZE]; int word_index=0, i_added=0;
	tda_simple_list_t *p = NULL;
	if(strcmp(command,"exit") == 0) *cmd = CMD_EXIT;
	else if(strcmp(command,"add") == 0) *cmd = CMD_ADD;
	else *cmd = CMD_DEL;

 	if(*cmd == CMD_ADD) {
 		printf("Inserte palabra: ");
 		scanf("%s", word);
 	}

 	if(*cmd != CMD_EXIT){
 		printf("Inserte indice de palabra: ");
 		scanf("%d", &word_index);
 	}

	switch(*cmd){
		case CMD_ADD:
			i_added = tda_base_ins(head,word_index, malloc(sizeof(CMD_SIZE)) );
			p = tda_base_search(head,i_added);
			memcpy(p->tda_data,(const void*)word,CMD_SIZE);
			p = NULL; i_added = 0;
			break;
		case CMD_DEL:
			tda_base_delete(head,word_index);
			break;
		case CMD_EXIT:
			exit(0);
			break;
	}
}

static void readwords(tda_simple_list_t **head, FILE *infp)
{
	char acum[CMD_SIZE], c;
	int j = 0, iadded;

	printf("call readwords ... \n");
	do {
		c = fgetc(infp);
		if(c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '.' || c == ',' ){
			iadded = tda_base_add(head,NULL);
			tda_base_savedat(head,(void *)acum,iadded,sizeof(char));
			memset(acum,0,CMD_SIZE);
			j = 0;
		} else {
			acum[j] = c;
			j++;
		}
	} while(c != EOF);
}

static void printwords(tda_simple_list_t **head)
{
	printf("call prinwords ... \n");
	tda_simple_list_t *p = *head;
	while(p){
		printf("[%d]. %s\n", p->tda_index, ( (char *)p->tda_data )  );
		p = p->tda_next;
	}
}

void update_file(tda_simple_list_t **head, char *filename)
{
	FILE *fout = fopen(filename, "w");

	if(!fout) printf("No puedo abrir archivo %s para escritura ... \n", filename);
	else {
		tda_simple_list_t *p=*head;
		while(p){
			fprintf(fout, "%s\n",  (char *)p->tda_data);
			p = p->tda_next;
		}

		fclose(fout);
	}
}

void les_problema2()
{
	tda_simple_list_t *wordlist=NULL;
	tda_set_type(&wordlist,TDA_DOUBLE_LIST);
	int cmd=0;
	char filename[CMD_SIZE], command[CMD_SIZE];
	printf("Inserte nombre de archivo de entrada: ");
	scanf("%s",filename);
	FILE *inf = fopen(filename, "r");
	if(!inf) { printf("No se pudo abrir archivo %s de entrada ...\n", filename); }
	else {
		readwords(&wordlist, inf);

		while(cmd != CMD_EXIT){
			printwords(&wordlist);
			memset(command,0,CMD_SIZE);
			printf("$ ");
			scanf("%s", command);
			proc_cmd(command,&cmd,&wordlist,inf);
			update_file(&wordlist,filename);
		}
	}
}
