/*
 *pwchechk.c
 *
 *Kontrola Hesiel
 *
 *Dávid Jókay 10.2021
 */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define LEVEL_INDEX 1
#define PARAM_INDEX 2
#define STATS_INDEX 3

#define BUFFER_LENGTH 103
#define MAX_BUFFER_LEGTH 101
#define STATS_LENGHT 7
#define stats "--stats"
#define UNIQE_CHARS 126
#define MIN_ARGUMENTS 3
#define MAX_ARGUMENTS 4
#define MIN_LEVEL_VALUE 1
#define MAX_LEVEL_VALUE 4
#define ASCII_MIN 32
#define ASCII_MAX 126

//functions that checks if program arguments are valid
bool validLevel(int argv1);
bool validStats(char ch[]);
bool validParamType(char argv2[]);
bool validParam(int argv2);

//functions for level 1
bool upperCase(char ch[]);
bool lowerCase(char ch[]);
bool level1(char buffer[]);

//functions for level 2
bool isNumber(char ch);
bool findNumber(char ch[]);
bool specialChar(char ch[]);
bool level2(char buffer[], int x);

//functions for level 3
bool sameCharsRow(char ch[], int param);
bool level3(char buffer[], unsigned long long param);

//functions for level 4
bool subString(char buffer[], int param);
bool lvl4(char buffer[], int param);

//functions for stats
int uniqeChars(char passwords[], char uniqe_chars[], int uniqe_chars_num);

//additional functions
int chooseSmaller(int number1, int number2);
int stringLength(char ch[]);
bool requirements_check(int level, int param, char buffer[]);






int main(int argc, char *argv[])
{

//condition checks whether the amount of arguments is valid
    if (!((argc == MIN_ARGUMENTS)||(argc == MAX_ARGUMENTS)))
    {
        fprintf(stderr, "incorrect amount of arguments");
        return 1;
    }

//condition checks whether the length of level is 1
    if (stringLength(argv[LEVEL_INDEX])!= 1)
    {
        fprintf(stderr, "incorrect argument 'level'");
        return 1;
    }

//condition checks whether the level value is between 1 and 4
    int argv1 = atoi(argv[LEVEL_INDEX]);
    if (!(validLevel(argv1)))
    {
        fprintf(stderr, "incorrect argument 'level'");
        return 1;
    }

//condition checks whether data type of argument "param" is valid
    if(!(validParamType(argv[2])))
    {
        fprintf(stderr,"incorrect argument 'PARAM'");
        return 1;
    }

//condition checks whether argument "param" is valid
    int argv2 = atoi(argv[2]);
    if(!(validParam(argv2)))
    {
        fprintf(stderr, "incorrect argument 'PARAM'");
        return 1;
    }

    /*
    condition checks whether argument "stats" is valid and if so,
    bool "Stats" is set to 1
    */
    bool Stats = 0;
    if(argc == 4)
    {
        if(!(validStats(argv[STATS_INDEX])))
        {
            fprintf(stderr,"incorrect argument 'stats'");
            return 1;
        }
        Stats = 1;
    }

    char uniqueChars[UNIQE_CHARS+1];
    int numUniqueChars = 0;
    int charSum = 0;
    float pwdCount = 0;
    int shortestBufferLenght = BUFFER_LENGTH;
    char buffer [BUFFER_LENGTH];
    double AVG;
    while(fgets(buffer, BUFFER_LENGTH, stdin))
    {
        shortestBufferLenght = chooseSmaller(stringLength(buffer)-1, shortestBufferLenght);
        pwdCount++;
        charSum = (charSum + stringLength(buffer))-1; //-1 because function stringLength returns also the last "\0" character
        if (stringLength(buffer)>MAX_BUFFER_LEGTH)
        {
            fprintf(stderr,"password given is too long");
            return 1;
        }
        if (requirements_check(argv1, argv2, buffer))
        {
            printf("%s", buffer);
        }
        numUniqueChars = uniqeChars(buffer, uniqueChars, numUniqueChars);
    }

    if (Stats)
    {
        AVG = charSum/ pwdCount;
        printf("Statistika:\n");
        printf("Ruznych znaku: %d\n", numUniqueChars - 1);
        printf("Minimalni delka: %d\n",shortestBufferLenght);
        printf("Prumerna delka: %.1f\n", AVG);
    }
    return 0;
}

//function returns whether string contains uppercase
bool upperCase(char ch[])
{
    for (int i = 0; ch[i] != '\0'; i++)
    {
        if (ch[i] >= 'A' && ch[i] <= 'Z')
        {
            return 1;
        }
    }
    return 0;
}

//function returns whether string contains lowercase
bool lowerCase(char ch[])
{
    for (int i = 0; ch[i] != '\0'; i++)
    {
        if (ch[i] >= 'a' && ch[i] <= 'z')
        {
            return 1;
        }
    }
    return 0;
}

//function returns whether string contains a number
bool findNumber(char ch[])
{
    for(int i = 0; ch[i] != '\0'; i++)
    {
        if (isNumber(ch[i]))
        {
            return 1;
        }
    }
    return 0;
}

//function returns whether char is a number
bool isNumber(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return 1;
    }
    return 0;
}

//function returns whether string fulfills level 1 requirements
bool level1(char buffer[])
{
    if (lowerCase(buffer)&& upperCase(buffer))
    {
        return 1;
    }
    return 0;
}

//functions checks whether argument "level" is in range <1;4>
bool validLevel(int argv1)
{
    if (argv1 >= MIN_LEVEL_VALUE && argv1 <= MAX_LEVEL_VALUE)
    {
        return 1;
    }
    return 0;
}

//function checks if "stats" program argument is valid
bool validStats(char ch[])
{
    for (int i = 0; i !=stringLength(ch); i++)
    {
        if (ch[i] != stats[i])
        {
            return 0;
        }
    }
    return 1;
}

//function returns whether argument "PARAM" is a number
bool validParamType(char argv2[])
{
    for(int i = 0; i < stringLength(argv2); i++)
    {
        if(!(isNumber(argv2[i])))
        {
            return 0;
        }
    }
    return 1;
}

//function checks if argument "PARAM" is a number greater than 0
bool validParam(int argv2)
{
    if ((argv2 > 0))
    {
        return 1;
    }
    return 0;
}

//function returns whether string contains a special character
bool specialChar(char ch[])
{
    for(int i = 0; ch[i] != '\0'; i++)
    {
        if ((ch[i] >=ASCII_MIN && ch[i] < '0')||(ch[i] >'9' && ch[i] < 'A')||(ch[i] >'Z' && ch[i] <'a')||(ch[i] > 'z' && ch[i] <= ASCII_MAX))
        {
            return 1;
        }
    }
    return 0;
}

//function returns whether string fulfills level 1 and level 2 requirements at param "X"
bool level2(char buffer[], int x)
{
    if (x > 4)
    {
        x = 4;
    }
    if (x == 1 || x ==2)
    {
        if(level1(buffer))
        {
            return 1;
        }
    }
    if (x == 3 || x == 4)
    {
        if(((lowerCase(buffer))+(upperCase(buffer))+(findNumber(buffer))+(specialChar(buffer))) >= x)
        {
            return 1;
        }
    }
    return 0;
}

//function returns whether string contains a sequence of same character of length at least "param"
bool sameCharsRow(char ch[], int param)
{
    if (param == 1)
    {
        return 0;
    }
    for(int i = 0; ch[i] != '\0'; i++)
    {
        if(ch[i] == ch[i+1])
        {
            for(int j = 0; j != param; j++)
            {
                if(ch[i] != ch[i+j])
                {
                    break;
                }
                if((j+1) == param)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

//function compares 2 integers and returns smaller one
int chooseSmaller(int number1, int number2)
{
    if (number1 > number2)
    {
        return number2;
    }
    return number1;
}

//function returns length of a string
int stringLength(char ch[])
{
    int lenght = 0;
    while(ch[lenght] != '\0')
    {
        lenght++;
    }
    return lenght;
}

//function returns amount of unique chars from string
int uniqeChars(char passwords[], char uniqe_chars[], int uniqe_chars_num)
{
    bool uniqe;
    for (int i = 0; passwords[i] != '\0'; i++)
    {
        uniqe = false;
        for (int j = 0; uniqe_chars[j] != '\0'; j++)
        {
            if(passwords[i] == uniqe_chars[j])
            {
                uniqe = true;
                break;
            }
        }
        if (uniqe == false)
        {
            uniqe_chars[uniqe_chars_num] = passwords[i];
            uniqe_chars_num++;
        }

    }
    return uniqe_chars_num;
}

//function checks if level 1, 2 and 3 requirements are fulfilled at "param"
bool level3(char buffer[], unsigned long long param)
{
    if(level2(buffer, param) && sameCharsRow(buffer, param))
    {
        return 1;
    }
    return 0;
}

//function checks whether string contains 2 or more substrings of length at least "param"
bool subString(char buffer[], int param)
{
    int same = 0;
    bool isSubString = false;
    for (int i = 0; i!= stringLength(buffer); i++)
    {
        same = 0;
        isSubString = true;
        for (int j = 0; j!= stringLength(buffer); j++)
        {
            isSubString = true;
            for(int k = 0; k!= param; k++)
            {
                if(buffer[i+k] != buffer[j+k])
                {
                    isSubString = false;
                }
            }
            if(isSubString)
            {
                same++;
            }
            if (same>1)
            {
                return 0;
            }
        }
    }
    return 1;
}

//function returns whether level 1,2,3 and 4 requirements are fulfilled
bool lvl4(char buffer[], int param)
{
    if (level3(buffer, param)&& subString(buffer, param))
    {
        return 1;
    }
    return 0;
}

//function returns whether requirements at given arguments are fulfilled
bool requirements_check(int level, int param, char buffer[])
{
    switch(level)
    {
    case 1:
        if(level1(buffer))
        {
            return 1;
        }
        break;

    case 2:
    {
        if (level2(buffer,param))
        {
            return 1;
        }
        break;
    }
    case 3:
    {
        if(level3(buffer, param))
        {
            return 1;
        }
        break;
    }
    case 4:
    {
        if (lvl4(buffer, param))
        {
            return 1;
        }
        break;
    }
    }
    return 0;
}