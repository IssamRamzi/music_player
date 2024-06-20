#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <dirent.h>

bool checkExtension(char *file, char *ext){
	int flen = strlen(file);
	int elen = strlen(ext);
    /* printf("flen : %d, elen %d\n",flen,elen); */
	if(elen > flen){
		return false;
	}

    for(int i = flen - elen, j = 0; i < flen; i++,j++){
        if(file[i] != ext[j]){
            /* printf("%c %c \n",file[i], ext[j]); */
            return false;
        }
    }
    return true;
}

void listMusics(DIR *d){
    struct dirent *dir;
    if(d){
        while ((dir = readdir(d)) != NULL)
        {
            if(checkExtension(dir->d_name,".mp3"))
                printf("%s\n",dir->d_name);
        }
        closedir(d);
    }
}

void addQueue(Music *musics, int *i, Music music){
    musics[(*i)++] = music;
}


void addAllQueue(Music *musics, int *i,char** musics_str, const char *dirPath) {
    DIR *d = opendir(dirPath);
    struct dirent *dir;

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (checkExtension(dir->d_name, ".mp3")) {
                char filePath[512];
                snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, dir->d_name);
                // Load the music file
                Music music = LoadMusicStream(filePath);
                musics_str[*i] = dir->d_name;
                addQueue(musics, i, music);
            }
        }
        closedir(d);
    }
}


#endif UTILS_H
