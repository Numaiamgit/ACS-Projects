#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
int main(void)
{
	int cate, luna, unu = 0, doi = 0, trei = 0, patru = 0;
	uint32_t *tranzactii;
	scanf("%d %d", &cate, &luna);
	tranzactii = (uint32_t *)malloc(cate * sizeof(uint32_t));
	for (int i = 0; i < cate; i++) {
		scanf("%i", &tranzactii[i]);
		uint8_t b0 = (tranzactii[i] & 0xFF);
		uint8_t b1 = (tranzactii[i] >> 8) & 0xFF;
		//uint8_t b2 = (tranzactii[i] >> 16) & 0xFF;
		uint8_t b3 = (tranzactii[i] >> 24) & 0xFF;
		if (b3 == luna){
			if (b1 == 0x01){
				unu += b0;
			} else if (b1 == 0x02){
				doi += b0;
			} else if (b1 == 0x03){
				trei += b0;
			} else if (b1 == 0x04){
				patru += b0;
			}
		}
	}
	printf("1:%d\n 2:%d\n 3:%d\n 4:%d\n", unu, doi, trei, patru);
	free(tranzactii);

	return 0;
}