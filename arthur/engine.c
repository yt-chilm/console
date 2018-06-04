#ifndef _ENGINE_
#define _ENGINE_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "math_3d.h"
#include "engine.h"

BUFFER *pbackbuffer = 0;

BUFFER* engine_init_backbuffer(int w, int h) {
	pbackbuffer = malloc(sizeof(BUFFER));
	pbackbuffer->width = w;
	pbackbuffer->height = h;
	pbackbuffer->pdata = calloc(w * h, sizeof(char));
	return pbackbuffer;
}

void engine_clear_backbuffer(void) {
	memset(pbackbuffer, 0, pbackbuffer->width * pbackbuffer->height);
}

void engine_kill_backbuffer(void) {
	free(pbackbuffer);
	pbackbuffer=0;
}

MESH* engine_new_mesh(char *pname, int vertexcount) {
	MESH *pmesh = malloc(sizeof(MESH));

	pmesh->pname = malloc(strlen(pname));
	strcpy(pmesh->pname, pname);

	pmesh->pvertices = malloc(sizeof(vec3_t)*vertexcount);

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
	pcamera->position = vec3(0,0,0);
	pcamera->target = vec3(0,0,0);
	return pcamera;
}

void engine_kill_camera(CAMERA *pcamera) {
	free(pcamera);
	pcamera = 0;
}

#endif
