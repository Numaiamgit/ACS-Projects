#include <stdio.h>
#include <stdint.h>

uint16_t encrypt_message(uint8_t msg, uint8_t key) 
{	
	uint8_t to_reverse = msg ^ key;
	uint8_t to_stuff = 0;
	uint16_t final = 0;
	for (int i = 0; i < 8; i++) {
		to_stuff |= ((to_reverse >> i) & 1) << (7 - i);
	}
	for(int i = 0; i < 8; i++) {
		if(((to_stuff >> i) & 1) == 1 && ((key >> i) & 1) == 0) {
			final |= (1 << (i * 2 + 1));
		} else if (((to_stuff >> i) & 1) == 0 && ((key >> i) & 1) == 1) {
		} else if (((to_stuff >> i) & 1) == 1 && ((key >> i) & 1) == 1) {
			final |= (1 << (i * 2 + 1));
			final |= (1 << (i * 2));
		} else {
			final |= (1 << (i * 2));
		}
	}
	uint16_t byte1 = 0;
	uint16_t byte2 = 0;
	byte1 = (final >> 8) & 0x00FF;
	byte2 = (final << 8) & 0xFF00;
	final = byte2 | byte1;
	return final;
}

int main(void)
{
	uint8_t msg, key;
	scanf("%x %x", (unsigned int *)&msg, (unsigned int *)&key);
	uint16_t encrypted = encrypt_message(msg, key);
	printf("0x%04X\n", encrypted);
	return 0;
}