# Tool to solve the [Countdown](https://en.wikipedia.org/wiki/Countdown_(game_show)) numbers problems

## Numbers game

### Build Instructions
Type "`cmake`", then type "`make numbers`"

### Run Instructions
Something along the lines of:
```
./numbers 25 50 4 3 8 456
```
Where the first 5 numbers are the input numbers and the last number is the target

You don't need to follow the Countdown rules. You can go crazy and do something like:
```
./numbers 1 2 3 4 5 6 7 8 456
```

N.B This will not find the best solution. Only **a** solution if one exists as you can see here:

```
./numbers 1 1 1 1 10 11

Numbers are : 1 1 1 1 10 
Target is   : 11
1 + 1 = 2
1 + 1 = 2
2 / 2 = 1
10 + 1 = 11
```

If a solution is not found then the closest attainable target will be found

## Letters game

### Build Instructions
Type "`cmake`", then type "`make letters`"

### Run Instructions
Something along the lines of:
```
./letters wordlist.txt ceensidrl
Populating letter tree
Searching for words
Best word is 9 letters: decliners
```
