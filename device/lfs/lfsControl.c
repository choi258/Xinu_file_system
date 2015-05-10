/* lfsControl.c  -  lfsControl */
#include <xinu.h>
/*------------------------------------------------------------------------
 *  * lfsControl - Control 
 *   *------------------------------------------------------------------------
 *    */
void Mkdir(ibid32 index,char *path, char arr[MAX_DEPTH][LF_NAME_LEN],int found, int depth);
int caseHandler(struct dentry*,char*);
void searchDir(ibid32 index,char[MAX_DEPTH][LF_NAME_LEN], char* path, int*found, int depth);

devcall lfsControl(struct dentry *devptr, int32 func, int32 arg1, int32 arg2){
    int32 retval;
    if(func!=3){
        return SYSERR;
    }else{
        retval = caseHandler(devptr, (char*)arg1);
    }
    return retval;
}

int caseHandler(struct dentry * devptr, char * path){
    struct lfdir *dirptr = NULL;
    int found;
    int depth;
    int retval = 0;
    char arr[MAX_DEPTH][LF_NAME_LEN];
    if(countDir(path) < countPath(path)){
        return SYSERR;    
    }else{
        dirptr = &Lf_data.lf_dir;
        wait(Lf_data.lf_mutex);
        if((retval = preDir(dirptr))== SYSERR){
            return SYSERR;
        }
        //kprintf("Size data :%d \r\n", sizeof(struct lfdir));  
        /*set the root iblock*/
        mytokenizer(arr, path);
        depth = 0;
        found = FOUND_DIR;
        /*search for directory and set position*/
        searchDir(0, arr, (char*)path,(int*)&found,depth);

        if(found == DUP_DIR){
            return SYSERR;
        }else if(found == NEW_DIR){
            depth = 0;
            found = FOUND_DIR;
            //lfibget(Lf_data.lf_dskdev,0,&new);
            Mkdir(0,path,arr,found,depth);
        }
        //write(Lf_data.lf_dskdev, db.lf_unused, 0);
        signal(Lf_data.lf_mutex);
        return OK;
    }
}

void searchDir(ibid32 index, char arr[MAX_DEPTH][LF_NAME_LEN], char* path, int*found, int depth){
    int i;
    struct lfiblk ib;
    struct lfdbfree loaddb;
    memset(&loaddb, NULLCH, sizeof(struct lfdbfree));
    memset(&ib, NULLCH, sizeof(struct lfiblk));

    if(*found == FOUND_DIR){
        *found = NEW_DIR;
        lfibget(Lf_data.lf_dskdev, index, &ib);
        //kprintf("---SEARCH depth:%d iblock:%d count:%d \r\n", depth,index,ib.count);
        for(i=0;i<ib.count&&ib.ib_dba[i]!=LF_INULL;i++){
            read(Lf_data.lf_dskdev,(char*)&loaddb, ib.ib_dba[i]);
            //kprintf("iblock:%d [%d]: dbindex:%d ldname:%s to iblock:%d  \r\n",index,i, ib.ib_dba[i],loaddb.ibentry.ld_name,loaddb.ibentry.ld_ilist);
            if((mystrcmp(arr[depth],loaddb.ibentry.ld_name))==0){
                *found = FOUND_DIR;
                /*go to deeper directory */
                depth++;
            }
        }
        if(*found == FOUND_DIR){
            if(depth == countPath(path)){
                *found = DUP_DIR;
            }else{
                searchDir(loaddb.ibentry.ld_ilist,arr,path,found,depth);
            }
        }
    }
}

void Mkdir(ibid32 index,char *path, char arr[MAX_DEPTH][LF_NAME_LEN],int found, int depth){
    struct lfdbfree new_db;
    struct lfdbfree loaddb;
    struct lfiblk new_ib;
    struct lfiblk load_ib;
    int db_index, ibnum;
    struct lfdir * dirptr;
    memset(&new_db, NULLCH, sizeof(struct lfdbfree));
    memset(&loaddb, NULLCH, sizeof(struct lfdbfree));
    memset(&new_ib, NULLCH, sizeof(struct lfiblk));
    memset(&load_ib, NULLCH, sizeof(struct lfiblk));
    int i;
    if(depth < countPath(path)){
        found = NEW_DIR;
        lfibget(Lf_data.lf_dskdev,index,&load_ib);
        for(i=0;i<load_ib.count;i++){
            read(Lf_data.lf_dskdev,(char*)&loaddb, load_ib.ib_dba[i]);
            if((mystrcmp(arr[depth],loaddb.ibentry.ld_name))==0){
                found = FOUND_DIR;
                /*go to deeper directory */
                if(depth < countPath(path)){
                    depth++;
                    Mkdir(loaddb.ibentry.ld_ilist,path,arr,found,depth);
                }

            }
        }
        if(found == NEW_DIR){
            //kprintf("=================Make new directory ============== \r\n");
            /* make new db*/ 
            db_index = lfdballoc(&new_db);
            load_ib.ib_dba[i] = db_index;
            load_ib.count++;
            lfibput(Lf_data.lf_dskdev,index, &load_ib);
            read(Lf_data.lf_dskdev,(char*)&new_db, load_ib.ib_dba[i]);
            /* initialize data block */
            new_db.ibentry.isDir = 1;
            mystrncpy(new_db.ibentry.ld_name,arr[depth],mystrlen(arr[depth]));
            /* create new iblock */
            ibnum = lfiballoc();
            new_db.ibentry.ld_ilist = ibnum;
            //kprintf("depth:%d connect iblock:%d:[%d]  to dblock : %d to new iblock:%d \r\n",depth, index, i, db_index,ibnum);
            lfibget(Lf_data.lf_dskdev, ibnum, &new_ib);
            new_ib.ib_next = LF_INULL;
            lfibclear(&new_ib,0);
            lfibput(Lf_data.lf_dskdev, ibnum, &new_ib);
            write(Lf_data.lf_dskdev, (char*)&new_db, db_index);
            dirptr = &Lf_data.lf_dir;
            dirptr->tot_iblk++;
            if(depth < countPath(path)){
                depth++;
                Mkdir(ibnum,path,arr,found,depth);
            }
        }
        /* not sure*/

    }
}




