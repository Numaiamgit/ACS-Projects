# Homework 1

## Assignment: Byte-Sized Travels: Moving Through Europe at 64-Bit Speed

**Soft Deadline**: 11.04.2026

**Hard Deadline**: 16.04.2026

**Authors**

* Radulescu Andrei-Valentin
* Popescu Robert-Andrei

## Introduction
![](banner.png)

The summer exams are officially over, and the narrow hallways of the Regie student dorms are echoing with the sound of rolling suitcases and frantic, last-minute plans. Eli and Edi, having just survived their first year of university, are hunched over a cluttered desk covered in Europass maps and half-packed rucksacks. Their dream is simple: an unforgettable summer trek through Europe’s greatest capitals, from the neon lights of Berlin to the winding canals of Amsterdam.

However, before they can validate their Interrail tickets, the duo has set one final "digital survival" challenge. As a rite of passage, they’ve decided that every logistical hurdle—from decoding ancient travel itineraries and securing their walkie-talkie communications to the physical optimization of their shared suitcase—must be solved in 64-bit Assembly before they even step foot on a train. You are the third member of the crew, the algorithmic "architect" tasked with ensuring their logic is bulletproof. If your code doesn't run perfectly now, while they’re still sitting on the floor of their room in Regie, their grand adventure might end before they even make it to Gara de Nord.

## Task 1 - Lost Itinerary

While rummaging through a forgotten trunk in the corner of their dorm room, Edi’s hand brushes against something crinkled and brittle. He pulls out a weathered, yellowed parchment it's an old, unnamed travel itinerary from decades ago. There are no city names or dates, only a bizarre, hand-drawn matrix of symbols and a cryptic list of instructions that looks like a series of encoded moves.

“This could be an amazing detour,” Eli says, scanning the odd grid. “But where does it lead? We can’t just wing it, or we'll get completely lost.” They need to know if this path is safe and worth the trouble before they add it to their journey. They’ve tasked you with writing a C program that can act as a digital tracker: it must read the encoded map, interpret the traveler’s bizarre instructions, and pinpoint the final destination (x,y) on the grid, ensuring they don't get lost.

### Example

You are given a matrix:
13  3   11
11  10  14
12  4   7

Each number can be represented on 4 bits(0b abcd), each "1" bit represents a wall:
- if a is 1 -> wall on the West side
- b = 1 -> wall on the South side
- c = 1 -> wall on the East side
- d = 1 -> Wall on the North side

The resulting maze for the given matrix will be:
```
 ________ 
|__   |  |
|  |  |__|
|________|
```
After the maze, a set of initial coordinates and a set of instructions (each represented as a byte) will be given in the following encoding:
- The last 4 bits represent the direction of movement, similar to the maze encoding, the first bit represents moving to the West and so on
- The first 4 bits represent a special request, such as repeating the instruction or going back "x" instructions in the flow. If the first bit is set, you will be required to go back n steps, otherwise you should repeat the current instruction the set amount of times. Once you go back once, on the following encounter you will skip the special request.
Example:
161 - 0b1010 0001 -> First bit is set so it will require going back 2 instructions(0b010). The current instruction is going North, so after going back 2 instructions and executing those, upon returning to this byte you will be required to go North.
72 - 0b0100 1000 -> First bit is 0 so we will repeat the instruction (going West) 4 times(100).

If you run into a wall or go out of bounds the instruction is ignored and you remain in the same square.

For initial coordinates (0,0) and the sequence 72 2 164, the final expected position is (1,1).

## Task 2 - Walkie Talkie

"What if we're hiking in the Carpathians or exploring some remote village and we lose cell service?" Eli asks, examining a set of sturdy, military-grade walkie-talkies they picked up at a flea market. Edi agrees; they need a backup. But Edi, being cautious, adds another layer to their communication plan: "Our conversations are top-secret. We can’t just blabber about our coordinates or secret party spots on an open channel where any amateur radio operator can eavesdrop!"

Their solution is a custom-built, multi-stage encryption protocol, specifically designed to be light enough for their modified handhelds to process. They’ve established a dynamic XOR key—a random byte known only to them—and a complex series of bit-level operations. Each character from the message they are about to send will be XORed with the key and the bit order inverted. After, they will use the following algorithm to stuff the message: For each resulting bit, if the bit corresponds to the one in the key a "1" will be added, else a 0. Then, the following short will be transmitted in Big Endian order and in hexadecimal.

### Example

If the given key is '>' -> 0b00111110 (ascii code). And the message they want to send is 'B' -> 0b01000010, the following operations will take place:
B is xored with the key -> 0b00111110 ^ 0b01000010 = 0b01111100
The bit order is reversed -> 0b001111110
Then the stuffing algorithm:
  - The first resulting bit is 0. This matches the first bit of the key, so a 1 is appended.
  - The last resulting bit is 0. This matches from the last bit of the key (0), so a 1 is appended.
In the end, we have: 01011111 111111101
We make it Big Endian: 11111101 01011111 and write it in hex -> 0xFD5F

## Task 3 - Suitcase

The departure time is looming, and the most challenging logistical puzzle yet is sitting wide open on the floor: the suitcase. Eli is trying to justify a full stack of paperbacks, while Edi is determined to fit in a bulky camera, three different pairs of shoes, and, inexplicably, a vintage chessboard. "We have multiple objects with completely different dimensions," Edi sighs, surveying the pile of heterogeneous items. "But only one contiguous block of space in this trunk!"

The problem isn't just space; it's organization and retrieval. Packing them is one thing, but finding Edi's charger among Eli's books without unpacking everything is a nightmare. They decide to treat the suitcase like a low-level memory buffer. You must create a custom memory manager that can efficiently serialize various object types (your diverse belongings) into a continuous void* suitcase and, more importantly, implements a precision indexing system that allows them to extract exactly what they need, exactly when they need it, regardless of the object's original type or size. Failure means leaving behind essential gear or, worse, losing it in the void of the suitcase!

### Example
You will be given a sequence of homogeneous data. You have the liberty to store them as you want but you should be able to retrieve any one of the given values.
An example of input data would be:
'C' 91 "Hello" 0b0100 'E' 0xCAFE
And afterwards some indicies:
0 3 5
You will be expected to return:
C 0b0100 0xCAFE

## Task4 - Expense Logger

After sorting out the itinerary, the secure communications, and the physical constraints of their luggage, reality hits Eli and Edi hard: traveling through Europe is expensive. They need to keep a strict eye on their budget, but their current system is just a messy, unorganized digital journal of numbers.

"We can't just swipe our cards and hope for the best," Eli says, pulling up a long list of hex codes. "I've logged every planned expense, but they are all mashed together. We need to know exactly how much we are spending on train tickets versus museum passes."

To save memory on their low-power devices, Edi encoded each transaction into a single 32-bit unsigned integer (uint32_t). By treating this integer like a hardware register, he packed four different pieces of information into it, using exactly one byte (8 bits) for each field.

The structure of the 32-bit transaction from left to right (Most Significant Byte to Least Significant Byte) is:

Byte 3 (Bits 24-31): The Month of the transaction (e.g., 7 for July).

Byte 2 (Bits 16-23): The Day of the transaction (1-31).

Byte 1 (Bits 8-15): The Category ID (1 = Food, 2 = Transport, 3 = Accommodation, 4 = Entertainment).

Byte 0 (Bits 0-7): The Amount spent in Euros (0-255).

Your task is to write a C function that iterates through an array of these 32-bit transactions. Using bitwise operations (shifts and masks), you must unpack the data and calculate the total sum spent on a specific category during a specific month.

### Example
You are given an array of 3 transactions, encoded in hexadecimal:
0x070F0214, 0x08100232, 0x0715020A

You need to find the total spent on every category in Month 7 (July).

Here is how the data is decoded:

0x070F0214 -> Month is 0x07 (7). Day is 0x0F (15). Category is 0x02 (2). Amount is 0x14 (20 EUR).

0x08100232 -> Month is 0x08 (8). Day is 0x10 (16). Category is 0x02 (2). Amount is 0x32 (50 EUR).

0x0715020A -> Month is 0x07 (7). Day is 0x15 (21). Category is 0x02 (2). Amount is 0x0A (10 EUR).

The program checks each transaction:

The first matches both the month (7) and the category (2). We add 20 to the total.

The second matches the category, but the month is 8. We ignore it.

The third matches both the month (7) and the category (2). We add 10 to the total.

The expected output returned by your function will be 1:0 2:30 3:0 4:0.


### Coding style

Coding style can be run directly in the checker, by pressing `C`, or by using the
`cs.sh` executable from `checker/cs`. The points are the folowing:

- \>= 10 of `CHECK` => -5 points
- \>= 5 of `WARNING` => -5 points
- \>= 1 of `ERROR` => -10 points

## Notes

- For sending the homework, you can use the `make pack` rule, which automatically creates
  a zip file with the necessary content already in it. Don't forget to change your name first

## Checker

> ! Attention, the checker doesn't run valgrind by default, but you must pass all the test
with valgrind in order to get the score. To activate valgrind on your checker, press
`v`, making sure there is a red border which will show that it is on.


### Checker Instructions

For a list of commands and guides for the checker, please read the README from the
`src/` directory.