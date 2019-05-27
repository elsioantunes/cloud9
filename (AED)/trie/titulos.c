#include <stdio.h>
#include <unistd.h>

int len(const char *str){
    const char *s;
    for(s = str; *s; s++);
    return (s-str);
};

int main(){
    int i;
    char str[80];
    
    while(scanf("%s", str) != EOF){
        printf("\033[J[%s], %d\r", str, len(str));
        fflush(stdout);
        usleep(100000);
    }
    printf("\n");
    return 0;
}
