#include "raylib.h"
#include "resources.h"
#include <stdlib.h>
#include <time.h>

#define SCR_WIDTH 1600
#define SCR_HEIGHT 900

#define MAX_SECUENCIA 100
#define N_COLORS 4

// Enum con estados del juego
typedef enum _gameState
{
    MAIN_MENU,
    IN_GAME,
    GAME_OVER,
    INPUT_SEC,
    SHOW_SEQUENCE,
} TgameState;

// Struct para almacenar propiedades del boton
typedef struct
{
    Rectangle rect;
    Color color;
    Color highlightColor;
} Button;

// Prototipos funciones
void drawMainMenu();
void initButtons();
void drawGame();
void showSequence();
void ingresarSecuencia();
int opcionUsuario();
void drawGameOver();
void updateGameState(int key);
void DrawTextCenterX(const char *text, int posX, int posY, int fontSize, Color color);

TgameState gameState = MAIN_MENU;            // Estado del juego
Button buttons[N_COLORS];                    // Botones de color
int secuencia[MAX_SECUENCIA];                // Arreglo que almacena la secuencia
int secuenciasCorrectas = 0;                 // Tamaño de secuencia actual
int intentoActual = 0;                       // Numero de intento del jugador
int indiceAMostrar = 0;                      // Indice a mostrar en showSequence
float tiempoInicio = 0;                      // Tiempo de inicio para pausa
Color highlightColor = {200, 200, 200, 255}; // Color para resaltar los botones

int main()
{
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Simon Game");
    SetTargetFPS(60);

    srand(time(NULL)); // Semilla numeros aleatorios

    /* Carga de texturas y sonidos */
    loadTextures();
    InitAudioDevice();
    loadSounds();

    int key; // Almacena tecla pulsada

    // Inicializa propiedades de los botones
    initButtons();

    while (!WindowShouldClose())
    {
        updateGameState(key);
        key = -1;

        BeginDrawing();

        switch (gameState)
        {
        case MAIN_MENU:
            PlayMusicStream(gameMusic);
            UpdateMusicStream(gameMusic);
            drawMainMenu();
            key = GetKeyPressed();
            break;

        case IN_GAME:
            indiceAMostrar = 0;                                   // Reinicia indice
            tiempoInicio = GetTime();                             // Reinicia tiempo
            secuencia[secuenciasCorrectas++] = rand() % N_COLORS; // Genera nuevo color secuencia
            gameState = SHOW_SEQUENCE;
            break;

        case SHOW_SEQUENCE:
            showSequence();
            break;

        case GAME_OVER:
            drawGameOver();
            secuenciasCorrectas = 0; // Reinicia aciertos del jugador
            key = GetKeyPressed();
            break;

        case INPUT_SEC:
            drawGame();
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

// Dibuja menu principal
void drawMainMenu()
{
    DrawTexture(menu, 0, 0, WHITE);
    DrawTextCenterX("SIMON GAME", 0, 90, 130, GOLD);
    DrawTextCenterX("SIMON GAME", 4, 94, 130, YELLOW);

    DrawTextCenterX("(Enter) Jugar", 0, 600, 55, LIME);
    DrawTextCenterX("(Enter) Jugar", 2, 602, 55, GREEN);

    DrawTextCenterX("(Esc) Salir", 0, 700, 55, MAROON);
    DrawTextCenterX("(Esc) Salir", 2, 702, 55, RED);
}

// Inicializa los botones y define sus propiedades
void initButtons()
{
    float buttonWidth = 200;
    float buttonHeight = 160;

    float centerX = SCR_WIDTH / 2;
    float centerY = SCR_HEIGHT / 2;

    buttons[0] = (Button){(Rectangle){centerX - buttonWidth - 10, centerY - buttonHeight - 10, buttonWidth, buttonHeight}, RED, MAROON};
    buttons[1] = (Button){(Rectangle){centerX + 10, centerY - buttonHeight - 10, buttonWidth, buttonHeight}, GREEN, DARKGREEN};
    buttons[2] = (Button){(Rectangle){centerX - buttonWidth - 10, centerY + 10, buttonWidth, buttonHeight}, BLUE, DARKBLUE};
    buttons[3] = (Button){(Rectangle){centerX + 10, centerY + 10, buttonWidth, buttonHeight}, YELLOW, GOLD};
}

// Dibuja interfaz principal del juego
void drawGame()
{
    ClearBackground(WHITE);
    DrawTexture(partida, 0, 0, WHITE);

    for (int i = 0; i < N_COLORS; i++)
    {
        Rectangle rect = buttons[i].rect;

        // Amplia boton al pasar cursor encima
        if (CheckCollisionPointRec(GetMousePosition(), rect))
        {
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

    DrawText(TextFormat("Aciertos: %d", secuenciasCorrectas - 1), SCR_WIDTH / 2 - MeasureText(TextFormat("Aciertos: %d", secuenciasCorrectas - 1), 50) / 2, 750, 50, DARKGRAY);
    DrawText(TextFormat("Aciertos: %d", secuenciasCorrectas - 1), (SCR_WIDTH / 2 - MeasureText(TextFormat("Aciertos: %d", secuenciasCorrectas - 1), 50) / 2) + 2, 752, 50, RAYWHITE);
    DrawTextCenterX("¡Replica la secuencia en el orden correcto!", 0, 100, 50, DARKGRAY);
    DrawTextCenterX("¡Replica la secuencia en el orden correcto!", 3, 103, 50, YELLOW);
}

// Reproduce secuencia actual
void showSequence()
{
    drawGame();

    if (indiceAMostrar < secuenciasCorrectas)
    {
        if (GetTime() - tiempoInicio > 0.5f)
        {
            Rectangle rect = buttons[secuencia[indiceAMostrar]].rect;

            // Ampliar el cuadrado
            rect.x -= 10;
            rect.y -= 10;
            rect.width += 20;
            rect.height += 20;

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
        intentoActual = 0;
    }
}

// Recibe y valida la secuencia ingresada
void ingresarSecuencia()
{
    int eleccion = opcionUsuario();
    if (eleccion != -1)
    {
        if (secuencia[intentoActual] == eleccion)
        {
            intentoActual++;
            if (intentoActual >= secuenciasCorrectas) // Completo la secuencia correctamente
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

// Lee y retorna opcion del usuario
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

void drawGameOver()
{
    ClearBackground(RAYWHITE);
    DrawTexture(gameover, 0, 0, WHITE);
    DrawTextCenterX("Has perdido!", 0, 250, 70, DARKGRAY);
    DrawTextCenterX("Has perdido!", 4, 254, 70, RED);

    DrawTextCenterX("(Enter) Jugar de nuevo", 0, 700, 40, DARKGRAY);
    DrawTextCenterX("(Enter) Jugar de nuevo", 4, 704, 40, GREEN);

    DrawTextCenterX("(Q) Volver al menu", 0, 760, 40, DARKGRAY);
    DrawTextCenterX("(Q) Volver al menu", 4, 764, 40, RED);
}

void updateGameState(int key)
{
    switch (gameState)
    {
    case MAIN_MENU:
        if (key == KEY_ENTER)
        {
            StopMusicStream(gameMusic);
            gameState = IN_GAME;
        }
        else if (key == KEY_F11)
        {
            ToggleFullscreen();
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

void DrawTextCenterX(const char *text, int posX, int posY, int fontSize, Color color)
{
    DrawText(text, SCR_WIDTH / 2 + posX - MeasureText(text, fontSize) / 2, posY, fontSize, color);
}