#include "graph.h"
#include "font.h"
#include <stdio.h>

#define GRAPH_MAX_Y 5
#define TIME_SEC 1 // 60 -> 1 segundo
#define X_AXIS_MAX x_axis_values[5]
#define X_AXIS_MIN x_axis_values[0]
//#define Y_AXIS_MAX y_axis_values[5]
//#define Y_AXIS_MIN y_axis_values[0]
#define GRAPH_WIDTH 250
#define GRAPH_HEIGHT 170
#define POINT_X_FIX (FONT_SIZE * i * 3)
#define POINT_Y_FIX (FONT_SIZE + (FONT_SIZE * i * 2))
#define POINT_R 5.0f

static int x_axis_values[6] = { 0, 1, 2, 3, 4, 5 };
//static int y_axis_values[6] = { 0, 1, 2, 3, 4, 5 };
long point_i = 0;
//unsigned int adv = 0;

// macro??
static inline void IncreaseYAxis(const int input, int* y_axis_values, int* adv) {
	/*printf("y_min_value: %d\n", y_axis_values[0]);
	printf("y_max_value: %d\n", y_axis_values[5]);
	printf("input: %d\n", input);*/
	while (y_axis_values[0] != input) {
		for (int i = 0; i < 6; ++i)
			y_axis_values[i]++;
		++(*adv);
	}
	/*printf("y_min_value: %d\n", y_axis_values[0]);
	printf("y_max_value: %d\n", y_axis_values[5]);*/
}

static inline void DecreaseYAxis(const int input, int* y_axis_values, int* adv) {
	//printf("y_min_value: %d\n", y_axis_values[0]);
	//printf("y_max_value: %d\n", y_axis_values[5]);
	//printf("input: %d\n", input);
	while (y_axis_values[0] != input) {
		for (int i = 0; i < 6; ++i)
			y_axis_values[i]--;
		--(*adv);
	}
	/*printf("y_min_value: %d\n", y_axis_values[0]);
	printf("y_max_value: %d\n", y_axis_values[5]);*/
}

//static inline void DecreaseYAxis(const int input) {
//	while (Y_AXIS_MIN != input)
//		for (int i = 0; i < 6; ++i)
//			y_axis_values[i]--;
//}

void Graph_init(graph_t* graph, int x, int y) {
	graph->x = x;
	graph->y = y;
	for (int i = 0; i < 6; ++i) {
		printf("%d\n", i);
		graph->y_axis_values[i] = i;
	}
}

void Graph_logic(graph_t* graph, const int value) {
	if (time == TIME_SEC) {
		graph->point[point_i].value = value;
		(point_i < GRAPH_POINT_MAX) ? (++point_i) : (point_i = 0);
		for (int i = 0; i < 6; ++i)
			++x_axis_values[i];
		for (int i = 0; i < GRAPH_POINT_MAX; ++i) {
			graph->point[i].point.y = graph->y - (15 + (30 * ((graph->point[i].value - (graph->adv))%6))) + POINT_R;
		}
	}
	
	if (value > graph->y_axis_values[5]) {
		IncreaseYAxis(value, graph->y_axis_values, &(graph->adv));
	}else if (value < graph->y_axis_values[0]) {
		DecreaseYAxis(value, graph->y_axis_values, &(graph->adv));
	}
}

void Graph_draw(graph_t* graph) {
	int x = graph->x;
	int y = graph->y;
	Vector2 in_pos = {0};
	Vector2 out_pos = {0};
	in_pos.y = y;
	out_pos.x = x - FONT_SIZE;

	// draw info
	DrawLine(x, y, x+GRAPH_WIDTH, y, BLACK);  // x
	DrawLine(x, y, x, y-GRAPH_HEIGHT, BLACK); // y

	for (int i = 0; i < GRAPH_POINT_MAX - 1; ++i)
		DrawLine(graph->point[i].point.x, graph->point[i].point.y, graph->point[i + 1].point.x, graph->point[i + 1].point.y, RED);

	for (int i = 0; i < GRAPH_POINT_MAX; ++i) {
		in_pos.x = x + POINT_X_FIX;
		out_pos.y = y - POINT_Y_FIX;

		DrawTextEx(font, TextFormat("%d", x_axis_values[i]), in_pos, FONT_SIZE, 0.0f, BLACK);
		DrawTextEx(font, TextFormat("%d", graph->y_axis_values[i]), out_pos, FONT_SIZE, 0.0f, BLACK);

		// draw points
		DrawCircleV(graph->point[i].point, POINT_R, BLUE);
		graph->point[i].point.x = x + POINT_X_FIX + POINT_R*2; // graph_x + fix x + d
	}
}

//#define GRAPH_POINT_MAX 6
//#define X_AXIS_MAX x_axis_values[5]
//#define X_AXIS_MIN x_axis_values[0]
//#define Y_AXIS_MAX y_axis_values[5]
//#define Y_AXIS_MIN y_axis_values[0]
//#define SECOND 12 // 60 -> 1 segundo
//#define FONT_SIZE 15
//
//typedef struct {
//	int x;
//	int y;
//	float input;
//	Vector2 point[GRAPH_POINT_MAX];
//} graph_t;
//
//static int x_axis_values[6] = { 0, 1, 2, 3, 4, 5 };
//static int y_axis_values[6] = { 0, 1, 2, 3, 4, 5 };
//static Vector2 point[6] = {0}; 
//static int input_value = 0;
//unsigned long time = 0;
//
//static int slopi = 0;
//// solo nos enfocamos en los valores de salida, ya que la entrada (tiempo en s) siempre es positiva y va
//// en constante aumento
//static inline void IncreaseYAxis(void) {
//	while (Y_AXIS_MAX != input_value)
//		for (int i = 0; i < 6; ++i)
//			y_axis_values[i]++;
//}
//
//static inline void DecreaseYAxis(void) {
//	while (Y_AXIS_MIN != input_value)
//		for (int i = 0; i < 6; ++i)
//			y_axis_values[i]--;
//}
//
//void Graph_logic(const int input) {
//	input_value = input;
//
//	if (time == SECOND) {
//		for (int i = 0; i < 6; ++i)
//			x_axis_values[i]++;
//		time = 0;
//	}else
//		(++time) / 60;
//	// aumentar o disminuir las salidas
//	if (input_value > Y_AXIS_MAX)
//		IncreaseYAxis();
//	else if (input_value < Y_AXIS_MIN)
//		DecreaseYAxis();
//}
//
//static int poi = 0;
//void Graph_draw(int x, int y) {
//	// dibujar ejes x e y
//	DrawLine(x, y, 250+x, y, BLACK);  // x
//	DrawLine(x, y, x, y-170, BLACK); // y
//	// dibujar las entradas y salidas
//	// x
//	for (int i = 0; i < 6; ++i) {
//		Vector2 vec = {x + FONT_SIZE*i*3.0f, y};
//		//Vector2 vecText = {x + 200, y + 15};
//		//Vector2 vecText2 = {x-100, y - 200};
//		DrawTextEx(font, TextFormat("%d", x_axis_values[i]), vec, FONT_SIZE, 0.0f, BLACK);
//		//DrawTextEx(font, "200 [ms]", vecText, 15.0f, 1.0f, BLACK);
//		//DrawTextEx(font, "Voltaje [V]", vecText2, 15.0f, 1.0f, BLACK);
//	}
//	// y
//	for (int i = 0; i < 6; ++i) {
//		Vector2 vec = { x-FONT_SIZE*2.0f, y - FONT_SIZE*i*2.0f - FONT_SIZE };
//		DrawTextEx(font, TextFormat("%d", y_axis_values[i]), vec, FONT_SIZE, 0.0f, BLACK);
//	}
//
//
//	// point[poi].y -= y;
//	if (input_value <= 5)
//		point[poi].y = y - (input_value * 2.0f * FONT_SIZE - FONT_SIZE) - 10.0f - FONT_SIZE;
//	else
//		point[poi].y = y - (5 * 2.0f * FONT_SIZE - FONT_SIZE) - 10.0f - FONT_SIZE;
//	for(int i = 0; i < 6; ++i) {
//		DrawCircleV(point[i], 5.0f, BLUE);
//		point[i].x = x + FONT_SIZE * i * 3.0f + 5.0f;
//	}
//	for(int i = 0; i < 5; ++i)
//		DrawLine(point[i].x, point[i].y, point[i+1].x, point[i+1].y, RED);
//
//	if (poi < 6)
//		++poi;
//	else
//		poi = 0;
//}
