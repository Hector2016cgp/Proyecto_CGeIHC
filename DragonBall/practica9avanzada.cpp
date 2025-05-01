
/*
Animación:
Sesión 1:
Simple o básica:Por banderas y condicionales (más de 1 transformación geométrica se ve modificada
Sesión 2
Compleja: Por medio de funciones y algoritmos.
Textura Animada
Mas de dos transformaciones para considerarse animación
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float movCoche;
float movOffset;
float rotllanta;
float rotllantaOffset;
bool avanza;
//variables movimiento del tren
const float startX = 0.0f;   //donde arranca en X
const float startZ = 0.0f;   //donde arranca en Z

const float lenNegZ = 74.0f;   //cuánto avanza hacia −Z
const float lenPosX = 74.0f;   //cuánto avanza hacia +X
const float lenPosZ = 74.0f;   //cuánto avanza hacia +Z
const float lenNegX = 74.0f;   //cuánto avanza hacia −X


const float limNegZ = startZ - lenNegZ;   
const float limPosX = startX + lenPosX;    
const float limPosZ = startZ + lenPosZ;    
const float limNegX = startX - lenNegX;    


float movXTrain = startX;
float movZTrain = startZ;
float trainRotation = 0.0f;
//variables movimiento de shenron y planeta
float shenronYOffset = 0.0f;
float shenronFloatSpeed = 1.0f;
float shenronFloatRange = 1.0f;
float planetaRotation = 0.0f;
float planetaRotationSpeed = 0.05f;
enum TrainDirection { TO_NEGATIVE_Z, TO_POSITIVE_X, TO_POSITIVE_Z, TO_NEGATIVE_X };
TrainDirection currentDirection = TO_NEGATIVE_Z;

//variables para el movimiento de la androide
float androideOffset = 0.0f;
float startAndroideX = -40.0f;
float startAndroideZ = -30.0f;
float movXAndroide = 0.0f;
float movZAndroide = 0.0f;
float androideRotation = 0.0f;
enum AndroideDirection { ANDROIDE_TO_NEGATIVE_Z, ANDROIDE_TO_POSITIVE_X, ANDROIDE_TO_POSITIVE_Z, ANDROIDE_TO_NEGATIVE_X };
AndroideDirection currentAndroideDirection = ANDROIDE_TO_NEGATIVE_Z;

// Límites para el movimiento del androide (puedes ajustarlos)
const float androideLenNegZ = 10.0f;
const float androideLenPosX = 10.0f;
const float androideLenPosZ = 10.0f;
const float androideLenNegX = 10.0f;

const float androideLimNegZ = startAndroideZ - androideLenNegZ;
const float androideLimPosX = startAndroideX + androideLenPosX;
const float androideLimPosZ = startAndroideZ + androideLenPosZ;
const float androideLimNegX = startAndroideX - androideLenNegX;


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;




Model Kitt_M;
Model Llanta_M;
Model shenron;
Model mapa;
Model goku;
Model tickets;
Model thomas;
Model planeta;
Model casa_capsula;
Model nave;
Model androide;
Model casa_kame;
Model coche;
Model namek;
Model casa;
Model broly;
Model radar;

Skybox skybox;
//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";



//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};
	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};


	unsigned int flechaIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat flechaVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int scoreIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat scoreVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int numeroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat numeroVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.25f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.25f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(flechaVertices, flechaIndices, 32, 6);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(scoreVertices, scoreIndices, 32, 6);
	meshList.push_back(obj6);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(numeroVertices, numeroIndices, 32, 6);
	meshList.push_back(obj7);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}




int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	

	mapa = Model();
	mapa.LoadModel("Models/mapa_preeliminar_cinco.obj");

	//MODELOS DRAGON BALL
	
	
	shenron = Model();
	shenron.LoadModel("Models/shenron.obj");
	goku = Model();
	goku.LoadModel("Models/goku.obj");
	tickets = Model();
	tickets.LoadModel("Models/tickets.obj");
	thomas = Model();
	thomas.LoadModel("Models/thomas.obj");
	planeta = Model();
	planeta.LoadModel("Models/planeta.obj");
	casa_capsula = Model();
	casa_capsula.LoadModel("Models/casa_capsula.obj");
	casa_kame = Model();
	casa_kame.LoadModel("Models/casa_kame.obj");
	nave = Model();
	nave.LoadModel("Models/nave_namek.obj");
	androide = Model();
	androide.LoadModel("Models/androide.obj");
	coche = Model();
	coche.LoadModel("Models/coche.obj");
	namek = Model();
	namek.LoadModel("Models/namek.obj");
	casa = Model();
	casa.LoadModel("Models/casa.obj");
	broly = Model();
	broly.LoadModel("Models/broly.obj");
	radar = Model();
	radar.LoadModel("Models/Radar.obj");


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 2.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;


	pointLights[1] = PointLight(1.0f, 0.5f, 0.0f,  // Color naranja (R=1.0, G=0.5, B=0.0)
		1.0f, 2.0f,  // Intensidades
		-85.0f, 3.0f, -35.0f,  // Posición (misma que Shenron)
		0.3f, 0.2f, 0.1f);
	pointLightCount++;


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	movCoche = 0.0f;
	movOffset = 0.3f;
	rotllanta = 0.0f;
	rotllantaOffset = 10.0f;
	avanza = true;

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

	
		//MOVIMIENTO TREN

		float trainSpeed = 0.5f;     //velocidd de movimiento
		float rotationY_rad = glm::radians(trainRotation);

		switch (currentDirection) {
		case TO_NEGATIVE_Z:
			movZTrain -= trainSpeed * deltaTime;
			if (movZTrain <= limNegZ) {
				movZTrain = limNegZ;
				currentDirection = TO_POSITIVE_X;
				trainRotation = -90.0f;  //rotar a -x
			}
			break;

		case TO_POSITIVE_X:
			movXTrain += trainSpeed * deltaTime;
			if (movXTrain >= limPosX) {
				movXTrain = limPosX;
				currentDirection = TO_POSITIVE_Z;
				trainRotation = 180.0f;  //rotar a z
			}
			break;

		case TO_POSITIVE_Z:
			movZTrain += trainSpeed * deltaTime;
			if (movZTrain >= limPosZ) {
				movZTrain = limPosZ;
				currentDirection = TO_NEGATIVE_X;
				trainRotation = 90.0f;  //rotar a -x
			}
			break;

		case TO_NEGATIVE_X:
			movXTrain -= trainSpeed * deltaTime;
			if (movXTrain <= limNegX) {
				movXTrain = limNegX;
				currentDirection = TO_NEGATIVE_Z;
				trainRotation = 0.0f;  //rota a -z
			}
			break;
		}

		//animación de la androide

		float androideSpeed = 0.05f;  // Velocidad más lenta que el tren

		switch (currentAndroideDirection) {
		case ANDROIDE_TO_NEGATIVE_Z:
			movZAndroide -= androideSpeed * deltaTime;
			if (movZAndroide <= androideLimNegZ) {
				movZAndroide = androideLimNegZ;
				currentAndroideDirection = ANDROIDE_TO_POSITIVE_X;
				androideRotation = 90.0f;
			}
			break;

		case ANDROIDE_TO_POSITIVE_X:
			movXAndroide += androideSpeed * deltaTime;
			if (movXAndroide >= androideLimPosX) {
				movXAndroide = androideLimPosX;
				currentAndroideDirection = ANDROIDE_TO_POSITIVE_Z;
				androideRotation = 0.0f;
			}
			break;

		case ANDROIDE_TO_POSITIVE_Z:
			movZAndroide += androideSpeed * deltaTime;
			if (movZAndroide >= androideLimPosZ) {
				movZAndroide = androideLimPosZ;
				currentAndroideDirection = ANDROIDE_TO_NEGATIVE_X;
				androideRotation = -90.0f;
			}
			break;

		case ANDROIDE_TO_NEGATIVE_X:
			movXAndroide -= androideSpeed * deltaTime;
			if (movXAndroide <= androideLimNegX) {
				movXAndroide = androideLimNegX;
				currentAndroideDirection = ANDROIDE_TO_NEGATIVE_Z;
				androideRotation = 180.0f;
			}
			break;
		}

		


		//movimiento shenron
		shenronYOffset = sin(now * shenronFloatSpeed) * shenronFloatRange;
		

		//animación del planeta (rotación)
		planetaRotation += planetaRotationSpeed * deltaTime;
		if (planetaRotation > 360.0f) {
			planetaRotation -= 360.0f;
		}



		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		
		
		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
	

		

		
		//MAPA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mapa.RenderModel();
		modelaux = model;
		//SHENRON
		model = glm::translate(model, glm::vec3(-85.0f, 3.0f + shenronYOffset, -35.0f)); // Agregar shenronYOffset
		model = glm::scale(model, glm::vec3(0.1f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		shenron.RenderModel();
		model = modelaux;
		//goku
		modelaux = model;
		model = glm::translate(model, glm::vec3(-55.0f, 1.4f, -8.2f));
		model = glm::scale(model, glm::vec3(2.0f));  // Puedes ajustar aquí
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		goku.RenderModel();
		//tickets
		modelaux = model;
		model = glm::translate(model, glm::vec3(-55.0f, 1.3f, -8.0f));
		model = glm::scale(model, glm::vec3(0.5f));  // Puedes ajustar aquí
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		tickets.RenderModel();
		//planeta
		modelaux = model;
		model = glm::translate(model, glm::vec3(-25.0f, 40.0f, -100.0f));
		model = glm::rotate(model, glm::radians(planetaRotation), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación en Y
		model = glm::scale(model, glm::vec3(0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		planeta.RenderModel();
		model = modelaux;
		//NAVES
		modelaux = model;
		model = glm::translate(model, glm::vec3(-75.0f, 30.0f, -60.0f));
		model = glm::scale(model, glm::vec3(1.0f));  // Puedes ajustar aquí
		model = glm::rotate(model, glm::radians(80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		nave.RenderModel();


		modelaux = model;
		model = glm::translate(model, glm::vec3(-55.0f, 50.0f, -60.0f));
		model = glm::scale(model, glm::vec3(1.0f));  // Puedes ajustar aquí
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		nave.RenderModel();


		modelaux = model;
		model = glm::translate(model, glm::vec3(-45.0f, 60.0f, -30.0f));
		model = glm::scale(model, glm::vec3(1.0f));  // Puedes ajustar aquí
		model = glm::rotate(model, glm::radians(100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		nave.RenderModel();
		//CASA GRANDE
		modelaux = model;
		model = glm::translate(model, glm::vec3(-25.0f, 1.2f, -64.0f));
		model = glm::scale(model, glm::vec3(0.05f));  // Puedes ajustar aquí
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		casa_capsula.RenderModel();

		modelaux = model;
		model = glm::translate(model, glm::vec3(-35.0f, 5.0f, -100.0f));
		model = glm::scale(model, glm::vec3(5.0f));  // Puedes ajustar aquí
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		casa_kame.RenderModel();

		modelaux = model;
		model = glm::translate(model, glm::vec3(movXAndroide, 20.0f, movZAndroide));  // Usa las variables de movimiento
		model = glm::rotate(model, glm::radians(androideRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		androide.RenderModel();
		model = modelaux;

		modelaux = model;
		model = glm::translate(model, glm::vec3(-35.0f, 1.5f, -20.0f));
		model = glm::scale(model, glm::vec3(0.1f));  // Puedes ajustar aquí
		model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		coche.RenderModel();

		modelaux = model;
		model = glm::translate(model, glm::vec3(-55.0f, -2.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.5f));  // Puedes ajustar aquí
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		namek.RenderModel();
		
		//broly
		modelaux = model;
		model = glm::translate(model, glm::vec3(-61.0f, 12.2f, -20.0f));
		model = glm::scale(model, glm::vec3(1.0f));  // Puedes ajustar aquí
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		broly.RenderModel();

		modelaux = model;
		model = glm::translate(model, glm::vec3(-55.0f, 0.0f, -55.0f));
		model = glm::scale(model, glm::vec3(0.5f));  // Puedes ajustar aquí
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		casa.RenderModel();

		modelaux = model;
		model = glm::translate(model, glm::vec3(-45.0f, 1.3f, -45.0f));
		model = glm::scale(model, glm::vec3(3.0f));  // Puedes ajustar aquí
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		radar.RenderModel();

		modelaux = model;
		model = glm::translate(model, glm::vec3(-25.0f, 1.3f, -45.0f));
		model = glm::scale(model, glm::vec3(3.0f));  // Puedes ajustar aquí
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		radar.RenderModel();

		modelaux = model;
		model = glm::translate(model, glm::vec3(-35.0f, 1.3f, -55.0f));
		model = glm::scale(model, glm::vec3(3.0f));  // Puedes ajustar aquí
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		radar.RenderModel();


		//tren
		glm::mat4 modelTrain = glm::mat4(1.0f);
		modelTrain = glm::translate(modelTrain, glm::vec3(movXTrain, 0.5f, movZTrain));
		modelTrain = glm::rotate(modelTrain, glm::radians(trainRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTrain = glm::scale(modelTrain, glm::vec3(2.0f));  // tu factor de escala

		// 3) Enviar al shader y renderizar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelTrain));
		thomas.RenderModel();
		
	



		


		glDisable(GL_BLEND);





		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}