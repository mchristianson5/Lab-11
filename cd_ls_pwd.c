/************* cd_ls_pwd.c file **************/
#include "globals.h"
#include "cd_ls_pwd.h"

int chdir(char *pathname)
{
        printf("chdir %s\n", pathname);
        int ino = getino(pathname);
        if (ino == 0 ) {
                printf("chdir: path does not exist.\n");
                return -1;
        }

        MINODE *mip = iget(dev, ino);
        if (is_dir(&mip->INODE) == 0) {
                printf("chdir: not a directory.\n");
                return -1;
        }

        iput(running->cwd);

        running->cwd = mip;
        return 0;
}

int ls_file(MINODE *mip, char *name)
{
        const long atime = mip->INODE.i_atime;
        printf("%d %d %s %s\n", mip->INODE.i_mode, mip->INODE.i_size, ctime(&atime), name);
}

int ls_dir(MINODE *mip)
{
        printf("ls_dir: list CWD's file names; YOU do it for ls -l\n");

        char buf[BLKSIZE], temp[256];
        DIR *dp;
        char *cp;

        // Assume DIR has only one data block i_block[0]
        get_block(dev, mip->INODE.i_block[0], buf);
        dp = (DIR *)buf;
        cp = buf;

        while (cp < buf + BLKSIZE) {
                strncpy(temp, dp->name, dp->name_len);
                temp[dp->name_len] = 0;

                //printf("[%d %s]  ", dp->inode, temp); // print [inode# name]
                ls_file(mip, temp);
                cp += dp->rec_len;
                dp = (DIR *)cp;
        }
        printf("\n");
}

int ls(char *pathname)
{
        printf("ls %s\n", pathname);
        printf("ls CWD only! YOU do it for ANY pathname\n");
        ls_dir(running->cwd);
}

char *pwd(MINODE *wd)
{
        printf("pwd: READ HOW TO pwd in textbook!!!!\n");
        if (wd == root) {
                printf("/\n");
                return "";
        }
}

int is_dir(INODE *ino)
{
        int mode = ino->i_mode;
        mode = mode >> 12; // Shift 12 bits right.
        if (mode == DIR_MODE) {
                return 1;
        }
        return 0;
}
