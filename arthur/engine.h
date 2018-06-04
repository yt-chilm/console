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
void engine_clear_backbuffer(void);
void engine_kill_backbuffer(void);

MESH* engine_new_mesh(char *pname, int vertexcount);
void engine_kill_mesh(MESH *pmesh);

CAMERA* engine_new_camera(void);
void engine_kill_camera(CAMERA *pcamera);
