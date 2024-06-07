/* Texturas y sonidos*/
Texture2D menu, partida, gameover;
Sound acierto, fallo, tap;
Music gameMusic;

void loadTextures()
{
    menu = LoadTexture("resources/background.png");
    partida = LoadTexture("resources/gameBg.png");
    gameover = LoadTexture("resources/gameover.png");
}

void unloadTextures()
{
    UnloadTexture(menu);
    UnloadTexture(partida);
    UnloadTexture(gameover);
}

void loadSounds()
{
    acierto = LoadSound("resources/sucess.mp3");
    fallo = LoadSound("resources/fail.mp3");
    tap = LoadSound("resources/tap.mp3");
    gameMusic = LoadMusicStream("resources/music.mp3");
}

void unloadSounds()
{
    UnloadSound(acierto);
    UnloadSound(fallo);
    UnloadSound(tap);
    UnloadMusicStream(gameMusic);
}