#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> // for folders

#include <raylib.h>
#include "utils.h"


#define MAX_MUSIC 256
#define MAX_MUSIC_STRING 256

typedef enum {
    PLAYING,
    PAUSED,
    FINISHED
}STATUS;

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

int updateMusic(Music *musics, int *i, int max){
    if(IsKeyPressed(KEY_RIGHT) ||
    (GetMusicTimeLength(musics[*i]) - 0.2f) == GetMusicTimePlayed(musics[*i])
    ){
        StopMusicStream(musics[*i]);
        if(*i < max - 1) (*i) +=1;
        PlayMusicStream(musics[*i]);
        printf("Next Music Playing\n");
        return 1;
    }
    if(IsKeyPressed(KEY_LEFT)){
        StopMusicStream(musics[*i]);
        if(*i >= 1) (*i) -=1;
        PlayMusicStream(musics[*i]);
        printf("Previous Music Playing\n");
        return 1;
    }
    return 0;
}



int main(void){
    InitAudioDevice();
    InitWindow(800, 600, "Spotify");
    SetTargetFPS(60);

    Music *musics = (Music*)malloc(sizeof(Music) * MAX_MUSIC);
    char** musics_str = (char**)malloc(sizeof(char*) * MAX_MUSIC);
    for (int i = 0; i < MAX_MUSIC; i++)
    {
        musics_str[i] = (char*)malloc(sizeof(char) * MAX_MUSIC_STRING);
    }

    int current = 0;
    addAllQueue(musics, &current, musics_str, "./music");
    printf("%d\n\n", current);

    int toPlay = 0;

    SetMusicVolume(musics[toPlay], 0.5f);
    PlayMusicStream(musics[toPlay]);
    printf("Playing %s\n",musics_str[toPlay]);
    while (!WindowShouldClose())
{
    float current_time = GetMusicTimePlayed(musics[toPlay]);
    float max_time = GetMusicTimeLength(musics[toPlay]);

    toggleResumePause(musics[toPlay]);
    UpdateMusicStream(musics[toPlay]);
    char *text = musics_str[toPlay];

    updateMusic(musics, &toPlay, current);
    
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText(text, 0, 0, 30, BLACK);

    if (IsMusicStreamPlaying(musics[toPlay]))
    {
        DrawText("Resume", 0, 80, 30, GREEN);
    }
    else
    {
        DrawText("Pause", 0, 80, 30, RED);
    }
    
    char time_info[100];
    snprintf(time_info, sizeof(time_info), "Current Time: %3.2f / Max Time: %3.2f", current_time, max_time);

    DrawText(time_info, 0, 120, 20, BLACK);

    EndDrawing();
}

    // Free allocated memory
    for (int i = 0; i < MAX_MUSIC; i++)
    {
        free(musics_str[i]);
    }
    free(musics_str);
    free(musics);

    CloseWindow();
    return 0;
}
