#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "raylib.h"
#include "g_time.h"

#define GRAPH_POINT_MAX 6

typedef struct {
	int value;
	Vector2 point;
} point_t;

typedef struct {
	int x;
	int y;
	int y_axis_values[6];
	unsigned int adv;
	point_t point[GRAPH_POINT_MAX];
} graph_t;

void Graph_init(graph_t* graph, int x, int y);
void Graph_logic(graph_t* graph, const int value);
void Graph_draw(graph_t* graph);

#endif // _GRAPH_H_