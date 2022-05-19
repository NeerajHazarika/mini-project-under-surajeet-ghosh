# What is the MTF transform?
The MTF (Move to Front) is a data transformation algorithm that restructures data in such a way that the transformed message is more compressible and therefore used as an extra step in compression. Technically, it is an invertible transform of a sequence of input characters to an array of output numbers.

# Why MTF?
1. In many cases, the output array gives frequently repeated characters’ lower indexes which is useful in data compression algorithms.

2. It is first of the three steps to be performed in succession while implementing Burrows – Wheeler Data Compression algorithm that forms the basis of the Unix compression utility bzip2.

# The main idea behind MTF:

1. The primary idea behind MTF is to maintain an ordered list of legal symbols (a to z, in our example).

2. Read one character at a time from input string .

3. Print out the position at which that character appears in the list.

4. Move that character to front of the list and repeat the process until indexes for all input characters are obtained.

```
Illustration for "panama".  
List initially contains English alphabets in order. 
We one by one characters of input to front.

input_str chars   output_arr       list
  p              15               abcdefghijklmnopqrstuvwxyz
  a              15 1             pabcdefghijklmnoqrstuvwxyz
  n              15 1 14          apbcdefghijklmnoqrstuvwxyz
  a              15 1 14 1        napbcdefghijklmoqrstuvwxyz
  m              15 1 14 1 14     anpbcdefghijklmoqrstuvwxyz
  a              15 1 14 1 14     manpbcdefghijkloqrstuvwxyz
  ```
  
# Inference:
1. If the letters occur many times in the input, then many of the output values will be small integers such as 0, 1, 2 etc.

2. Thus, encoding extremely high frequency of these letters makes an ideal scenario for Huffman Coding.

# Examples:
```
Input : panama
Output : 15 1 14 1 14 1

Input : geeksforgeeks
Output : 6 5 0 10 18 8 15 18 6 6 0 6 6 
```
# C program to find move to front transform of a given string
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns index at which character of the input text
// exists in the list
int search(char input_char, char* list)
{
	int i;
	for (i = 0; i < strlen(list); i++) {
		if (list[i] == input_char) {
			return i;
			break;
		}
	}
}

// Takes curr_index of input_char as argument
// to bring that character to the front of the list
void moveToFront(int curr_index, char* list)
{
	char* record = (char*)malloc(sizeof(char) * 26);
	strcpy(record, list);

	// Characters pushed one position right
	// in the list up until curr_index
	strncpy(list + 1, record, curr_index);

	// Character at curr_index stored at 0th position
	list[0] = record[curr_index];
}

// Move to Front Encoding
void mtfEncode(char* input_text, int len_text, char* list)
{
	int i;
	int* output_arr = (int*)malloc(len_text * sizeof(int));

	for (i = 0; i < len_text; i++) {

		// Linear Searches the characters of input_text
		// in list
		output_arr[i] = search(input_text[i], list);

		// Printing the Move to Front Transform
		printf("%d ", output_arr[i]);

		// Moves the searched character to the front
		// of the list
		moveToFront(output_arr[i], list);
	}
}

// Driver program to test functions above
int main()
{
	char* input_text = "panama";
	int len_text = strlen(input_text);

	// Maintains an ordered list of legal symbols
	char* list = (char*)malloc(sizeof(char) * 26);
	strcpy(list, "abcdefghijklmnopqrstuvwxyz");

	printf("Input text: %s", input_text);
	printf("\nMove to Front Transform: ");

	// Computes Move to Front transform of given text
	mtfEncode(input_text, len_text, list);
	
	return 0;
}
```

# Output:
```
Input text: panama
Move to Front Transform: 15 1 14 1 14 1
```

# Time Complexity: O(n^2)

