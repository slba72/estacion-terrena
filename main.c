#include "raylib.h"
#include "font.h"
#include "graph.h"

int main() {
	InitWindow(640, 480, "GISAT");
	SetTargetFPS(60);

	font = LoadFont("C:/Windows/Fonts/consola.ttf");

	graph_t graph1 = {0};
	Graph_init(&graph1, 50, 200);

	while(!WindowShouldClose()){
		INCREASE_TIME(time);
		
		Graph_logic(&graph1, input);

		CHECK_TIME();

		BeginDrawing();
		ClearBackground(WHITE);
			Graph_draw(&graph1);
		EndDrawing();
	}

	UnloadFont(font);
	CloseWindow();
	return 0;
}
