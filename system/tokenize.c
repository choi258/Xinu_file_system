#include <xinu.h>

int mytokenizer(char dir[MAX_DEPTH][LF_NAME_LEN],char*path){
    int i,j;
    int ret,lvl = 0;

    for(i = 0;i < mystrlen(path); i++){
        for(j=0; path[i]!='/'&&path[i]!='\0';j++,i++){
            dir[lvl][j] = path[i];
        }
        if(i!=0){
            dir[lvl][j] = '\0';
            //kprintf("tokenize dir:%s \r\n", dir[lvl]);
            lvl++;

        }
    }
    return ret;
}
void mystrncpy(char *s,char *t,int n)
{
    while(*t && n-- > 0)
        *s++ = *t++;

    while(n-- > 0)
        *s++ = '\0';
}
int mystrcmp(char *s1, char *s2) 
{
    while ((*s1 != '\0') && (*s2 != '\0')) 
    {
        if (*s1 < *s2) {
            return(-1);      // string1 "less than" string2
        }
        if (*s1 > *s2) {
            return(1);       // string1 "greater than" string2
        }
        s1++;
        s2++;
    }
    if ((*s1 == '\0') && (*s2 == '\0')) {
        return(0);           
    }
    if (*s1 == '\0') {
        return(-1);          
    }
    return(1);              
}
int preDir(struct lfdir*dirptr ){
    int retval;
    if (! Lf_data.lf_dirpresent) {
        retval = read(Lf_data.lf_dskdev, (char *)dirptr,LF_AREA_DIR);
        if (retval == SYSERR ) {
            signal(Lf_data.lf_mutex);
            return SYSERR;
        }
        Lf_data.lf_dirpresent = TRUE;
    }
    retval = OK;
    return retval;
}

int countPath(char*path){
    int i;
    int count;
    count = 0;
    for(i=0;i < mystrlen(path); i++){
        if(path[i] == '/'){
            count++;
        }
    }
    return count;
}
int mystrlen(char*path){
    int i;
    for(i=0; path[i]!='\0';i++){
    }
    return i;
}
int countDir(char*path){
    int len;
    int count;
    int i;
    count = 0;
    len = mystrlen(path);
    for(i = 0;i < len; i++){
        if(path[i] == '/'){
            if(i != len-1){
                if(path[i+1]!='/' && path[i+1]!='\0'){
                    count++;
                }
            }
        }
    }
    return count;
}

