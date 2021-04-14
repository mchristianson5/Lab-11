#ifndef CD_LS_PWD_H
#define CD_LS_PWD_H

#include "util.h"

int chdir(char *pathname);
int ls_file(MINODE *mip, char *name);
int ls_dir(MINODE *mip);
int ls(char *pathname);
char *pwd(MINODE *wd);

#endif // CD_LS_PWD_H
