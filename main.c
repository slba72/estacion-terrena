#include "raylib.h"
#include "font.h"
#include "graph.h"

#define GRAPH_MAX 4

int main() {
	InitWindow(640, 480, "GISAT");
	SetTargetFPS(60);

	font = LoadFont("C:/Windows/Fonts/consola.ttf");

	graph_t graph1 = {0};
	graph_t graph2 = {0};
	Graph_init(&graph1, 50, 200);
	Graph_init(&graph2, 310, 200);

	int v = 0;
	int input = 0;
	int input2 = 0;
	//input = GetRandomValue(20, 25); //20, 24 // 50, 54
	while(!WindowShouldClose()){
		INCREASE_TIME(time);

		//(time == 1) ? (time = 0) : (++time);

		//input = GetRandomValue(20, 25); //20, 24 // 50, 54
		//printf("%d\n", input);
		//Graph_logic(&s1, GetRandomValue(2, 4));
		/*Graph_logic(&graph1, input);*/

		if (IsKeyPressed(KEY_ENTER)) {
			input = GetRandomValue(-5, 0); //20, 24 // 50, 54	
			printf("input: %d\n", input);
		}
		
		input = GetRandomValue(-2, 2);
		input2 = GetRandomValue(0, 5);
		Graph_logic(&graph1, input);
		Graph_logic(&graph2, input2);

		CHECK_TIME();

		BeginDrawing();
		ClearBackground(WHITE);

		//for (int i = 0; i < GRAPH_MAX; ++i) {
			
			Graph_draw(&graph1);
			Graph_draw(&graph2);
		//}

		EndDrawing();
	}

	UnloadFont(font);
	CloseWindow();
	return 0;
}