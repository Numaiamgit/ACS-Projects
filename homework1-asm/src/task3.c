#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void get_items(void *suitcase, int *indices, int num_indices)
{
	for (int i = 0; i < num_indices; i++) {
		int index = (indices)[i];
		if (index >= 0) {
			int type = *(char *)(suitcase + index * 8);
			if (type == 1) {
				printf("%c\n", *(char *)(suitcase + index * 8 + 1));
			} else if (type == 2) {
				printf("%d\n", *(int *)(suitcase + index * 8 + 1));
			} else if (type == 3) {
				printf("\"%s\"\n", (char *)(suitcase + index * 8 + 2));
			} else if (type == 4) {
				printf("0x%02X\n", *(uint8_t *)(suitcase + index * 8 + 1));
			} else if (type == 5) {
				printf("0x%04X\n", *(uint16_t *)(suitcase + index * 8 + 1));
			}
		}
	}
}

int main(void)
{
	void *suitcase = NULL;
	int *indices = NULL;
	int num_indices = 0;
	int cate;
	scanf("%d", &cate);
	suitcase = calloc(cate * 9 + 1, 1);
	for(int i = 0; i < cate; i++){
		int type;
		scanf("%d", &type);
		if(type == 1){
			*(char *)(suitcase + i * 8) = (char) type;
			scanf(" %c", (char *)(suitcase + i * 8 + 1));
		}else if(type == 2){
			*(char *)(suitcase + i * 8) = (char) type;
			scanf(" %d", (int *)(suitcase + i * 8 + 1));
		}else if(type == 3){
			int lungime;
			scanf(" %d", &lungime);
			char *str = malloc(lungime + 1);
			if(lungime == 0){
				*(char *)(suitcase + i * 8) = (char) type;
				*(char *)(suitcase + i * 8 + 1) = (char) lungime;
				*(char *)(suitcase + i * 8 + 2) = '\0';
				getchar();
				getchar();
				getchar();
				free(str);
				continue;
			}
			 else{
			scanf(" %s", str);
			suitcase = realloc(suitcase, (cate * 9 + 1) + 1 + lungime);
			if(!suitcase){
				free(str);
				return 1;
			}
			*(char *)(suitcase + i * 8) = (char) type;
			*(char *)(suitcase + i * 8 + 1) = (char) lungime;
			int j = 1;
			while(lungime >= 8 * j){
				j++;
				i++;
				cate++;
			}
			memcpy(suitcase + i * 8 + 2, str, lungime + 1);
			free(str);
		}
		}else if(type == 4){
			*(char *)(suitcase + i * 8) = (char) type;
			uint8_t byte;
			scanf(" %hhi", &byte);
			*(uint8_t *)(suitcase + i * 8 + 1) = byte;
		}else if(type == 5){
			*(char *)(suitcase + i * 8) = (char) type;
			unsigned int temp;
			scanf(" %i", &temp);
			*(uint16_t *)(suitcase + i * 8 + 1) = (uint16_t)temp;
	}
	}
	scanf("%d", &num_indices);
	indices = (int *)malloc(num_indices * sizeof(int));
	for(int i = 0; i < num_indices; i++){
		scanf("%d", &indices[i]);
	}
	get_items(suitcase, indices, num_indices);
	free(suitcase);
	free(indices);
	return 0;
}