#include <raylib.h>
#include <stdio.h>
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

int main(int argc, char const *argv[])
{
    InitAudioDevice();
    InitWindow(800,600,"Music Player");
    SetTargetFPS(60);
    Music music = LoadMusicStream("./music/K cigarettes after sex slowed.mp3");
    PlayMusicStream(music);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);

        BeginDrawing();
        ClearBackground(PINK);
        toggleResumePause(music);

        EndDrawing();
    }
    

    return 0;
}
