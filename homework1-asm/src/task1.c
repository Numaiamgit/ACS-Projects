#include <stdio.h>
#include <stdlib.h>

void solve_itinerary(int rows, int cols, int matrix[rows][cols], int start_x, int start_y, unsigned char *instrs, int num_instrs)
{
	for (int i = 0; i < num_instrs; i++) {
			int bit_tip = (instrs[i] >> 7) & 1;
			int bit_cate1 = (instrs[i] >> 6) & 1;
			int bit_cate2 = (instrs[i] >> 5) & 1;
			int bit_cate3 = (instrs[i] >> 4) & 1;
			int bit_cate = bit_cate3 * 1 + bit_cate2 * 2 + bit_cate1 * 4;
			int bit_directie_vest = (instrs[i] >> 3) & 1;
			int bit_directie_sud = (instrs[i] >> 2) & 1;
			int bit_directie_est = (instrs[i] >> 1) & 1;
			int bit_directie_nord = (instrs[i] >> 0) & 1;
			int zid_vest = (matrix[start_y][start_x] >> 3) & 1;
			int zid_sud = (matrix[start_y][start_x] >> 2) & 1;
			int zid_est = (matrix[start_y][start_x] >> 1) & 1;
			int zid_nord = (matrix[start_y][start_x] >> 0) & 1;
			if (bit_tip == 0) {
				if (bit_cate == 0) {
					if (bit_directie_vest == 1 && zid_vest == 0) {
						start_x -= 1;
					} else if (bit_directie_sud == 1 && zid_sud == 0) {
						start_y += 1;
					} else if (bit_directie_est == 1 && zid_est == 0) {
						start_x += 1;
					} else if (bit_directie_nord == 1 && zid_nord == 0) {
						start_y -= 1;
					}
				} else {
					for (int j = 0; j < bit_cate; j++) {
						int zid_vest = (matrix[start_y][start_x] >> 3) & 1;
						int zid_sud = (matrix[start_y][start_x] >> 2) & 1;
						int zid_est = (matrix[start_y][start_x] >> 1) & 1;
						int zid_nord = (matrix[start_y][start_x] >> 0) & 1;

						if (bit_directie_vest == 1 && zid_vest == 0) {
							start_x -= 1;
						} else if (bit_directie_sud == 1 && zid_sud == 0) {
							start_y += 1;
						} else if (bit_directie_est == 1 && zid_est == 0) {
							start_x += 1;
						} else if (bit_directie_nord == 1 && zid_nord == 0) {
							start_y -= 1;
						}
					}
				}
			}else{
				if(bit_cate == 0){
					if(bit_directie_vest == 1 && zid_vest == 0){
						start_x -= 1;
					}else if(bit_directie_sud == 1 && zid_sud == 0){
						start_y += 1;
					}else if(bit_directie_est == 1 && zid_est == 0){
						start_x += 1;
					}else if(bit_directie_nord == 1 && zid_nord == 0){
						start_y -= 1;
					}

			 }else{
					for (int j = i - bit_cate; j < i; j++) {
						int bit_tip_anter = (instrs[j] >> 7) & 1;                        
						int bit_cate1_anter = (instrs[j] >> 6) & 1;
						int bit_cate2_anter = (instrs[j] >> 5) & 1;
						int bit_cate3_anter = (instrs[j] >> 4) & 1;
						int bit_cate = bit_cate3_anter * 1 + bit_cate2_anter * 2 + bit_cate1_anter * 4;
						int bit_directie_vest_anter = (instrs[j] >> 3) & 1;
						int bit_directie_sud_anter = (instrs[j] >> 2) & 1;
						int bit_directie_est_anter = (instrs[j] >> 1) & 1;
						int bit_directie_nord_anter = (instrs[j] >> 0) & 1;
						int zid_vest = (matrix[start_y][start_x] >> 3) & 1;
						int zid_sud = (matrix[start_y][start_x] >> 2) & 1;
						int zid_est = (matrix[start_y][start_x] >> 1) & 1;
						int zid_nord = (matrix[start_y][start_x] >> 0) & 1;
						if(bit_tip_anter == 0){
							if(bit_cate == 0){
								if(bit_directie_vest_anter == 1 && zid_vest == 0){
									start_x -= 1;
								}else if(bit_directie_sud_anter == 1 && zid_sud == 0){
									start_y += 1;
								}else if(bit_directie_est_anter == 1 && zid_est == 0){
									start_x += 1;
								}else if(bit_directie_nord_anter == 1 && zid_nord == 0){
									start_y -= 1;
								}
							}else{
								for (int k = 0; k < bit_cate; k++) {
								 int zid_vest = (matrix[start_y][start_x] >> 3) & 1;
								 int zid_sud = (matrix[start_y][start_x] >> 2) & 1;
								 int zid_est = (matrix[start_y][start_x] >> 1) & 1;
								 int zid_nord = (matrix[start_y][start_x] >> 0) & 1;

								 if(bit_directie_vest_anter == 1 && zid_vest == 0){
									 start_x -= 1;
								 }else if(bit_directie_sud_anter == 1 && zid_sud == 0){
									 start_y += 1;
								 }else if(bit_directie_est_anter == 1 && zid_est == 0){
									 start_x += 1;
								 }else if(bit_directie_nord_anter == 1 && zid_nord == 0){
									 start_y -= 1;
								 }
							 }
						 }
						} else{
								int zid_vest = (matrix[start_y][start_x] >> 3) & 1;
								int zid_sud = (matrix[start_y][start_x] >> 2) & 1;
								int zid_est = (matrix[start_y][start_x] >> 1) & 1;
								int zid_nord = (matrix[start_y][start_x] >> 0) & 1;
	
								if(bit_directie_vest_anter == 1 && zid_vest == 0){
									start_x -= 1;
								}else if(bit_directie_sud_anter == 1 && zid_sud == 0){
									start_y += 1;
								}else if(bit_directie_est_anter == 1 && zid_est == 0){
									start_x += 1;
								}else if(bit_directie_nord_anter == 1 && zid_nord == 0){
									start_y -= 1;
								}
						}
					}
														 int zid_vest = (matrix[start_y][start_x] >> 3) & 1;
								 int zid_sud = (matrix[start_y][start_x] >> 2) & 1;
								 int zid_est = (matrix[start_y][start_x] >> 1) & 1;
								 int zid_nord = (matrix[start_y][start_x] >> 0) & 1;

						if(bit_directie_vest == 1 && zid_vest == 0){
							start_x -= 1;
						}else if(bit_directie_sud == 1 && zid_sud == 0){
							start_y += 1;
						}else if(bit_directie_est == 1 && zid_est == 0){
							start_x += 1;
						}else if(bit_directie_nord == 1 && zid_nord == 0){
							start_y -= 1;
						}
					}
				}
	}
	printf("(%d, %d)\n", start_x, start_y);
}

int main(void)
{
	int rows, cols, start_x, start_y, num_instrs;
	scanf("%d %d", &rows, &cols);
	int matrix[rows][cols];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	scanf("%d %d", &start_x, &start_y);
	scanf("%d", &num_instrs);
	unsigned char *instr = malloc(num_instrs * sizeof(unsigned char));
	for (int k = 0; k < num_instrs; k++) {
		int temp;
		scanf("%d", &temp);
		instr[k] = (unsigned char)temp;
	}
	solve_itinerary(rows, cols, matrix, start_x, start_y, instr, num_instrs);
	free(instr);
	return 0;
}