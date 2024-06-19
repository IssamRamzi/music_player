#include <stdio.h>

#include <raylib.h>


int main(void)
{
    InitAudioDevice();
    InitWindow(800,600,"Music Player");
    SetTargetFPS(60);

    Music music = LoadMusicStream("./Agora.mp3");
    PlayMusicStream(music);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);


        BeginDrawing();
        ClearBackground(RED);

        EndDrawing();
    }
    

    return 0;
}
