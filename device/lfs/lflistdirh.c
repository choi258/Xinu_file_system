#include <xinu.h>

int searchDirPrint(int flag, ibid32 index, char arr[MAX_DEPTH][LF_NAME_LEN], char* path   , int*found, int depth);

int trunc(int total, char*path);
int lflistdirh(did32 diskdev, char *directorypath){
    int found;
    int depth;
    int flag;
    int retval;
    struct lfdir *dirptr;
    char arr[MAX_DEPTH][LF_NAME_LEN];
    found = FOUND_DIR;
    depth = 0;
    dirptr =&Lf_data.lf_dir;
    wait(Lf_data.lf_mutex);
    if((retval = preDir(dirptr))== SYSERR){
        return SYSERR;
    }
    //kprintf("========List for :%s ===============\r\n", directorypath);
    mytokenizer(arr,directorypath);
    if(mystrcmp(directorypath, "/") == 0){
        flag = 1;
        retval = searchDirPrint(flag, 0, arr, (char*)directorypath,&found, depth);
    }else{
        flag = 0;
        retval = searchDirPrint(flag, 0, arr, (char*)directorypath,&found, depth);
    }
    signal(Lf_data.lf_mutex);

    return retval;
}



int searchDirPrint(int flag,ibid32 index, char arr[MAX_DEPTH][LF_NAME_LEN], char* path, int*found, int depth){
    int i;
    struct lfiblk ib;
    struct lfdbfree loaddb;

    if(*found == FOUND_DIR){
        *found = NEW_DIR;
        lfibget(Lf_data.lf_dskdev, index, &ib);
        /*kprintf("---SEARCH depth:%d iblock:%d count:%d \r\n", depth,index, ib.count);*/
        for(i=0;i < ib.count;i++){
            read(Lf_data.lf_dskdev,(char*)&loaddb, ib.ib_dba[i]);
            /*kprintf("arr:%s ld_name:%s \r\n", arr[depth],loaddb.ibentry.ld_name);*/
            if(flag == 1){
                kprintf("%s \t", loaddb.ibentry.ld_name);
            }else{
                if((mystrcmp(arr[depth],loaddb.ibentry.ld_name))==0){
                    *found = FOUND_DIR;
                    /*go to deeper directory */
                    depth++;
                    if(depth == countPath(path)){
                        flag = 1;
                    }
                    break;
                }
            }
        }
        if(*found == NEW_DIR && flag == 0 && i == ib.count){
            depth++;
            if(depth == countPath(path)){
                //kprintf("Wrong directory path\r\n");
                return SYSERR;
            }
        }
        if(*found == FOUND_DIR){
            searchDirPrint(flag,loaddb.ibentry.ld_ilist,arr,path,found,depth);
        }
    }
    kprintf("\n");
    return 0;
}

