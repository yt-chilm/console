
#ifndef _ENGINE_
#define _ENGINE_

typedef struct camera {
	vec3_t position;
	vec3_t target;
}CAMERA;

typedef struct mesh {
	char* pname;
	vec3_t *pvertices;
	vec3_t position;
	vec3_t rotation;
}MESH;

typedef struct buffer {
	char* pdata;
	int width;
	int height;
}BUFFER;

#define COL_CUBE 1

BUFFER* engine_init_backbuffer(int w, int h);
void engine_clear_backbuffer(BUFFER *pbackbuffer);
void engine_kill_backbuffer(BUFFER *pbackbuffer);

MESH* engine_new_mesh(char *pname, int vertexcount);
void engine_kill_mesh(MESH *pmesh);

CAMERA* engine_new_camera(void);
void engine_kill_camera(CAMERA *pcamera);

mat4_t engine_project(vec3_t coord, mat4_t trans);
void engine_draw(CAMERA *pcamera, MESH *pmeshes, BUFFER *pbuffer);
void engine_draw_point(vec3_t *point, BUFFER *pbuffer);
void engine_render(WINDOW* pwindow, BUFFER* pdata);

#endif
