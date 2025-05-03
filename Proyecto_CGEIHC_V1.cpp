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

//<--------------------------------DECLARACIÓN DE VARIABLES-------------------------------->
 
//*********************************PARA UNIVERSO DE DRAGON BALL*********************************

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


//*********************************PARA UNIVERSO DE RESIDENT EVIL*********************************

float alagiro;
bool gira;
float movDragon;
float dragongiro;
bool medicinaTomada = false;
glm::vec3 gPersonajePos(0.0f, 1.27f, -10.0f);  // Posición inicial de Leon Kennedy
float gPersonajeRotY = 0.0f;  // Rotación en Y (en grados)
float gVelocidadMovimiento = 15.0f;  // Velocidad de movimiento
float gVelocidadRotacion = 100.0f;  // Velocidad de rotación del personaje


//Para movimiento de las extremidades
float animacionTiempo = 0.0f;
float velocidadAnimacion = 4.0f; // controla qué tan rápido camina
float amplitudMovimiento = 11.0f; // grados de rotación de brazos y piernas


//Para zombie
float animacionTiempoZombie = 0.0f;
float velocidadAnimacionZombie = 4.0f;
float amplitudMovimientoZombie = 5.0f;


float movZombie = 0.0f;      // Movimiento en Z
bool avanzaZombie = true;    // Para saber si avanza o retrocede
float velocidadZombie = 2.0f; // Velocidad de movimiento del zombie

//Para medicina
float tiempoMedicina = 0.0f;
float velocidadFlotacion = 2.0f;  // Qué tan rápido sube y baja
float amplitudFlotacion = 0.3f;   // Qué tanto se mueve verticalmente
float tiempoAnimacionMano = 0.0f;
bool animandoManoPickup = false;

int tipoCamara = 0;
bool teclaC_presionada = false;
glm::vec3 camaraAereaPos(0.0f, 100.0f, 0.0f);  // justo arriba del centro
glm::vec3 camaraAereaTarget(0.0f, 0.0f, 0.0f); // mirando al centro
glm::vec3 camaraAereaUp(0.0f, 0.0f, -1.0f);    // eje Z negativo como "arriba"

//<--------------------------------FIN DECLARACIÓN DE VARIABLES-------------------------------->


//<--------------------------------INICIO DECLARACIÓN DE MODELOS-------------------------------->


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Skybox skybox;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;

//*********************************PARA UNIVERSO DE DRAGON BALL*********************************

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

//*********************************PARA UNIVERSO DE RESIDENT EVIL*********************************

//Para personaje Leon Kennedy
Model Cuerpo_Leon;
Model Brazo_izquierdo_Leon;
Model Brazo_derecho_Leon;
Model Pie_izquierdo_Leon;
Model Pie_derecho_Leon;

//Para rueda de la fortuna
Model RuedaFortuna_parteUno;
Model RuedaFortuna_parteDos;
Model RuedaFortuna_parteTres;

//Otros elementos de modelos
Model Mansion;
Model Mapa;
Model TiroHacha;
Model Torre;
Model Baño;
Model Tren;
Model Torre_Helicoptero;
Model Torre_Helicoptero_Dos;
Model Torre_Helicoptero_Tres;
Model Carro_Abandonado;
Model Cartel_Circo;


//Para zombies

Model Zombie_Dos_PiernaDerecha;
Model Zombie_Dos_PiernaIzquierda;
Model Zombie_Dos_Cuerpo;
Model Zombie_Dos_BrazoDerecho;
Model Zombie_Dos_BrazoIzquierdo;
Model Zombie_Dos_Cabeza;


//Para tanque
Model Tanque_Fusil;
Model Tanque_Capote;
Model Tanque_Cuerpo;
Model Tanque_LlantasDerechas;
Model Tanque_LlantasIzquierdas;

//Medicinas
Model Medicina;
std::vector<glm::vec3> posicionesMedicinas = {
	glm::vec3(19.214f, 2.209f, 14.423f),
	glm::vec3(25.73f, 2.209f, 21.245f),
	glm::vec3(30.0f, 2.209f, 10.0f), // más medicinas
	glm::vec3(40.0f, 2.209f, 15.0f)
};

std::vector<bool> medicinasTomadas(posicionesMedicinas.size(), false);

//materiales
Material Material_brillante;
Material Material_opaco;

//<--------------------------------FIN DECLARACIÓN DE MODELOS-------------------------------->


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat deltaTimeDos = 0.0f;
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

	//<--------------------------------INICIO LLAMADA DE MODELOS-------------------------------->
	
	//*********************************PARA UNIVERSO DE DRAGON BALL*********************************

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

	//*********************************PARA UNIVERSO DE RESIDENT EVIL*********************************
	
	Cuerpo_Leon = Model();
	Cuerpo_Leon.LoadModel("Models/Leon_Kennedy_cuerpo_completo.obj");

	Brazo_izquierdo_Leon = Model();
	Brazo_izquierdo_Leon.LoadModel("Models/Leon_Kennedy_brazo_izquierdo.obj");

	Brazo_derecho_Leon = Model();
	Brazo_derecho_Leon.LoadModel("Models/Leon_Kennedy_brazo_derecho.obj");

	Pie_izquierdo_Leon = Model();
	Pie_izquierdo_Leon.LoadModel("Models/Leon_Kennedy_pierna_izquierda.obj");

	Pie_derecho_Leon = Model();
	Pie_derecho_Leon.LoadModel("Models/Leon_Kennedy_pierna_derecha.obj");

	Mansion = Model();
	Mansion.LoadModel("Models/Mansion_evil.obj");

	TiroHacha = Model();
	TiroHacha.LoadModel("Models/tiro_hacha_v2.obj");

	Torre = Model();
	Torre.LoadModel("Models/torre.obj");

	Tren = Model();
	Tren.LoadModel("Models/tren_licker.obj");

	Baño = Model();
	Baño.LoadModel("Models/baño_RE.obj");

	Torre_Helicoptero = Model();
	Torre_Helicoptero.LoadModel("Models/torre_helicoptero.obj");

	Torre_Helicoptero_Dos = Model();
	Torre_Helicoptero_Dos.LoadModel("Models/torre_helicoptero_dos.obj");

	Torre_Helicoptero_Tres = Model();
	Torre_Helicoptero_Tres.LoadModel("Models/torre_helicoptero_tres.obj");

	Carro_Abandonado = Model();
	Carro_Abandonado.LoadModel("Models/carro.obj");

	Cartel_Circo = Model();
	Cartel_Circo.LoadModel("Models/cartel_circo.obj");

	// Carga de modelos para ruega de la fortuna

	RuedaFortuna_parteUno = Model();
	RuedaFortuna_parteUno.LoadModel("Models/rueda_fortuna_parte_una.obj");

	RuedaFortuna_parteDos = Model();
	RuedaFortuna_parteDos.LoadModel("Models/rueda_fortuna_parte_dos.obj");

	RuedaFortuna_parteTres = Model();
	RuedaFortuna_parteTres.LoadModel("Models/rueda_fortuna_parte_tres.obj");

	// Carga de modelos para zombies

	Zombie_Dos_PiernaDerecha = Model();
	Zombie_Dos_PiernaDerecha.LoadModel("Models/zombie_dos_piernaDerecha.obj");

	Zombie_Dos_PiernaIzquierda = Model();
	Zombie_Dos_PiernaIzquierda.LoadModel("Models/zombie_dos_piernaIzquierda.obj");

	Zombie_Dos_Cuerpo = Model();
	Zombie_Dos_Cuerpo.LoadModel("Models/zombie_dos_cuerpo.obj");

	Zombie_Dos_BrazoDerecho = Model();
	Zombie_Dos_BrazoDerecho.LoadModel("Models/zombie_dos_ManoDerecha.obj");

	Zombie_Dos_BrazoIzquierdo = Model();
	Zombie_Dos_BrazoIzquierdo.LoadModel("Models/zombie_dos_ManoIzquierda.obj");

	Zombie_Dos_Cabeza = Model();
	Zombie_Dos_Cabeza.LoadModel("Models/zombie_dos_cabeza.obj");

	//Para tanque 

	Tanque_Cuerpo = Model();
	Tanque_Cuerpo.LoadModel("Models/tanque_t34_cuerpo.obj");

	Tanque_Fusil = Model();
	Tanque_Fusil.LoadModel("Models/tanque_t34_fusil.obj");

	Tanque_Capote = Model();
	Tanque_Capote.LoadModel("Models/tanque_t34_capoteFusil.obj");

	Tanque_LlantasDerechas = Model();
	Tanque_LlantasDerechas.LoadModel("Models/tanque_t34_llantasDerechas.obj");

	Tanque_LlantasIzquierdas = Model();
	Tanque_LlantasIzquierdas.LoadModel("Models/tanque_t34_llantasIzquierdas.obj");

	//Para medicinas

	Medicina = Model();
	Medicina.LoadModel("Models/lata.obj");

	//<--------------------------------FIN LLAMADA DE MODELOS-------------------------------->

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


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	movCoche = 0.0f;
	movOffset = 0.3f;
	rotllanta = 0.0f;
	rotllantaOffset = 10.0f;
	avanza = true;

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTimeDos = now - lastTime;

		if (animandoManoPickup) {
			tiempoAnimacionMano += deltaTime;

			//Levantar la mano cada vez que se agarre una medicina
			if (tiempoAnimacionMano >= 0.5f) {
				animandoManoPickup = false;
				tiempoAnimacionMano = 0.0f;
			}
		}

		deltaTimeDos += (now - lastTime) / limitFPS;
		lastTime = now;


		//Para giro de rueda de la fortuna
		static float anguloRueda = 0.0f;
		anguloRueda += 20.0f * deltaTime;  // 20 grados por segundo
		if (anguloRueda > 360.0f) anguloRueda -= 360.0f;

		//Para animación de zombie RE
		animacionTiempoZombie += deltaTime * velocidadAnimacionZombie;

		//Para medicina RE
		tiempoMedicina += deltaTime * velocidadFlotacion;

		// Dirección hacia la que Leon está mirando
		glm::vec3 direccionFrontal;
		direccionFrontal.x = -sin(glm::radians(gPersonajeRotY));
		direccionFrontal.y = 0.0f;
		direccionFrontal.z = -cos(glm::radians(gPersonajeRotY));
		direccionFrontal = glm::normalize(direccionFrontal);

		//Para movimiento del tren
		float trainSpeed = 0.5f; //velocidad de movimiento
		float rotationY_rad = glm::radians(trainRotation);

		switch (currentDirection) {
		case TO_NEGATIVE_Z:
			movZTrain -= trainSpeed * deltaTimeDos;
			if (movZTrain <= limNegZ) {
				movZTrain = limNegZ;
				currentDirection = TO_POSITIVE_X;
				trainRotation = -90.0f;  //rotar a -x
			}
			break;

		case TO_POSITIVE_X:
			movXTrain += trainSpeed * deltaTimeDos;
			if (movXTrain >= limPosX) {
				movXTrain = limPosX;
				currentDirection = TO_POSITIVE_Z;
				trainRotation = 180.0f;  //rotar a z
			}
			break;

		case TO_POSITIVE_Z:
			movZTrain += trainSpeed * deltaTimeDos;
			if (movZTrain >= limPosZ) {
				movZTrain = limPosZ;
				currentDirection = TO_NEGATIVE_X;
				trainRotation = 90.0f;  //rotar a -x
			}
			break;

		case TO_NEGATIVE_X:
			movXTrain -= trainSpeed * deltaTimeDos;
			if (movXTrain <= limNegX) {
				movXTrain = limNegX;
				currentDirection = TO_NEGATIVE_Z;
				trainRotation = 0.0f;  //rota a -z
			}
			break;
		}

		//Para movimiento del androide

		float androideSpeed = 0.05f;  // Velocidad más lenta que el tren

		switch (currentAndroideDirection) {
		case ANDROIDE_TO_NEGATIVE_Z:
			movZAndroide -= androideSpeed * deltaTimeDos;
			if (movZAndroide <= androideLimNegZ) {
				movZAndroide = androideLimNegZ;
				currentAndroideDirection = ANDROIDE_TO_POSITIVE_X;
				androideRotation = 90.0f;
			}
			break;

		case ANDROIDE_TO_POSITIVE_X:
			movXAndroide += androideSpeed * deltaTimeDos;
			if (movXAndroide >= androideLimPosX) {
				movXAndroide = androideLimPosX;
				currentAndroideDirection = ANDROIDE_TO_POSITIVE_Z;
				androideRotation = 0.0f;
			}
			break;

		case ANDROIDE_TO_POSITIVE_Z:
			movZAndroide += androideSpeed * deltaTimeDos;
			if (movZAndroide >= androideLimPosZ) {
				movZAndroide = androideLimPosZ;
				currentAndroideDirection = ANDROIDE_TO_NEGATIVE_X;
				androideRotation = -90.0f;
			}
			break;

		case ANDROIDE_TO_NEGATIVE_X:
			movXAndroide -= androideSpeed * deltaTimeDos;
			if (movXAndroide <= androideLimNegX) {
				movXAndroide = androideLimNegX;
				currentAndroideDirection = ANDROIDE_TO_NEGATIVE_Z;
				androideRotation = 180.0f;
			}
			break;
		}

		//Para movimiento shenron
		shenronYOffset = sin(now * shenronFloatSpeed) * shenronFloatRange;

		//Para animación del planeta (rotación)
		planetaRotation += planetaRotationSpeed * deltaTimeDos;
		if (planetaRotation > 360.0f) {
			planetaRotation -= 360.0f;
		}

		//Recibir eventos del usuario
		glfwPollEvents();

		// Para alternar entre cámaras con la tecla C
		//Alterna entre la cámara 1(tercera persona) con la cámara 2(vista ortogonal o superior)
		if (mainWindow.getsKeys()[GLFW_KEY_C]) {
			if (!teclaC_presionada) {
				tipoCamara = (tipoCamara + 1) % 3;
				teclaC_presionada = true;
			}
		}
		else {
			teclaC_presionada = false;
		} 

		camera.keyControl(mainWindow.getsKeys(), deltaTimeDos);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();
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


		// Movimiento con teclado para personaje de Leon RE

		// Movimiento hacia adelante y atrás, S y W
		if (mainWindow.getsKeys()[GLFW_KEY_S]) {
			gPersonajePos += direccionFrontal * gVelocidadMovimiento * deltaTime;
		}
		if (mainWindow.getsKeys()[GLFW_KEY_W]) {
			gPersonajePos -= direccionFrontal * gVelocidadMovimiento * deltaTime;
		}
		if (mainWindow.getsKeys()[GLFW_KEY_A]) {
			// Girar hacia la izquierda 
			gPersonajeRotY -= gVelocidadRotacion * deltaTime;  // Rotar en sentido antihorario
		}
		if (mainWindow.getsKeys()[GLFW_KEY_D]) {
			// Girar hacia la derecha 
			gPersonajeRotY += gVelocidadRotacion * deltaTime;  // Rotar en sentido horario
		}

		// Rotación con el mouse
		float offsetX = mainWindow.getXChange();
		gPersonajeRotY += offsetX * 0.1f;  // Ajustar la rotación del personaje en Y con el mouse

		// Calcular la posición de la cámara en tercera persona
		//Se pueden modificar los valores para adaptar la cámara en 3ra persona, vista aerea y vista ortogonal
		float distanciaCamara = 2.0f;
		float alturaCamara = 1.0f;
		float angleRad = glm::radians(gPersonajeRotY);
		glm::vec3 offset(-sin(angleRad) * distanciaCamara, alturaCamara, -cos(angleRad) * distanciaCamara);

		glm::mat4 view;
		glm::mat4 orthoProjection;  //Cámara aerea

		if (tipoCamara == 0) {  // Cámara en tercera persona
			camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
			view = camera.calculateViewMatrix();
		}
		else if (tipoCamara == 1) {  // Cámara en 3ra persona personaje Leon
			float angleRad = glm::radians(gPersonajeRotY);
			glm::vec3 offset(-sin(angleRad) * 2.0f, 1.0f, -cos(angleRad) * 2.0f);
			glm::vec3 camPos = gPersonajePos + offset;
			glm::vec3 target = gPersonajePos + glm::vec3(0.0f, 1.0f, 0.0f);
			view = glm::lookAt(camPos, target, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (tipoCamara == 2) {  // Cámara ortogonal, se modifica la posición en y dependiendo la altura
			orthoProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f); 
			glm::vec3 camPos(0.0f, 200.0f, 0.0f);  // Cámara mirando desde Y = 100
			glm::vec3 target(0.0f, 0.0f, 0.0f);   
			glm::vec3 up(0.0f, 0.0f, -1.0f);      
			view = glm::lookAt(camPos, target, up);  
			// Usamos la proyección ortogonal
			glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(orthoProjection));
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		}

		//No borrar este código comentado(Héctor 02/05/2025)

		/*float angleRad = glm::radians(gPersonajeRotY);
		glm::vec3 offset(-sin(angleRad) * 2.0f, 1.0f, -cos(angleRad) * 2.0f);
		glm::vec3 camPos = gPersonajePos + offset;
		glm::vec3 target = gPersonajePos + glm::vec3(0.0f, 1.0f, 0.0f);
		view = glm::lookAt(camPos, target, glm::vec3(0.0f, 1.0f, 0.0f));*/

		/*camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		view = camera.calculateViewMatrix();*/

		// Enviar la matriz de vista al shader
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(view, projection);

		// Movimiento simple del zombie adelante y atrás

		if (avanza) {
			if (movDragon > -8.0f) {
				movDragon -= movOffset * deltaTime;
				dragongiro = 0;
			}
			else {
				avanza = !avanza;
			}
		}
		else {
			if (movDragon < 0.0f) {
				movDragon += movOffset * deltaTime;
				dragongiro = 180;
			}
			else {
				avanza = !avanza;
			}
		}

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

		// Para movimiento de las extremidades de Leon, 
		// Avanzar animación solo si se presiona W o S
		//NOTA: Los botones W y S se están declarando igualmente arriba, sin embargo se están colocando aquí para diferenciar el movimiento de extremidades.
		if (mainWindow.getsKeys()[GLFW_KEY_W] || mainWindow.getsKeys()[GLFW_KEY_S]) {
			animacionTiempo += deltaTime * velocidadAnimacion;
		}
		else {
			animacionTiempo = 0.0f; // Detener el movimiento si no se esta caminando
		}
		// Cálculo de ángulos tipo caminata RE2
		float anguloPiernas = sin(animacionTiempo) * amplitudMovimiento;
		float anguloBrazos = -anguloPiernas;
		
		//<--------------------------------INICIO LLAMADA DE MODELOS-------------------------------->

		model = glm::mat4(1.0);
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mapa.RenderModel();

		//*********************************PARA UNIVERSO DE RESIDENT EVIL*********************************

		//Cuerpo de Leon Kennedy
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, gPersonajePos);
		model = glm::rotate(model, glm::radians(gPersonajeRotY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.19f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuerpo_Leon.RenderModel();

		//Brazo izquierdo Leon
		model = modelaux;
		model = glm::rotate(model, glm::radians(anguloBrazos), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Brazo_izquierdo_Leon.RenderModel();

		//Brazo derecho Leon
		model = modelaux;
		float anguloExtraPickup = 0.0f;

		if (animandoManoPickup) {
			anguloExtraPickup = sin(tiempoAnimacionMano * 10.0f) * 20.0f;
		}

		model = glm::rotate(model, glm::radians(-anguloBrazos + anguloExtraPickup), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Brazo_derecho_Leon.RenderModel();

		//Pie derecho Leon
		model = modelaux;
		model = glm::rotate(model, glm::radians(-anguloPiernas), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pie_derecho_Leon.RenderModel();

		//Pie izquierdo Leon
		model = modelaux;
		model = glm::rotate(model, glm::radians(anguloPiernas), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pie_izquierdo_Leon.RenderModel();


		model = glm::mat4(1.0);
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mansion.RenderModel();

		model = glm::mat4(1.0);
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TiroHacha.RenderModel();

		model = glm::mat4(1.0);
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Torre.RenderModel();

		model = glm::mat4(1.0);
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tren.RenderModel();

		model = glm::mat4(1.0);
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Baño.RenderModel();

		model = glm::mat4(1.0);
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Torre_Helicoptero.RenderModel();

		model = glm::mat4(1.0);
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Torre_Helicoptero_Dos.RenderModel();

		model = glm::mat4(1.0);
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Torre_Helicoptero_Tres.RenderModel();

		model = glm::mat4(1.0);
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carro_Abandonado.RenderModel();

		model = glm::mat4(1.0);
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cartel_Circo.RenderModel();

		// <---------- INICIO: Código para jerarquía de rueda fortuna y su giro ------------->

		// Parte 3: Base fija
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.541f, 15.716f, 46.624f)); // deshacer la traslación del pivote
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RuedaFortuna_parteTres.RenderModel();

		// Parte 1: estructura metálica girando
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.541f, 15.716f, 46.624f)); // deshacer la traslación del pivote
		model = glm::rotate(model, glm::radians(anguloRueda), glm::vec3(0.0f, 0.0f, 1.0f)); // eje Z típico de ruedas
		modelaux = model; // guardamos para ParteDos
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RuedaFortuna_parteUno.RenderModel();

		// Parte 2: canastas giran con la rueda
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RuedaFortuna_parteDos.RenderModel();


		// <---------- FIN: Código para jerarquía de rueda fortuna y su giro ------------->

		// <---------- INICIO: Código para movimiento de los zombies ------------->

		// Animación continua de piernas de zombie
		animacionTiempoZombie += deltaTime * velocidadAnimacionZombie;

		// Cálculo de movimiento tipo "caminar"
		float anguloPiernasZombie = sin(animacionTiempoZombie) * amplitudMovimientoZombie;

		// ZombieUno - Cuerpo principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(28.062f, 2.393f, 14.145f + movDragon)); // Movimiento en Z
		model = glm::rotate(model, dragongiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model; // Guardamos el cuerpo base
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cuerpo.RenderModel();

		// Pierna izquierda (relativa al cuerpo)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.189f, -0.405f, -0.007f)); // Offset desde el cuerpo
		model = glm::rotate(model, glm::radians(anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Animación caminar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaIzquierda.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.103f, -0.448f, -0.022f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento contrario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaDerecha.RenderModel();

		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.375f, 0.772f, 0.458f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoDerecho.RenderModel();

		// Brazo izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.415f, 0.855f, 0.513f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoIzquierdo.RenderModel();

		// Cabeza (movimiento de lado a lado)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.032f, 1.241f, 0.03f));
		model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Cabeceo suave
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cabeza.RenderModel();



		// ZombieDos - Cuerpo principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(11.831f, 2.393f, 26.731f + movDragon)); // Movimiento en Z
		model = glm::rotate(model, dragongiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model; // Guardamos el cuerpo base
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cuerpo.RenderModel();

		// Pierna izquierda (relativa al cuerpo)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.189f, -0.405f, -0.007f)); // Offset desde el cuerpo
		model = glm::rotate(model, glm::radians(anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Animación caminar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaIzquierda.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.103f, -0.448f, -0.022f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento contrario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaDerecha.RenderModel();

		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.375f, 0.772f, 0.458f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoDerecho.RenderModel();

		// Brazo izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.415f, 0.855f, 0.513f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoIzquierdo.RenderModel();

		// Cabeza (movimiento de lado a lado)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.032f, 1.241f, 0.03f));
		model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Cabeceo suave
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cabeza.RenderModel();



		// ZombieTres - Cuerpo principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(11.58f, 2.393f, 48.224f + movDragon)); // Movimiento en Z
		model = glm::rotate(model, dragongiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model; // Guardamos el cuerpo base
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cuerpo.RenderModel();

		// Pierna izquierda (relativa al cuerpo)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.189f, -0.405f, -0.007f)); // Offset desde el cuerpo
		model = glm::rotate(model, glm::radians(anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Animación caminar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaIzquierda.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.103f, -0.448f, -0.022f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento contrario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaDerecha.RenderModel();

		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.375f, 0.772f, 0.458f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoDerecho.RenderModel();

		// Brazo izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.415f, 0.855f, 0.513f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoIzquierdo.RenderModel();

		// Cabeza (movimiento de lado a lado)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.032f, 1.241f, 0.03f));
		model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Cabeceo suave
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cabeza.RenderModel();


		// ZombieCuatro - Cuerpo principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(35.113f, 2.393f, 32.783f + movDragon)); // Movimiento en Z
		model = glm::rotate(model, dragongiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model; // Guardamos el cuerpo base
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cuerpo.RenderModel();

		// Pierna izquierda (relativa al cuerpo)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.189f, -0.405f, -0.007f)); // Offset desde el cuerpo
		model = glm::rotate(model, glm::radians(anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Animación caminar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaIzquierda.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.103f, -0.448f, -0.022f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento contrario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaDerecha.RenderModel();

		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.375f, 0.772f, 0.458f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoDerecho.RenderModel();

		// Brazo izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.415f, 0.855f, 0.513f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoIzquierdo.RenderModel();

		// Cabeza (movimiento de lado a lado)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.032f, 1.241f, 0.03f));
		model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Cabeceo suave
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cabeza.RenderModel();




		// ZombieCinco - Cuerpo principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(39.989f, 2.393f, 52.871f + movDragon)); // Movimiento en Z
		model = glm::rotate(model, dragongiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model; // Guardamos el cuerpo base
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cuerpo.RenderModel();

		// Pierna izquierda (relativa al cuerpo)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.189f, -0.405f, -0.007f)); // Offset desde el cuerpo
		model = glm::rotate(model, glm::radians(anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Animación caminar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaIzquierda.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.103f, -0.448f, -0.022f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento contrario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaDerecha.RenderModel();

		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.375f, 0.772f, 0.458f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoDerecho.RenderModel();

		// Brazo izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.415f, 0.855f, 0.513f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoIzquierdo.RenderModel();

		// Cabeza (movimiento de lado a lado)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.032f, 1.241f, 0.03f));
		model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Cabeceo suave
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cabeza.RenderModel();



		// ZombieSiete - Cuerpo principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(17.412f + movDragon, 2.393f, 34.346f)); // Movimiento en Z
		model = glm::rotate(model, dragongiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model; // Guardamos el cuerpo base
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cuerpo.RenderModel();

		// Pierna izquierda (relativa al cuerpo)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.189f, -0.405f, -0.007f)); // Offset desde el cuerpo
		model = glm::rotate(model, glm::radians(anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Animación caminar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaIzquierda.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.103f, -0.448f, -0.022f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento contrario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaDerecha.RenderModel();

		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.375f, 0.772f, 0.458f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoDerecho.RenderModel();

		// Brazo izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.415f, 0.855f, 0.513f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoIzquierdo.RenderModel();

		// Cabeza (movimiento de lado a lado)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.032f, 1.241f, 0.03f));
		model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Cabeceo suave
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cabeza.RenderModel();


		// ZombieSeis - Cuerpo principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(28.62f + movDragon, 2.393f, 64.873f)); // Movimiento en Z
		model = glm::rotate(model, dragongiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model; // Guardamos el cuerpo base
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cuerpo.RenderModel();

		// Pierna izquierda (relativa al cuerpo)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.189f, -0.405f, -0.007f)); // Offset desde el cuerpo
		model = glm::rotate(model, glm::radians(anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Animación caminar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaIzquierda.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.103f, -0.448f, -0.022f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento contrario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaDerecha.RenderModel();

		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.375f, 0.772f, 0.458f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoDerecho.RenderModel();

		// Brazo izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.415f, 0.855f, 0.513f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoIzquierdo.RenderModel();

		// Cabeza (movimiento de lado a lado)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.032f, 1.241f, 0.03f));
		model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Cabeceo suave
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cabeza.RenderModel();


		// ZombieOcho - Cuerpo principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(56.247f + movDragon, 2.393f, 61.298f)); // Movimiento en Z
		model = glm::rotate(model, dragongiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model; // Guardamos el cuerpo base
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cuerpo.RenderModel();

		// Pierna izquierda (relativa al cuerpo)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.189f, -0.405f, -0.007f)); // Offset desde el cuerpo
		model = glm::rotate(model, glm::radians(anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Animación caminar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaIzquierda.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.103f, -0.448f, -0.022f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento contrario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaDerecha.RenderModel();

		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.375f, 0.772f, 0.458f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoDerecho.RenderModel();

		// Brazo izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.415f, 0.855f, 0.513f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoIzquierdo.RenderModel();

		// Cabeza (movimiento de lado a lado)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.032f, 1.241f, 0.03f));
		model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Cabeceo suave
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cabeza.RenderModel();


		// ZombieNueve - Cuerpo principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(35.104f + movDragon, 2.393f, 32.79f)); // Movimiento en Z
		model = glm::rotate(model, dragongiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model; // Guardamos el cuerpo base
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cuerpo.RenderModel();

		// Pierna izquierda (relativa al cuerpo)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.189f, -0.405f, -0.007f)); // Offset desde el cuerpo
		model = glm::rotate(model, glm::radians(anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Animación caminar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaIzquierda.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.103f, -0.448f, -0.022f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento contrario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaDerecha.RenderModel();

		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.375f, 0.772f, 0.458f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoDerecho.RenderModel();

		// Brazo izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.415f, 0.855f, 0.513f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoIzquierdo.RenderModel();

		// Cabeza (movimiento de lado a lado)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.032f, 1.241f, 0.03f));
		model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Cabeceo suave
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cabeza.RenderModel();


		// ZombieDiez - Cuerpo principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(28.769f + movDragon, 2.393f, 30.81f)); // Movimiento en Z
		model = glm::rotate(model, dragongiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model; // Guardamos el cuerpo base
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cuerpo.RenderModel();

		// Pierna izquierda (relativa al cuerpo)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.189f, -0.405f, -0.007f)); // Offset desde el cuerpo
		model = glm::rotate(model, glm::radians(anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Animación caminar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaIzquierda.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.103f, -0.448f, -0.022f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento contrario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaDerecha.RenderModel();

		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.375f, 0.772f, 0.458f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoDerecho.RenderModel();

		// Brazo izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.415f, 0.855f, 0.513f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoIzquierdo.RenderModel();

		// Cabeza (movimiento de lado a lado)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.032f, 1.241f, 0.03f));
		model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Cabeceo suave
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cabeza.RenderModel();


		// ZombieOnce - Cuerpo principal
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(20.903f + movDragon, 2.393f, 1.197f)); // Movimiento en Z
		model = glm::rotate(model, dragongiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model; // Guardamos el cuerpo base
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cuerpo.RenderModel();

		// Pierna izquierda (relativa al cuerpo)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.189f, -0.405f, -0.007f)); // Offset desde el cuerpo
		model = glm::rotate(model, glm::radians(anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Animación caminar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaIzquierda.RenderModel();

		// Pierna derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.103f, -0.448f, -0.022f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento contrario
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_PiernaDerecha.RenderModel();

		// Brazo derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.375f, 0.772f, 0.458f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoDerecho.RenderModel();

		// Brazo izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.415f, 0.855f, 0.513f));
		model = glm::rotate(model, glm::radians(-anguloPiernasZombie), glm::vec3(1.0f, 0.0f, 0.0f)); // Movimiento
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_BrazoIzquierdo.RenderModel();

		// Cabeza (movimiento de lado a lado)
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.032f, 1.241f, 0.03f));
		model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Cabeceo suave
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zombie_Dos_Cabeza.RenderModel();


		// <---------- FIN: Código para animar al Zombie ------------->


		//Para tanque

		/*Model Tanque_Fusil;
		Model Tanque_Capote;
		Model Tanque_Cuerpo;
		Model Tanque_LlantasDerechas;
		Model Tanque_LlantasIzquierdas;*/


		// Posiciona y rota el tanque completo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(18.347f, 3.148f, 55.705f)); // Posición global del tanque
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;

		// ----- Cuerpo del tanque -----
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tanque_Cuerpo.RenderModel();

		// ----- Llantas DERECHAS -----
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.345f, -1.056f, -0.541f)); // Offset desde el cuerpo
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tanque_LlantasDerechas.RenderModel();

		// ----- Llantas IZQUIERDAS -----
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.211f, -1.056f, 0.965f)); // Offset relativo ya corregido
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tanque_LlantasIzquierdas.RenderModel();

		// ----- Capote -----
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.178f, 2.082f, -0.712f)); // Offset arriba del cuerpo
		model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tanque_Capote.RenderModel();



		float altura = sin(tiempoMedicina) * amplitudFlotacion;

		for (size_t i = 0; i < posicionesMedicinas.size(); ++i) {
			if (!medicinasTomadas[i]) {
				glm::vec3 pos = posicionesMedicinas[i];
				float distancia = glm::distance(gPersonajePos, pos);

				if (distancia < 3.0f && mainWindow.getsKeys()[GLFW_KEY_E]) {
					medicinasTomadas[i] = true;
					animandoManoPickup = true;
					tiempoAnimacionMano = 0.0f;
				}
				else {
					//Esto solo sirve para dibujar en caso de que no este dibujada 
					model = glm::mat4(1.0f);
					model = glm::translate(model, pos + glm::vec3(0.0f, altura, 0.0f));
					model = glm::rotate(model, tiempoMedicina, glm::vec3(0.0f, 1.0f, 0.0f));
					glUniform3fv(uniformColor, 1, glm::value_ptr(color));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
					Medicina.RenderModel();
				}
			}
		}


		//*********************************PARA UNIVERSO DE DRAGON BALL*********************************

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