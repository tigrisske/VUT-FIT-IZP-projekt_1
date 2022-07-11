/*
**  IZP projekt 1 but in JS 
**  author : David Jokay 
**  date   : 10.07.2022 
*/

//PROGRAM

//function declarations and constans 

//function reads from a file given and returns an array with content of the file 
const {readFileSync, promises: fsPromises} = require('fs');

function syncReadFile(filename) {
  const contents = readFileSync(filename, 'utf-8');
  const arr = contents.split(/\r?\n/);
  //console.log(arr);
  return arr;
}

const passwords = syncReadFile(process.argv[process.argv.length-1]);

//checks whether given value is in range
function inRange(min, max, value){
    if(value <= max && value >= min) 
        return true;    
    return false;    
}

//level 1 

function isLower(char){
    return (inRange(65, 90, char.charCodeAt(0)));   
}
function isUpper(char){
    return (inRange(97, 122, char.charCodeAt(0)));   
}

function level1(word){
    if (level > 1) return true;
    let upper = false;
    let lower = false;
        for (char of word){
            if (isUpper(char))        
                upper = true;
            if (isLower(char))
                lower = true;
        }
    return (lower && upper);
}

//level 2 
function isNum(char){
    return (inRange(48, 57, char.charCodeAt(0)));   
}
function isSpecilaChar(char){
    return (inRange(32, 126, char.charCodeAt(0))) && !isLower(char) && !isUpper(char) && !isNum(char); 
}

function level2(word,level, param){
    if (level < 2) return true;
    //if (level> 2) param = 4;
    let achievedParam = 0;
    let param1 = false;
    let param2 = false;
    let param3 = false;
    let param4 = false;
    
    for (char of word){
        if (isLower(char)) param1 = true;
        if (isUpper(char)) param2 = true;
        if (isNum(char)) param3 = true;
        if (isSpecilaChar(char)) param4 = true;
    }
    if (param1) achievedParam++;
    if (param2) achievedParam++;
    if (param3) achievedParam++;
    if (param4) achievedParam++;
    return (achievedParam >= param);
}


//level 3

function level3(word, level, param){
    if (level < 3){
        return true;
    }
    if (param <2) return false;
        for ( let i = 0 ; i < word.length- (param -1); i++){
            let same = 1;
            for (let p = 0; p < param - 1; p++){
                if (word[p+i] === word[p+i+1]){
                    same++;
                }
                //console.log('word[p+i]:', word[p+i], ',word[p+i+1]:', word[p+i+1], ',same:', same)
                if (same >= param) return false;
            }
        }
    //console.log('toto sa deje');
    return true;
}

function level4(word, level, param){
    if (level < 4) return true;
    let same = 0
    let isSubstring = false
    for (let i = 0; i < word.length; i++){
        same = 0;
        isSubstring = true;
        for ( let j = 0; j < word.length; j++){
            isSubstring = true;
            for (let k = 0; k < param; k++)
                if(word[i+k] != word[j+k]) isSubstring = false;
            if(isSubstring) same++;
            if (same>1) return false; 
        } 
    }
    return true
}

//run function
function run(array, level, param){
    for (word of array)
        if (level1(word, level, param)&& level2(word, level, param) && level3(word, level, param)&& level4(word, level, param)) 
            console.log(word)
}



//console.log(isSpecilaChar('@'))

//stats functions 
function uniqeChars(array){
    let uniqe = 0;
    const arr = [];
    for (let i of array){
        for (let j of i){
            if (!arr.includes(j)){ 
                uniqe++;        
            } 
            arr.push(j);
        }
    }
    return uniqe;
}

function minLen(array){
    if (array.length <= 1)
        return array[0].length;
    return array.reduce((a, b) => (a < b.length)? a : b.length, array[0].length);
}

function avgLen(array){
    const sum = array.reduce((a ,b) => a + b.length, 0);
    const arrLen = array.length
    return sum/arrLen;
}

function showStats(passwords){
    console.log('Ruznych znaku: ' + uniqeChars(passwords));
    console.log('Minimalni delka: '+ minLen(passwords));
    console.log('Prumerna delka: '+ avgLen(passwords));
    return 0;
}

//-------------------------------------------------------------------------------------------------------

// CHECKING ARGUMENTS
let level = Number(process.argv[2]);
let param = Number(process.argv[3]);
let isStat = false;



//number of arguments given
if (process.argv.length != 5 && process.argv.length != 6){
    console.error('[ERROR] invalind amount of argumets given');
    return 1;
}

//firt 2 given arguments must be numbers 


if (isNaN(level)){
    console.error('[ERROR] level must be number in range [1,4]');
    return 1;
}

if (isNaN(param)){
    console.error('[ERROR] parameter must be number')
    return 1;
}

//optional argument stats 
if (process.argv.length === 6 && process.argv[4] !== '--stats'){
    console.error('[ERROR] wrong optional argument');
    return 1;  
}

if (process.argv[4] == '--stats'){
    isStat = true;
}

//range of level and param 
if (!inRange(1,4,level)){
    console.error('[ERROR] level must be number in range [1,4]');
    return 1;
} 

if (!inRange(1, 50, param)){
    console.error('[ERROR] param must be number in range [1,50] ')
    return 1;
}

//running the program 
run(passwords, level, param);

//stats 
if (isStat) showStats(passwords);



