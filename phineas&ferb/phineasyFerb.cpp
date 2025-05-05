
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
enum TrainDirection { TO_NEGATIVE_Z, TO_POSITIVE_X, TO_POSITIVE_Z, TO_NEGATIVE_X };
TrainDirection currentDirection = TO_NEGATIVE_Z;

float tiempoCarrusel = 0.0f;
float ballonyTime = 0.0f;
const float ballonySpeed = 0.01f;       // Controla la velocidad
const float ballonyAmplitudeY = 3.0f;  // Oscilación Y 
const float ballonyAmplitudeZ = 10.0f; // Oscilación Z 
const float ballonyAmplitudeX = 5.0f; // Oscilación X

float ferbHandTime = 0.0f;  // Tiempo acumulado
float phineasHandTime = 0.0f;



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

//Modelos Phineas y Ferb
Model edificioDoof_M;
Model Ferb_M;
Model Perry_M;
Model Phineas_M;
Model Candace_M;
Model Isabella_M;
Model Bufard_M;
Model Baljeet_M;
Model Doof_M;
Model topo_machine_M;
Model planty_M;
Model ballony_M;
Model phineasHouse_M;
Model reja_madera_M;
Model arbol_phineas_M;
Model carrusel_M;
Model carpa_perry_M;
Model mesa_perry_M;
Model letrero_perry_juego_M;
Model techo_carrusel_M;
Model nave1_M;
Model nave2_M;
Model nave3_M;
Model nave4_M;
Model nave5_M;
Model nave6_M;
Model toilet_phineas_M;
Model decoracion_M;
Model puesto_tacos_M;
Model puesto_miches_M;
Model Ferb_mano_M;
Model Phineas_mano_M;

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


	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	mapa = Model();
	mapa.LoadModel("Models/mapa_preeliminar_cinco.obj");
	shenron = Model();
	shenron.LoadModel("Models/shenron.obj");
	goku = Model();
	goku.LoadModel("Models/goku.obj");
	tickets = Model();
	tickets.LoadModel("Models/tickets.obj");
	thomas = Model();
	thomas.LoadModel("Models/thomas.obj");
	edificioDoof_M = Model();
	edificioDoof_M.LoadModel("Models/EdificioDoof.obj");
	Ferb_M = Model();
	Ferb_M.LoadModel("Models/ferb.obj");
	Perry_M = Model();
	Perry_M.LoadModel("Models/perry.obj");
	Phineas_M = Model();
	Phineas_M.LoadModel("Models/phineas.obj");
	Candace_M = Model();
	Candace_M.LoadModel("Models/candace.obj");
	Isabella_M = Model();
	Isabella_M.LoadModel("Models/isabella.obj");
	Baljeet_M = Model();
	Baljeet_M.LoadModel("Models/baljeet.obj");
	Bufard_M = Model();
	Bufard_M.LoadModel("Models/bufard.obj");
	Doof_M = Model();
	Doof_M.LoadModel("Models/doof.obj");
	topo_machine_M = Model();
	topo_machine_M.LoadModel("Models/topo_machine.obj");
	planty_M = Model();
	planty_M.LoadModel("Models/planty.obj");
	ballony_M = Model();
	ballony_M.LoadModel("Models/balloony.obj");
	phineasHouse_M = Model();
	phineasHouse_M.LoadModel("Models/phineasHouse.obj");
	reja_madera_M = Model();
	reja_madera_M.LoadModel("Models/reja_madera.obj");
	arbol_phineas_M = Model();
	arbol_phineas_M.LoadModel("Models/arbol_phineas.obj");
	carrusel_M = Model();
	carrusel_M.LoadModel("Models/carrusel.obj");
	techo_carrusel_M = Model();
	techo_carrusel_M.LoadModel("Models/techo_carrusel.obj");
	nave1_M = Model();
	nave1_M.LoadModel("Models/nave1.obj");
	nave2_M = Model();
	nave2_M.LoadModel("Models/nave2.obj");
	nave3_M = Model();
	nave3_M.LoadModel("Models/nave3.obj");
	nave4_M = Model();
	nave4_M.LoadModel("Models/nave4.obj");
	nave5_M = Model();
	nave5_M.LoadModel("Models/nave5.obj");
	nave6_M = Model();
	nave6_M.LoadModel("Models/nave6.obj");
	carpa_perry_M = Model();
	carpa_perry_M.LoadModel("Models/carpa_perry.obj");
	mesa_perry_M = Model();
	mesa_perry_M.LoadModel("Models/mesa_perry.obj");
	letrero_perry_juego_M = Model();
	letrero_perry_juego_M.LoadModel("Models/letrero_perry_juego.obj");
	toilet_phineas_M = Model();
	toilet_phineas_M.LoadModel("Models/toilet_phineas.obj");
	decoracion_M = Model();
	decoracion_M.LoadModel("Models/decoracion.obj");
	puesto_tacos_M = Model();
	puesto_tacos_M.LoadModel("Models/puesto_tacos.obj");
	puesto_miches_M = Model();
	puesto_miches_M.LoadModel("Models/puesto_miches.obj");
	Ferb_mano_M = Model();
	Ferb_mano_M.LoadModel("Models/ferb_mano_der.obj");
	Phineas_mano_M = Model();
	Phineas_mano_M.LoadModel("Models/phineas_mano_izq.obj");


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
		tiempoCarrusel += deltaTime;
		ballonyTime += deltaTime;
		ferbHandTime += deltaTime;
		phineasHandTime += deltaTime;


		// Movimiento
		float posX = -40.0f + cos(ballonyTime * ballonySpeed * 0.7f) * ballonyAmplitudeX;
		float posY = 20.0f + sin(ballonyTime * ballonySpeed) * ballonyAmplitudeY;
		float posZ = 35.0f + sin(ballonyTime * ballonySpeed * 0.5f) * ballonyAmplitudeZ;


	

		if (avanza) {
			if (movCoche > -50.0f)
			{
				movCoche -= movOffset * deltaTime;
				//printf("avanza%f \n ",movCoche);
				rotllanta += rotllantaOffset * deltaTime;
			}
			else {
				avanza = false;
			}
		}
		else {
			if (movCoche < 50.0f)
			{
				movCoche += movOffset * deltaTime;
				//printf("avanza%f \n ",movCoche);
				rotllanta -= rotllantaOffset * deltaTime;
			}
			else {
				avanza = true;
			}
		}


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
	

		

		

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mapa.RenderModel();
		modelaux = model;
		model = glm::translate(model, glm::vec3(-40.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(0.1f));  // Puedes ajustar aquí
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		shenron.RenderModel();
		//goku
		modelaux = model;
		model = glm::translate(model, glm::vec3(-60.0f, 1.2f, -8.2f));
		model = glm::scale(model, glm::vec3(8.0f));  // Puedes ajustar aquí
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		goku.RenderModel();
		//tickets
		modelaux = model;
		model = glm::translate(model, glm::vec3(-60.0f, 0.9f, -8.0f));
		model = glm::scale(model, glm::vec3(2.0f));  // Puedes ajustar aquí
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		tickets.RenderModel();

		//tren
		glm::mat4 modelTrain = glm::mat4(1.0f);
		modelTrain = glm::translate(modelTrain, glm::vec3(movXTrain, 0.5f, movZTrain));
		modelTrain = glm::rotate(modelTrain, glm::radians(trainRotation), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTrain = glm::scale(modelTrain, glm::vec3(2.0f));  // tu factor de escala
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelTrain));
		thomas.RenderModel();


		//EDIFICIO DE DOOF
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-60.0f, 1.2f, 60.0f));
		model = glm::scale(model, glm::vec3(8.0f)); 
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		edificioDoof_M.RenderModel();
		
		//Ferb
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-45.0f, 1.3f, 30.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ferb_M.RenderModel();

		// Ferb mano derecha 
		float angleSaludo = sin(ferbHandTime * 0.25f) * 20.0f; // Oscila entre -20 y +20 grados
		modelaux = model; // guarda el modelo base
		model = glm::translate(model, glm::vec3(-0.169f, 0.942f, 0.019f)); // punto de unión al hombro
		model = glm::rotate(model, glm::radians(angleSaludo), glm::vec3(0.0f, 0.0f, 1.0f)); // rotación de saludo
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ferb_mano_M.RenderModel();

	
		//Perry
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-45.0f, 1.3f, 26.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Perry_M.RenderModel();

		// Phineas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-47.0f, 1.2f, 5.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Phineas_M.RenderModel();
		// Phineas mano izquierda
		float anglePhineasSaludo = sin(phineasHandTime * 0.25f) * 25.0f;
		modelaux = model; // Guarda la transformación base
		model = glm::translate(model, glm::vec3(0.126f, 0.912f, 0.035f)); // Punto de unión del brazo
		model = glm::rotate(model, glm::radians(anglePhineasSaludo), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotación tipo saludo
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Phineas_mano_M.RenderModel();


		
		//Candace
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, 1.2f, 20.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Candace_M.RenderModel();

		//Isabella
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 1.2f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Isabella_M.RenderModel();

		//Bufard
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-26.0f, 1.2f, 64.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bufard_M.RenderModel();

		//Baljeet
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, 1.2f, 40.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Baljeet_M.RenderModel();

		//Doof
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 1.2f, 64.0f));
		model = glm::rotate(model, glm::radians(130.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Doof_M.RenderModel();


		//Maquina de perry
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-45.0f, 1.2f, 22.0f));
		model = glm::scale(model, glm::vec3(0.75f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		topo_machine_M.RenderModel();

		//Carpa Perry
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-45.0f, 1.2f, 20.0f));
		model = glm::scale(model, glm::vec3(0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		carpa_perry_M.RenderModel();

		//mesa Perry
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-45.0f, 1.2f, 19.0f));
		model = glm::scale(model, glm::vec3(0.75f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mesa_perry_M.RenderModel();

		//letrero perry
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-43.0f, 1.2f, 18.0f));
		model = glm::scale(model, glm::vec3(0.75f));
		model = glm::rotate(model, glm::radians(-80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		letrero_perry_juego_M.RenderModel();
		

		//Planty
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-55.0f, 1.2f, 8.0f));
		model = glm::scale(model, glm::vec3(0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		planty_M.RenderModel();

		//Ballony
		float ballonySpinAngle = fmod(ballonyTime * 0.5f, 360.0f); // velocidad baja
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::scale(model, glm::vec3(3.0f));
		model = glm::rotate(model, glm::radians(ballonySpinAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // rotación 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ballony_M.RenderModel();


		
		//Casa Phineas & Ferb 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-60.0f, 1.2f, 40.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		phineasHouse_M.RenderModel();

		//reja_phineas 
		for (int i = 0; i < 10; i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-12.0f - 2.0f * i, 1.2f, 55.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			reja_madera_M.RenderModel();
		}

		//reja_phineas 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-38.0f, 1.2f, 42.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		for (int i = 0; i < 16; ++i) {
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			reja_madera_M.RenderModel();

			// Aplica salto normal de 2.0f o salto especial de 8.0f en el lugar 12
			float salto = (i == 11) ? 8.0f : 2.0f;
			model = glm::translate(model, glm::vec3(salto, 0.0f, 0.0f));
		}





		//toilet phineas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-18.0f, 1.2f, 62.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		toilet_phineas_M.RenderModel();
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		toilet_phineas_M.RenderModel();

		//toilet phineas 
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(-45.0f, 1.2f, 10.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		toilet_phineas_M.RenderModel();
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		toilet_phineas_M.RenderModel();

		//decoracion
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-58.0f, 1.2f, 3.0f));
		model = glm::scale(model, glm::vec3(3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		decoracion_M.RenderModel();
		
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		decoracion_M.RenderModel();
		
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		decoracion_M.RenderModel();

		//puesto tacos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-45.0f, 1.2f, 50.0f));
		model = glm::scale(model, glm::vec3(0.75f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puesto_tacos_M.RenderModel();

		//puesto micheladas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 1.2f, 62.0f));
		model = glm::scale(model, glm::vec3(0.75f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puesto_miches_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, 1.2f, 15.0f));
		model = glm::scale(model, glm::vec3(0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puesto_miches_M.RenderModel();

		//arbol_phineas 
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(2.0f));
		modelaux = model;
		model = glm::translate(model, glm::vec3(-30.0f, 0.7f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_phineas_M.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(-29.0f, 0.7f, 25.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_phineas_M.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(-13.5f, 0.7f, 17.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_phineas_M.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(-17.5f, 0.7f, 33.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbol_phineas_M.RenderModel();

		// Base del carrusel (fija)
		glm::mat4 modelCarrusel = glm::mat4(1.0f);
		float anguloCarrusel = fmod(tiempoCarrusel * 1.5f, 360.0f); // 18 grados por segundo
		modelCarrusel = glm::translate(glm::mat4(1.0f), glm::vec3(-30.0f, 1.2f, 45.0f));
		modelCarrusel = glm::scale(modelCarrusel, glm::vec3(0.75f));
		modelCarrusel = glm::rotate(modelCarrusel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCarrusel));
		carrusel_M.RenderModel();
		modelCarrusel = glm::rotate(modelCarrusel, glm::radians(anguloCarrusel), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCarrusel));
		techo_carrusel_M.RenderModel();
		
		const float VELOCIDAD_OSCILACION_NAVES = 0.05f;
		const float AMPLITUD_OSCILACION_NAVES = 0.3f;
		const float ALTURA_BASE_NAVES = 1.5f;

		for (int i = 0; i < 6; i++) {
			float offsetY = sin(tiempoCarrusel * VELOCIDAD_OSCILACION_NAVES + i) * AMPLITUD_OSCILACION_NAVES;

			glm::mat4 naveModel = glm::mat4(1.0f);
			naveModel = glm::translate(naveModel, glm::vec3(-30.0f, ALTURA_BASE_NAVES + offsetY, 45.0f));
			naveModel = glm::scale(naveModel, glm::vec3(0.75f));
			naveModel = glm::rotate(naveModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			naveModel = glm::rotate(naveModel, glm::radians(anguloCarrusel), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(naveModel));

			switch (i) {
			case 0: nave1_M.RenderModel(); break;
			case 1: nave2_M.RenderModel(); break;
			case 2: nave3_M.RenderModel(); break;
			case 3: nave4_M.RenderModel(); break;
			case 4: nave5_M.RenderModel(); break;
			case 5: nave6_M.RenderModel(); break;
			}
		}





		



		glDisable(GL_BLEND);





		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}