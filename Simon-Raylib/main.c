#include "raylib.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

#define SCR_WIDTH 1600
#define SCR_HEIGHT 900

#define MAX_SECUENCIA 100
#define N_COLORS 4

// Estados del juego
typedef enum _gameState
{
    MAIN_MENU,
    IN_GAME,
    GAME_OVER,
    INPUT_SEC,
    SHOW_SEQUENCE,
} TgameState;

// Estructura para almacenar el cuadro y su color
typedef struct
{
    Rectangle rect;
    Color color;
    Color highlightColor;
} Button;

TgameState gameState = MAIN_MENU; // Estado del juego
Button buttons[N_COLORS];         // Botones de color
int secuencia[MAX_SECUENCIA];     // Arreglo que almacena la secuencia
int secuenciaACT = 0;             // Tamaño de secuencia actual
int intentoJugador = 0;           // Numero de intento del jugador
int indiceAMostrar = 0;           // Indice a mostrar en showSequence
float tiempoInicio = 0;           // Tiempo de inicio para pausa

Color highlightColor = {200, 200, 200, 255}; // Color para resaltar los botones

void menuInterface();
void gameoverInterface();
void drawColors();
void showSequence();
void secondspause(float seconds);
void DrawTextCenter(const char *text, int posX, int posY, int fontSize, Color color);
void updateGame(int key);
void ingresarSecuencia();
int opcionUsuario();

int main()
{
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Simon Game");
    SetTargetFPS(60);

    srand(time(NULL));

    loadTextures();
    InitAudioDevice();
    loadSounds();

    int key = -1; // Opcion del usuario

    float buttonWidth = 200;
    float buttonHeight = 160;

    float centerX = SCR_WIDTH / 2;
    float centerY = SCR_HEIGHT / 2;

    buttons[0] = (Button){(Rectangle){centerX - buttonWidth - 10, centerY - buttonHeight - 10, buttonWidth, buttonHeight}, RED, MAROON};
    buttons[1] = (Button){(Rectangle){centerX + 10, centerY - buttonHeight - 10, buttonWidth, buttonHeight}, GREEN, DARKGREEN};
    buttons[2] = (Button){(Rectangle){centerX - buttonWidth - 10, centerY + 10, buttonWidth, buttonHeight}, BLUE, DARKBLUE};
    buttons[3] = (Button){(Rectangle){centerX + 10, centerY + 10, buttonWidth, buttonHeight}, YELLOW, GOLD};

    while (!WindowShouldClose())
    {
        updateGame(key);
        key = -1;

        BeginDrawing();

        switch (gameState)
        {
        case MAIN_MENU:
            PlayMusicStream(gameMusic);
            UpdateMusicStream(gameMusic);
            menuInterface();
            key = GetKeyPressed();
            break;

        case IN_GAME:
            StopMusicStream(gameMusic);
            gameState = SHOW_SEQUENCE;
            indiceAMostrar = 0;                            // Reinicia indice
            tiempoInicio = GetTime();                      // Reinicia tiempo
            secuencia[secuenciaACT++] = rand() % N_COLORS; // Genera nuevo.
            break;

        case SHOW_SEQUENCE:
            showSequence();
            break;

        case GAME_OVER:
            gameoverInterface();
            secuenciaACT = 0;
            key = GetKeyPressed();
            break;

        case INPUT_SEC:
            drawColors();
            ingresarSecuencia();
            break;
        }

        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
    unloadTextures();
    unloadSounds();
    return 0;
}

void menuInterface()
{
    DrawTexture(menu, 0, 0, WHITE);
    DrawTextCenter("SIMON GAME", 0, 90, 130, GOLD);
    DrawTextCenter("SIMON GAME", 4, 94, 130, YELLOW);

    DrawTextCenter("(Enter) Jugar", 0, 600, 55, LIME);
    DrawTextCenter("(Enter) Jugar", 2, 602, 55, GREEN);

    DrawTextCenter("(Esc) Salir", 0, 700, 55, MAROON);
    DrawTextCenter("(Esc) Salir", 2, 702, 55, RED);
}

void gameoverInterface()
{
    ClearBackground(RAYWHITE);
    DrawTexture(gameover, 0, 0, WHITE);
    DrawTextCenter("Has perdido!", 0, 250, 70, DARKGRAY);
    DrawTextCenter("Has perdido!", 4, 254, 70, RED);

    DrawTextCenter("(Enter) Jugar de nuevo", 0, 700, 40, DARKGRAY);
    DrawTextCenter("(Enter) Jugar de nuevo", 4, 704, 40, GREEN);

    DrawTextCenter("(Q) Volver al menu", 0, 760, 40, DARKGRAY);
    DrawTextCenter("(Q) Volver al menu", 4, 764, 40, RED);
}

void drawColors()
{
    ClearBackground(RAYWHITE);
    DrawTexture(partida, 0, 0, WHITE);

    for (int i = 0; i < N_COLORS; i++)
    {
        Rectangle rect = buttons[i].rect;

        // Si el cursor esta sobre el cuadro, lo amplia
        if (CheckCollisionPointRec(GetMousePosition(), rect))
        {
            // rect.x -= 5;
            // rect.y -= 5;
            // rect.width += 10;
            // rect.height += 10;
            DrawRectangleRoundedLines(rect, 0.2, 0, 10, highlightColor);
        }
        // Dibuja el cuadrado
        DrawRectangleRounded(rect, 0.2, 0, buttons[i].color);

        // Restaurar el tamaño original cuando el cursor se aleja
        if (!CheckCollisionPointRec(GetMousePosition(), buttons[i].rect))
        {
            rect = buttons[i].rect;
            DrawRectangleRounded(rect, 0.2, 0, buttons[i].color);
        }
    }

    DrawText(TextFormat("Aciertos: %d", secuenciaACT - 1), SCR_WIDTH / 2 - MeasureText(TextFormat("Aciertos: %d", secuenciaACT - 1), 50) / 2, 750, 50, DARKGRAY);
    DrawText(TextFormat("Aciertos: %d", secuenciaACT - 1), (SCR_WIDTH / 2 - MeasureText(TextFormat("Aciertos: %d", secuenciaACT - 1), 50) / 2) + 2, 752, 50, RAYWHITE);
    DrawTextCenter("¡Replica la secuencia en el orden correcto!", 0, 100, 50, DARKGRAY);
    DrawTextCenter("¡Replica la secuencia en el orden correcto!", 3, 103, 50, YELLOW);
}

void showSequence()
{
    drawColors();

    if (indiceAMostrar < secuenciaACT)
    {
        if (GetTime() - tiempoInicio > 0.5f)
        {
            Rectangle rect = buttons[secuencia[indiceAMostrar]].rect;

            // Ampliar el cuadrado
            rect.x -= 5;
            rect.y -= 5;
            rect.width += 10;
            rect.height += 10;

            DrawRectangleRounded(rect, 0.2, 0, buttons[secuencia[indiceAMostrar]].highlightColor);

            if (GetTime() - tiempoInicio > 1.0f)
            {
                indiceAMostrar++;
                tiempoInicio = GetTime();
            }
        }
    }
    else
    {
        gameState = INPUT_SEC;
        intentoJugador = 0;
    }
}

void ingresarSecuencia()
{
    int eleccion = opcionUsuario();
    if (eleccion != -1)
    {
        if (secuencia[intentoJugador] == eleccion)
        {
            intentoJugador++;
            if (intentoJugador >= secuenciaACT)
            {
                PlaySound(acierto);
                gameState = IN_GAME;
            }
        }
        else
        {
            PlaySound(fallo);
            gameState = GAME_OVER;
        }
    }
}

int opcionUsuario()
{
    for (int i = 0; i < N_COLORS; i++)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), buttons[i].rect))
        {
            PlaySound(tap);
            return i;
        }
    }
    return -1;
}

void DrawTextCenter(const char *text, int posX, int posY, int fontSize, Color color)
{
    DrawText(text, SCR_WIDTH / 2 + posX - MeasureText(text, fontSize) / 2, posY, fontSize, color);
}

void secondspause(float seconds)
{
    double startTime2 = GetTime();

    while (GetTime() - startTime2 < seconds)
    {
        BeginDrawing();
    }
    EndDrawing();
}

void updateGame(int key)
{
    switch (gameState)
    {
    case MAIN_MENU:
        if (key == KEY_ENTER)
        {
            gameState = IN_GAME;
        }
        break;

    case IN_GAME:
        break;

    case GAME_OVER:
        if (key == KEY_ENTER)
        {
            gameState = IN_GAME;
        }
        else if (key == KEY_Q)
        {
            gameState = MAIN_MENU;
        }
        break;

    case INPUT_SEC:
        break;

    case SHOW_SEQUENCE:
        break;
    }
}
