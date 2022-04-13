# Brute Force Approach

- This will detect if the entire string can be generated from a particular substring of it. But we need to also accept/consider cases for which entirely new pattern starts repeating in the string after a particular repeating pattern.

```
def repeats(string):
    for x in range(1, len(string)):
        substring = string[:x]

        if substring * (len(string)//len(substring))+(substring[:len(string)%len(substring)]) == string:
            print(substring)
            return "break"

    print(string)
```
- source : [link](https://stackoverflow.com/questions/41077268/python-find-repeated-substring-in-string)

# Dynamic Programming Approach 

- This algorithm only prints out the number of characters it will take to encode the entire string using RLE while detecting repeating substrings.
- INPUT STRING : `AAABBAAABBCECE`

```
import sys
import numpy as np

bignum = 10000

S = 'AAABBAAABBCECE'                                                                                                                              
N = len(S)

# length of longest substring match bet s[i:] and s[j:]                                                                                                        
maxmatch = np.zeros( (N+1,N+1), dtype=int)

for i in range(N-1,-1,-1):
  for j in range(i+1,N):
    if S[i] == S[j]:
      maxmatch[i,j] = maxmatch[i+1,j+1]+1

# P[n,k] = cost of encoding first n characters given that last k are a block                                                                                   
P = np.zeros( (N+1,N+1),dtype=int ) + bignum
# Q[n] = cost of encoding first n characters                                                                                                                   
Q = np.zeros(N+1, dtype=int) + bignum

# base case: no cost for empty string                                                                                                                          
P[0,0]=0
Q[0]=0

for n in range(1,N+1):
  for k in range(1,n+1):
    if n-2*k >= 0:
#     s1, s2 = S[n-k:n], S[n-2*k:n-k]                                                                                                                          
#     if s1 == s2:                                                                                                                                             
      if maxmatch[n-2*k,n-k] >=k:
        # Here we are incrementing the count: C x_1...x_k -> C+1 x_1...x_k                                                                                     
        P[n,k] = min(P[n,k], P[n-k,k])
        # print('P[',n,',',k,'] = ',P[n,k])
    # Here we are starting a new block: 1 x_1...x_k                                                                                                            
    P[n,k] = min(P[n,k], Q[n-k] + 1 + k)
    # print('P[',n,',',k,'] = ',P[n,k])
  for k in range(1,n+1):
    Q[n] = min(Q[n], P[n,k])

  print

print(Q[N])
```
### OUTPUT : 
```
9
```
- INPUT string : `AAABBAAABBCECE` (14 characters), RLE string : `2AAABB2CE` (9 characters)
- source : [link](https://stackoverflow.com/questions/2261318/finding-the-minimum-length-rle)
