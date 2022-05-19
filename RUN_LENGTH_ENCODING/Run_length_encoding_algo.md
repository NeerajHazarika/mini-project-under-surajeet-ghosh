# Run Length Encoding
Given an input string, write a function that returns the Run Length Encoded string for the input string.
For example, if the input string is “wwwwaaadexxxxxx”, then the function should return “w4a3d1e1x6”

Steps :
1. Pick the first character from the source string.
2. Append the picked character to the destination string. 
3. Count the number of subsequent occurrences of the picked character and append the count to the destination string. 
4. Pick the next character and repeat steps 2,3 & 4 if the end of the string is NOT reached.

```
// CPP program to implement run length encoding
#include <bits/stdc++.h>

using namespace std;
 

void printRLE(string str)
{

    int n = str.length();

    for (int i = 0; i < n; i++) {
 

        // Count occurrences of current character

        int count = 1;

        while (i < n - 1 && str[i] == str[i + 1]) {

            count++;

            i++;

        }
 

        // Print character and its count

        cout << str[i] << count;

    }
}
 

int main()
{

    string str = "wwwwaaadexxxxxxywww";

    printRLE(str);

    return 0;
}
```
## OUTPUT :
` w4a3d1e1x6y1w3 `
