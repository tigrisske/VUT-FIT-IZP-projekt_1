#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
//  #include<stdarg.h>

#define BUFFER_LENGTH 101
#define stats "--stats"
#define UNIQE_CHARS 126

bool upperCase(char ch[]){             //zistim ci konkretne slovo obsahuje aspon jedno velke pismeno
    for (int i = 0; ch[i] != '\0'; i++){
        if (ch[i] >= 'A' && ch[i] <= 'Z'){
            return 1;
        }
    }
    return 0;
}

int stringLength(char ch[]){
    int lenght = 0;
    while(ch[lenght] != '\0'){
    lenght++;
    }
    return lenght;
}

bool lowerCase(char ch[]){              //zistim ci konkretne slovo obsahuje aspon jedno male pismeno
    for (int i = 0; ch[i] != '\0'; i++){
        if (ch[i] >= 'a' && ch[i] <= 'z'){
            return 1;
        }
    }
    return 0;
}

bool requirement1(char ch[]){                //
    if (upperCase(ch)== 1 && lowerCase(ch) == 1){
        return 1;
    }
    else{
        return 0;
    }

}

bool findNumber(char ch[]){                  //funkcia zusti ci heslo obsahuje cislicu
    for(int i = 0; ch[i] != '\0'; i++){
        if (ch[i] >= '0' && ch[i] <= '9'){
            return 1;
        }
    }
    return 0;
}

bool validLevel(int argv1){                 //funkcia zisti ci je pargument Level zadany spravne*
    if (argv1 >= 1 && argv1 <= 4){
        return 1;
    }
    else{
        //printf("bol nespravne zadany Level\n");
        return 0;
    }
}

bool validParam(int argv2){                //funkcia zisti ci je argument PARAM zadany spravne*
    if (argv2 > 0){
        return 1;
    }
    else{
        //printf("bol nespravne zadany Parameter\n");
        return 0;
    }
}

bool specialChar(char ch[]){
    for(int i = 0; ch[i] != '\0'; i++){
        if ((ch[i] >=32 && ch[i] <= 47)||(ch[i] >=58 && ch[i] <= 64)||(ch[i] >=91 && ch[i] < 96)||(ch[i] >= 123 && ch[i] <= 126)){
                return 1;
        }
    }
    return 0;
}

bool rovnostStringov(char ch[], char ch1[]){ //funkcia porovna dva stringy
    for (int i = 0; ch[i]!= '\0';i++){
        if (ch[i] != ch1[i]){
            return 0;
        }
    }
    return 1;
 }

bool validStats(char ch[]){
    for (int i = 0; i !=stringLength(ch); i++){
        if (ch[i] != stats[i]){
            fprintf(stderr, "zle zadany argument");
            return 0;
        }
    }
    return 1;
}

int uniqeChars(char passwords[], char uniqe_chars[], int uniqe_chars_num){
    bool uniqe;
    for (int i = 0; passwords[i] != '\0'; i++){
    uniqe = false;
        for (int j = 0; uniqe_chars[j] != '\0'; j++){
            if(passwords[i] == uniqe_chars[j]){
                uniqe = true;
                break;
            }
            if (uniqe == false){
                uniqe_chars_num ++;
                uniqe_chars[uniqe_chars_num] = passwords[i];
            }
        }
    }

    return uniqe_chars_num;
}


int main(int argc, char *argv[]){
    int argv1 = atoi(argv[1]);
    int argv2 = atoi(argv[2]);
    if (argc == 4){
        if (validStats(argv[3]) == false){
            fprintf(stderr, "zle zadany argument");
            return 0;
        }
    }
    else if (argc == 3){
        if (validLevel(argv1) != 1){
            fprintf(stderr, "zle zadany argument");
            return 0;
        }
    }
    char buffer [BUFFER_LENGTH];
    while(fgets(buffer, BUFFER_LENGTH, stdin)){
        if (requirement1(buffer) && specialChar(buffer)){   //kontrolujem ci je prvy level splneny
            printf("%s", buffer);
        }
    }
    return 0;
}


