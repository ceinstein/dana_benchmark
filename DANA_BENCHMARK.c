#include <stdio.h>
#include <pthread.h>

//Struct that holds a net file, a train file, and the thread info
struct Net{
	char net_file[100];
	char train_file[100];
	int thread_number;
	pthread_t thread;
};

//Copies a character array into another character array
void strcopy(char *file, char str[]){
	int i = 0;
	while(str[i] != '\0'){
		file[i] = str[i];
		i++;
	}
	file[i] = '\0';
}

//Prints the info contained in a thread
void *print_info(void *net_info){
	struct Net *nets;
	nets = (struct Net *) net_info;

	printf("%s, %s\n", nets->net_file, nets->train_file);
}

//Converts a character into an integer
int atoi(char directive[]){
	int i = 0;
	int ret = 0;
	while(directive[i] != '\0'){
		ret = ret*10 +  directive[i] - '0';
		i++;
	}
	return ret;
}

int main(int argc, char *argv[]){
        printf("%s: STARTED\n", argv[0]);
	if(argc < 3){
		printf("Not enough input\nExiting ...\n");
		return 0;
	}
	int directive = atoi(argv[argc - 1]);
	struct Net nets[argc - 2];
	//Parse input files
	int file = 0;
	int k = 0;
	int j = 0;
	char n_file[50];
	char t_file[50];
	for(int i = 1; i < argc  - 1; i++){
		j = 0;
		k = 0;
		file = 0;
		while (argv[i][j] != '\0'){
			if(argv[i][j] == ','){
				file++;
				n_file[k] = '\0';
				k = 0;
			}else{
				if(file == 0){
					n_file[k] = argv[i][j];
				}else{
					t_file[k] = argv[i][j];
				}
				k++;
			}			
			j++;
		}
		t_file[k] = '\0';
		strcopy(nets[i - 1].net_file, n_file);
		strcopy(nets[i - 1].train_file, t_file);

	}

	//Thread creation and execution
	for(int i = 0; i < sizeof(nets)/sizeof(struct Net); i += directive){
		for(int j = i; j < directive + i && j < sizeof(nets)/sizeof(struct Net); j++){
			nets[j].thread_number = pthread_create(&nets[j].thread, NULL, &print_info, &nets[j]);
		}

		for(int j = i; j < directive + i && j < sizeof(nets)/sizeof(struct Net); j++){
			pthread_join(nets[j].thread, NULL);
		}
	}
}



