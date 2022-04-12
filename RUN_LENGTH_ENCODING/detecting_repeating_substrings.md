# Brute Force Approach

```
def repeats(string):
    for x in range(1, len(string)):
        substring = string[:x]

        if substring * (len(string)//len(substring))+(substring[:len(string)%len(substring)]) == string:
            print(substring)
            return "break"

    print(string)
```

- This will detect if the entire string can be generated from a particular substring of it. But we need to also accept/consider cases for which entirely new pattern starts repeating in the string after a particular repeating pattern.
