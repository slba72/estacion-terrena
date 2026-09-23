#include "graph.h"
#include "font.h"
#include <stdio.h>

#define GRAPH_MAX_Y 5
#define TIME_SEC 1 // 60 -> 1 segundo
#define X_AXIS_MAX x_axis_values[5]
#define X_AXIS_MIN x_axis_values[0]
#define GRAPH_WIDTH 250
#define GRAPH_HEIGHT 170
#define POINT_X_FIX (FONT_SIZE * i * 3)
#define POINT_Y_FIX (FONT_SIZE + (FONT_SIZE * i * 2))
#define POINT_R 5.0f

static int x_axis_values[6] = { 0, 1, 2, 3, 4, 5 };
unsigned char point_i = 0; 
// long point_i

// macro??
static inline void IncreaseYAxis(const int input, int* y_axis_values, int* adv) {
	while (y_axis_values[0] != input) {
		for (int i = 0; i < 6; ++i)
			y_axis_values[i]++;
		++(*adv);
	}
}

static inline void DecreaseYAxis(const int input, int* y_axis_values, int* adv) {
	while (y_axis_values[0] != input) {
		for (int i = 0; i < 6; ++i)
			y_axis_values[i]--;
		--(*adv);
	}
}

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
