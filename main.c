#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> // for folders

#include <raylib.h>
#include "utils.h"


#define MAX_MUSIC 256
#define MAX_MUSIC_STRING 256

void toggleResumePause(Music music)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        if (IsMusicStreamPlaying(music))
        {
            PauseMusicStream(music);
            printf("Pause\n");
        }
        else
        {
            ResumeMusicStream(music);
            printf("Resume\n");
        }
    }
}

int main(void)
{   
    InitWindow(800, 600, "Music Player");
    SetTargetFPS(60);
    
    Music *musics = (Music*)malloc(sizeof(Music) * MAX_MUSIC);
    char** musics_str = (char*) malloc(sizeof(char) * MAX_MUSIC);
    for(int i =0; i < MAX_MUSIC; i ++){
        musics_str[i] = (char*)malloc(sizeof(char) * MAX_MUSIC_STRING);
    }
    int current = 0;
    addAllQueue(musics, &current,musics_str, "./music");


    int toPlay = 1;
    
    SetMusicVolume(musics[toPlay],0.5f);
    PlayMusicStream(musics[toPlay]);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(musics[toPlay]);
        toggleResumePause(musics[toPlay]);

        BeginDrawing();
        ClearBackground(RED);

        EndDrawing();
    }

    free(musics);
    free(musics_str);
    return 0;
}
