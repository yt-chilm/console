#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "math_3d.h"
#include "engine.h"

BUFFER* engine_init_backbuffer(int w, int h) {
	BUFFER *pbackbuffer = malloc(sizeof(BUFFER));
	pbackbuffer->width = w;
	pbackbuffer->height = h;
	pbackbuffer->pdata = calloc(w * h, sizeof(char));
	return pbackbuffer;
}

void engine_clear_backbuffer(BUFFER *pbackbuffer) {
	memset(pbackbuffer->pdata, 0, pbackbuffer->width * pbackbuffer->height);
}

void engine_kill_backbuffer(BUFFER *pbackbuffer) {
	free(pbackbuffer->pdata);
	free(pbackbuffer);
	pbackbuffer=0;
}

MESH* engine_new_mesh(char *pname, int vertexcount) {
	MESH *pmesh = malloc(sizeof(MESH));

	pmesh->pname = malloc(strlen(pname));
	strcpy(pmesh->pname, pname);

	pmesh->pvertices = malloc(sizeof(vec3_t)*vertexcount);
	pmesh->pvertices[0] = vec3(-1, 1, 1);
	pmesh->pvertices[1] = vec3(1, 1, 1);
	pmesh->pvertices[2] = vec3(-1, -1, 1);
	pmesh->pvertices[3] = vec3(-1, -1, -1);
	pmesh->pvertices[4] = vec3(-1, 1, -1);
	pmesh->pvertices[5] = vec3(1, 1, -1);
	pmesh->pvertices[6] = vec3(1, -1, 1);
	pmesh->pvertices[7] = vec3(1, -1, -1);

	pmesh->position = vec3(0,0,0);
	pmesh->rotation = vec3(0,0,0);

	return pmesh;
}

void engine_kill_mesh(MESH *pmesh) {
	free(pmesh->pname);
	free(pmesh->pvertices);
	free(pmesh);
	pmesh = 0;
}

CAMERA* engine_new_camera(void) {
	CAMERA *pcamera = malloc(sizeof(CAMERA));
	pcamera->position = vec3(0,0,10);
	pcamera->target = vec3(0,0,0);
	return pcamera;
}

void engine_kill_camera(CAMERA *pcamera) {
	free(pcamera);
	pcamera = 0;
}

void engine_draw_point(vec3_t *point, BUFFER *pbuffer) {
	if(point->x >= 0 && point->y >= 0 && point->x <= pbuffer->width && point->y <= pbuffer->height) {
		pbuffer->pdata[(int)(point->x + (point->y*pbuffer->width))] = 1;
	}
}

void engine_draw(CAMERA *pcamera, MESH *pmeshes, BUFFER *pbuffer) {
	vec3_t up = vec3(0, 1, 0);
	mat4_t transform = m4_look_at(pcamera->position, pcamera->target, up);
	mat4_t projection = m4_perspective(60,  pbuffer->width/pbuffer->height, 1, 10);
	mat4_t world_to_screen = m4_mul(transform, projection);

	for(int v=0; v<8; v++) {
		vec3_t vert = pmeshes->pvertices[v];

		mat4_t world_matrix = m4_identity();
		world_matrix = m4_mul(world_matrix, m4_rotation_x(pmeshes->rotation.x));
		world_matrix = m4_mul(world_matrix, m4_rotation_y(pmeshes->rotation.y));
		world_matrix = m4_mul(world_matrix, m4_rotation_z(pmeshes->rotation.z));
		world_matrix = m4_mul(world_matrix, m4_translation(pmeshes->position));
		//mat4_t transMatrix = m4_mul(world_matrix, m4_mul(transform, projection));
		mat4_t transMatrix = m4_mul(m4_mul(projection, transform), world_matrix);

		vec3_t point = m4_mul_pos(transMatrix, vert);

		point.x = point.x * pbuffer->width + pbuffer->width / 2.0f;
		point.y = -point.y * pbuffer->height + pbuffer->height / 2.0f;

		engine_draw_point(&point, pbuffer);
		mvprintw(2+v, 1, "vertex[%d] - x:%f, y:%f", v, point.x, point.y);
	}
}

void engine_render(WINDOW* pwindow, BUFFER* pdata) {
	for(int x=0; x<pdata->width; x++) {
		for(int y=0; y<pdata->height; y++) {
			if(pdata->pdata[x+(y*pdata->width)])
				mvwprintw(pwindow, y, x, "*");
		}
	}
}

