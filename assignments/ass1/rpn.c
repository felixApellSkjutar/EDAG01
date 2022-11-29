#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N (10)

static void error(unsigned int line, int c, bool* err)
{
    char buf[3];
    if(c == '\n')
    {
        strcpy(buf, "\\n");
    }
    else {
        buf[0] = c;
        buf[1] = 0;
    }

    printf("line %u: error at %s\n", line, buf);

    *err = true;
}


int main() {   
  
int stack[N];  
int c;      //our read value
int i;      //iterator
int x;      //value of number
bool num;
bool err;
unsigned line;

x = 0;
i = 0;
line = 1;
num = false;
err = false;

    while((c = getchar()) != EOF)       //while loop som checkar om vi kommit till slutet av filen och ger nästa värde till c
    {

        error:
        if(err){

            while(c != '\n') {
                c = getchar();
            }
            
            if(c == '\n') {
            line += 1;
            err = 0;
            i = 0;

        
        continue;
            }
    
        } else if(isdigit(c)) {
            x = x * 10 + c - '0';       //konstigt sätt för att få x att bli rätt siffra
            num = true;                 
            continue;
        } else if(num) {                //när vi inte har en digit men num är true betyder det att vi precis är klara med en siffra
            if(i == N) {                 //kolla om stacken e full
                error(line, '0' + x%10, &err);
                goto error;
            }
            else {
                stack[i++] = x;         //lägg till x till stacken och öka i
                num = false;            //gör oss redo för nästa input
                x = 0;
            }
        }                      //tror det är här jag hanterar operatörer
            if(i >= 2){
                switch(c) {   
                case '+':
                stack[i - 2] = stack[i- 1] + stack[i-2];
                i--;
                break;

                case '-':
                stack[i - 2] = stack[i- 2] - stack[i-1];
                i--;
                break;

                case '*':
                stack[i - 2] = stack[i- 2] * stack[i-1];
                i--;
                break;
                case '/':           //behöver check så att inte stack[i-1] är 0;
                if(!stack[i-1] == 0){
                    stack[i - 2] = stack[i- 2] / stack[i-1];
                    i--;
                } else {
                    error(line, c, &err);
                }

                break;

                case ' ':
                break;

                case '\n':
                error(line, c, &err);
                goto error;

                default:
                error(line, c, &err);
                break;
                }
            } else if(c == '\n') {
                if(i > 0) {
                    err = 1;
                    printf("line %u: %d\n", line, stack[0]);
                    goto error;
                } else {
                    error(line, c, &err);
                    goto error;
                }            
            } else if(c != ' ') {
                error(line, c, &err);
                }
        }
    }

