/*
PROYECTO FERIA
*/

//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <cmath>
#include <cstdlib>

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
#include "animaciones_ferb.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//<--------------------------------DECLARACIÓN DE VARIABLES-------------------------------->

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;

//*********************************MODELOS SUPERMAN*********************************
Model Mapa;
Model Fortress, BrainiacShip, SupermanStatue, Hall, Bench, BigBench, Fountain, BigLogo, Carts, Kryptonite;
//********************************MODELOS PHINEAS Y FERB***********************************
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
Model Doof_bicep_M;
Model Doof_brazo_M;
Model Doof_muneca_M;
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
Model Mazo_M;
Model carpa_globo_M;
Model globo_M;
Model dardo_M;
Model linea_roja_M;
Model globo_ponchado_M;

//*********************************PARA UNIVERSO DE DRAGON BALL*********************************
Model shenron;
Model goku;
Model tickets;
Model thomas;
Model planeta;
Model casa_capsula;
Model casa_goku;
Model tasa;
Model cuerpo_juego;
Model topo;
Model martillo;
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

Skybox skyboxDay;
Skybox skyboxNight;

//materiales
Material Material_brillante;
Material Material_opaco;

//*********************************VARIABLES SUPERMAN*********************************
float brainiacHoverOffset = 0.0f;
float brainiacHoverSpeed = 0.07f;
float brainiacRotationAngle = 0.0f;
float brainiacRotationSpeed = 0.02f;
float kryptoniteRotationAngle = 0.0f;
float kryptoniteRotationSpeed = 0.5f;
float logoRotationAngle = 0.0f;
float logoRotationSpeed = 1.0f;

//*********************************VARIABLES DRAGON BALL*********************************
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

// Límites para el movimiento del androide
const float androideLenNegZ = 10.0f;
const float androideLenPosX = 10.0f;
const float androideLenPosZ = 10.0f;
const float androideLenNegX = 10.0f;

const float androideLimNegZ = startAndroideZ - androideLenNegZ;
const float androideLimPosX = startAndroideX + androideLenPosX;
const float androideLimPosZ = startAndroideZ + androideLenPosZ;
const float androideLimNegX = startAndroideX - androideLenNegX;

//Variables del movimiento del topo

int topoActual = rand() % 8;
float topoY = 0.0f;
float tiempoTopo = 0.0f;
bool subiendo2 = true;
float esperaActual2 = 0.0f;
bool esperando2 = false;



const float velocidadTopo = 0.01f;      // Mucho más lento
const float alturaMax = 0.4f;
const float tiempoEspera = 4.0f;       // Espera antes de cambiar de posición
const float tiempoArriba = 2.5f;        // Tiempo que se queda arriba


glm::vec3 posicionesTopo[6] = {
{-30.0f, -0.5f, -41.75f},
{-30.0f, -0.5f, -41.45f},
{-30.0f, -0.5f, -41.05f},
{-30.5f,-0.5f, -41.75f},
{-30.5f, -0.5f, -41.45f},
{-30.5f, -0.5f, -41.05f}
};

//variables para el movimiento del martillo
float martilloRotation = -30.0f; // Ángulo inicial (como listo para golpear)
float martilloAnimTime = 0.0f;
const float martilloAnimSpeed = 0.1f; // Velocidad de la animación
const float martilloGolpeAngle = 60.0f; // Máximo ángulo de golpeo
const float martilloHeight = 4.5f; // Altura sobre el topo

//*********************************VARIABLES RESIDENT EVIL*********************************
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

std::vector<glm::vec3> posicionesMedicinas = {
    glm::vec3(19.214f, 2.209f, 14.423f),
    glm::vec3(25.73f, 2.209f, 21.245f),
    glm::vec3(30.0f, 2.209f, 10.0f),
    glm::vec3(40.0f, 2.209f, 15.0f)
};

std::vector<bool> medicinasTomadas(posicionesMedicinas.size(), false);

int tipoCamara = 0;
bool teclaC_presionada = false;
glm::vec3 camaraAereaPos(0.0f, 100.0f, 0.0f);
glm::vec3 camaraAereaTarget(0.0f, 0.0f, 0.0f);
glm::vec3 camaraAereaUp(0.0f, 0.0f, -1.0f);

//*********************************VARIABLES DIA/NOCHE*********************************
float dayNightCycle = 0.0f; // Ángulo que representará la posición del sol/luna (0-360)
float cycleSpeed = 0.2f;   // Velocidad del ciclo
bool isDaytime = true;     // Para controlar si es día o noche
Sphere sunSphere = Sphere(2.0f, 20, 20);  // Radio y divisiones
Sphere moonSphere = Sphere(1.5f, 20, 20);

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

//función de calculo de normales por promedio de vértices 
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

    CreateShaders();

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

    brickTexture = Texture("Textures/brick.png");
    brickTexture.LoadTextureA();
    dirtTexture = Texture("Textures/dirt.png");
    dirtTexture.LoadTextureA();
    plainTexture = Texture("Textures/plain.png");
    plainTexture.LoadTextureA();
    pisoTexture = Texture("Textures/piso.tga");
    pisoTexture.LoadTextureA();

    // Cargar modelos del universo Superman
    Mapa = Model();
    Mapa.LoadModel("Models/mapa_preeliminar_cinco.obj");
    Fortress = Model();
    Fortress.LoadModel("Models/FortressSolitude.obj");
    BrainiacShip = Model();
    BrainiacShip.LoadModel("Models/BrainiacShipF.obj");
    SupermanStatue = Model();
    SupermanStatue.LoadModel("Models/Statue.obj");
    Hall = Model();
    Hall.LoadModel("Models/HallofJustice.obj");
    Bench = Model();
    Bench.LoadModel("Models/SupermanBenchF.obj");
    Kryptonite = Model();
    Kryptonite.LoadModel("Models/Kriptonite.obj");
    Carts = Model();
    Carts.LoadModel("Models/CarroComida.obj");
    BigLogo = Model();
    BigLogo.LoadModel("Models/SupermanLogo.obj");
    


    // Cargar modelos del universo Dragon Ball
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
    casa_goku = Model();
    casa_goku.LoadModel("Models/casa_goku.obj");
    tasa = Model();
    tasa.LoadModel("Models/tasa.obj");
    cuerpo_juego = Model();
    cuerpo_juego.LoadModel("Models/cuerpo_maquina.obj");
    topo = Model();
    topo.LoadModel("Models/topo.obj");
    martillo = Model();
    martillo.LoadModel("Models/martillo.obj");

    // Cargar modelos del universo Resident Evil
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
    RuedaFortuna_parteUno = Model();
    RuedaFortuna_parteUno.LoadModel("Models/rueda_fortuna_parte_una.obj");
    RuedaFortuna_parteDos = Model();
    RuedaFortuna_parteDos.LoadModel("Models/rueda_fortuna_parte_dos.obj");
    RuedaFortuna_parteTres = Model();
    RuedaFortuna_parteTres.LoadModel("Models/rueda_fortuna_parte_tres.obj");
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
    Medicina = Model();
    Medicina.LoadModel("Models/lata.obj");


    // ----------------------------------------------------------------------------------------------------------------------------------
    // ----------------------------------------- UNIVERSO PHINEAS & FERB - MODELOS ------------------------------------------------------
    // ----------------------------------------------------------------------------------------------------------------------------------

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
    Doof_bicep_M = Model();
    Doof_bicep_M.LoadModel("Models/doof_bicep.obj");
    Doof_brazo_M = Model();
    Doof_brazo_M.LoadModel("Models/doof_brazo.obj");
    Doof_muneca_M = Model();
    Doof_muneca_M.LoadModel("Models/doof_muneca.obj");
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
    Mazo_M = Model();
    Mazo_M.LoadModel("Models/mallet.obj");
    carpa_globo_M = Model();
    carpa_globo_M.LoadModel("Models/carpa_globos.obj");
    globo_M = Model();
    globo_M.LoadModel("Models/globo.obj");
    dardo_M = Model();
    dardo_M.LoadModel("MOdels/dardo.obj");
    linea_roja_M = Model();
    linea_roja_M.LoadModel("Models/linea_roja.obj");
    globo_ponchado_M = Model();
    globo_ponchado_M.LoadModel("Models/globo_ponchado.obj");

    // Configuración de skybox día/noche
    std::vector<std::string> skyboxFacesDay;
    skyboxFacesDay.push_back("Textures/Skybox/sb_day_rt.tga");
    skyboxFacesDay.push_back("Textures/Skybox/sb_day_lf.tga");
    skyboxFacesDay.push_back("Textures/Skybox/sb_day_dn.tga");
    skyboxFacesDay.push_back("Textures/Skybox/sb_day_up.tga");
    skyboxFacesDay.push_back("Textures/Skybox/sb_day_ft.tga");
    skyboxFacesDay.push_back("Textures/Skybox/sb_day_bk.tga");

    std::vector<std::string> skyboxFacesNight;
    skyboxFacesNight.push_back("Textures/Skybox/sb_night_rt.tga");
    skyboxFacesNight.push_back("Textures/Skybox/sb_night_lf.tga");
    skyboxFacesNight.push_back("Textures/Skybox/sb_night_dn.tga");
    skyboxFacesNight.push_back("Textures/Skybox/sb_night_up.tga");
    skyboxFacesNight.push_back("Textures/Skybox/sb_night_ft.tga");
    skyboxFacesNight.push_back("Textures/Skybox/sb_night_bk.tga");

    // Creamos ambos skyboxes
    skyboxDay = Skybox(skyboxFacesDay);
    skyboxNight = Skybox(skyboxFacesNight);

    Material_brillante = Material(2.0f, 256);
    Material_opaco = Material(0.3f, 4);

    // Configuración de luces (desde archivo 1)
    mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
        0.3f, 0.3f,
        0.0f, 0.0f, -1.0f);

    unsigned int pointLightCount = 1;

    // Configuración de luces spotlight
    unsigned int spotLightCount = 0;

    // Luz spotlight 1 - (52, 10, -53)
    spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,    // Color blanco
        0.0f, 2.0f,                               // Intensidad ambiental y difusa
        52.0f, 10.0f, -53.0f,                     // Posición
        0.0f, -1.0f, 0.0f,                        // Dirección (hacia abajo)
        1.0f, 0.0f, 0.0f,                         // Atenuación
        60.0f);                                   // Ángulo de apertura
    spotLightCount++;

    // Luz spotlight 2 - (50, 10, 56)
    spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,    // Color blanco
        0.0f, 2.0f,                               // Intensidad ambiental y difusa
        50.0f, 10.0f, 56.0f,                      // Posición
        0.0f, -1.0f, 0.0f,                        // Dirección (hacia abajo)
        1.0f, 0.0f, 0.0f,                         // Atenuación
        60.0f);                                   // Ángulo de apertura
    spotLightCount++;

    // Luz spotlight 3 - (-39, 10, 56)
    spotLights[2] = SpotLight(1.0f, 1.0f, 1.0f,    // Color blanco
        0.0f, 2.0f,                               // Intensidad ambiental y difusa
        -39.0f, 10.0f, 56.0f,                     // Posición
        0.0f, -1.0f, 0.0f,                        // Dirección (hacia abajo)
        1.0f, 0.0f, 0.0f,                         // Atenuación
        60.0f);                                   // Ángulo de apertura
    spotLightCount++;

    // Luz spotlight 4 - (-39, 10, -54)
    spotLights[3] = SpotLight(1.0f, 1.0f, 1.0f,    // Color blanco
        0.0f, 2.0f,                               // Intensidad ambiental y difusa
        -39.0f, 10.0f, -54.0f,                    // Posición
        0.0f, -1.0f, 0.0f,                        // Dirección (hacia abajo)
        1.0f, 0.0f, 0.0f,                         // Atenuación
        60.0f);                                   // Ángulo de apertura
    spotLightCount++;

    // Inicializar variables de animación
    movCoche = 0.0f;
    movOffset = 0.3f;
    rotllanta = 0.0f;
    rotllantaOffset = 10.0f;
    avanza = true;

    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
        uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
    GLuint uniformColor = 0;
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

    // Loop mientras no se cierra la ventana
    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTimeDos = now - lastTime;
        deltaTime = now - lastTime;
        deltaTime += (now - lastTime) / limitFPS;
        lastTime = now;

        // Actualización de animaciones para personajes y objetos
        // Zombie
        animacionTiempoZombie += deltaTimeDos * velocidadAnimacionZombie;

        // Medicina
        tiempoMedicina += deltaTimeDos * velocidadFlotacion;

        if (animandoManoPickup) {
            tiempoAnimacionMano += deltaTimeDos;
            if (tiempoAnimacionMano >= 0.5f) {
                animandoManoPickup = false;
                tiempoAnimacionMano = 0.0f;
            }
        }

        // Rueda de la fortuna
        static float anguloRueda = 0.0f;
        anguloRueda += 20.0f * deltaTimeDos;
        if (anguloRueda > 360.0f) anguloRueda -= 360.0f;

        // Brainiac Ship
        brainiacHoverOffset += brainiacHoverSpeed * deltaTime;
        if (brainiacHoverOffset > 2.0f * glm::pi<float>())
            brainiacHoverOffset = 0.0f;
        float verticalOffset = sin(brainiacHoverOffset) * 2.0f;

        brainiacRotationAngle += brainiacRotationSpeed * deltaTime;
        if (brainiacRotationAngle > 2.0f * glm::pi<float>())
            brainiacRotationAngle = 0.0f;
        float rotationAmount = sin(brainiacRotationAngle) * 5.0f;

        // Kryptonite
        kryptoniteRotationAngle += kryptoniteRotationSpeed * deltaTime;
        if (kryptoniteRotationAngle > 360.0f)
            kryptoniteRotationAngle -= 360.0f;

        // Logo
        logoRotationAngle += logoRotationSpeed * deltaTime;
        if (logoRotationAngle > 360.0f)
            logoRotationAngle -= 360.0f;

        // Shenron
        shenronYOffset = sin(now * shenronFloatSpeed) * shenronFloatRange;

        // Planeta
        planetaRotation += planetaRotationSpeed * deltaTime;
        if (planetaRotation > 360.0f) {
            planetaRotation -= 360.0f;
        }

        //EMPIEZA ANIMACIÓN TOPO
        if (esperando2) {
            esperaActual2 += deltaTime;
            if (esperaActual2 >= tiempoEspera) {
                esperando2 = false;
                esperaActual2 = 0.0f;
                topoActual = rand() % 6;  // Cambia de hoyo
            }
        }
        else {
            if (subiendo2) {
                topoY += velocidadTopo * deltaTime;
                if (topoY >= alturaMax) {
                    topoY = alturaMax;
                    subiendo2 = false;
                    esperaActual = 0.0f;
                }
            }
            else {
                esperaActual2 += deltaTime;
                if (esperaActual2 >= tiempoArriba) {
                    topoY -= velocidadTopo * deltaTime;
                    if (topoY <= 0.0f) {
                        topoY = 0.0f;
                        subiendo2 = true;
                        esperando2 = true;
                        esperaActual2 = 0.0f;
                    }
                }
            }
        }
        //TRMINA MOVIMIENTO DEL TOPO
        martilloAnimTime += deltaTime * martilloAnimSpeed;

        // Calcular rotación oscilante para efecto de golpeo continuo
        martilloRotation = -30.0f + (sin(martilloAnimTime) * 0.5f + 0.5f) * martilloGolpeAngle;

        // Tren
        float trainSpeed = 0.5f;
        switch (currentDirection) {
        case TO_NEGATIVE_Z:
            movZTrain -= trainSpeed * deltaTime;
            if (movZTrain <= limNegZ) {
                movZTrain = limNegZ;
                currentDirection = TO_POSITIVE_X;
                trainRotation = -90.0f;
            }
            break;
        case TO_POSITIVE_X:
            movXTrain += trainSpeed * deltaTime;
            if (movXTrain >= limPosX) {
                movXTrain = limPosX;
                currentDirection = TO_POSITIVE_Z;
                trainRotation = 180.0f;
            }
            break;
        case TO_POSITIVE_Z:
            movZTrain += trainSpeed * deltaTime;
            if (movZTrain >= limPosZ) {
                movZTrain = limPosZ;
                currentDirection = TO_NEGATIVE_X;
                trainRotation = 90.0f;
            }
            break;
        case TO_NEGATIVE_X:
            movXTrain -= trainSpeed * deltaTime;
            if (movXTrain <= limNegX) {
                movXTrain = limNegX;
                currentDirection = TO_NEGATIVE_Z;
                trainRotation = 0.0f;
            }
            break;
        }

        // Androide
        float androideSpeed = 0.05f;
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

        // Dirección hacia la que Leon está mirando
        glm::vec3 direccionFrontal;
        direccionFrontal.x = -sin(glm::radians(gPersonajeRotY));
        direccionFrontal.y = 0.0f;
        direccionFrontal.z = -cos(glm::radians(gPersonajeRotY));
        direccionFrontal = glm::normalize(direccionFrontal);

        // Movimiento de zombies
        if (avanza) {
            if (movDragon > -8.0f) {
                movDragon -= movOffset * deltaTimeDos;
                dragongiro = 0;
            }
            else {
                avanza = !avanza;
            }
        }
        else {
            if (movDragon < 0.0f) {
                movDragon += movOffset * deltaTimeDos;
                dragongiro = 180;
            }
            else {
                avanza = !avanza;
            }
        }

        // Recibir eventos del usuario
        glfwPollEvents();

        // Para alternar entre cámaras con la tecla C
        if (mainWindow.getsKeys()[GLFW_KEY_C]) {
            if (!teclaC_presionada) {
                tipoCamara = (tipoCamara + 1) % 3;
                teclaC_presionada = true;
            }
        }
        else {
            teclaC_presionada = false;
        }

        // Movimiento con teclado para personaje de Leon RE
        if (mainWindow.getsKeys()[GLFW_KEY_S]) {
            gPersonajePos += direccionFrontal * gVelocidadMovimiento * deltaTimeDos;
        }
        if (mainWindow.getsKeys()[GLFW_KEY_W]) {
            gPersonajePos -= direccionFrontal * gVelocidadMovimiento * deltaTimeDos;
        }
        if (mainWindow.getsKeys()[GLFW_KEY_A]) {
            gPersonajeRotY -= gVelocidadRotacion * deltaTimeDos;
        }
        if (mainWindow.getsKeys()[GLFW_KEY_D]) {
            gPersonajeRotY += gVelocidadRotacion * deltaTimeDos;
        }

        // Avanzar animación solo si se presiona W o S
        if (mainWindow.getsKeys()[GLFW_KEY_W] || mainWindow.getsKeys()[GLFW_KEY_S]) {
            animacionTiempo += deltaTimeDos * velocidadAnimacion;
        }
        else {
            animacionTiempo = 0.0f;
        }

        // Cálculo de ángulos tipo caminata
        float anguloPiernas = sin(animacionTiempo) * amplitudMovimiento;
        float anguloBrazos = -anguloPiernas;

        camera.keyControl(mainWindow.getsKeys(), deltaTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

        // Configuración de cámara según tipo seleccionado
        glm::mat4 view;
        glm::mat4 orthoProjection;

        if (tipoCamara == 0) {  // Cámara normal
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
        else if (tipoCamara == 2) {  // Cámara ortogonal
            orthoProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
            glm::vec3 camPos(0.0f, 200.0f, 0.0f);
            glm::vec3 target(0.0f, 0.0f, 0.0f);
            glm::vec3 up(0.0f, 0.0f, -1.0f);
            view = glm::lookAt(camPos, target, up);
        }

        // Rotación con el mouse para personaje
        float offsetX = mainWindow.getXChange();
        gPersonajeRotY += offsetX * 0.1f;

        // Clear the window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Sistema día-noche
        dayNightCycle += cycleSpeed * deltaTime;
        if (dayNightCycle > 360.0f)
            dayNightCycle = 0.0f;

        // Calcula la posición del sol/luna en una trayectoria circular
        float orbitRadius = 50.0f;
        float sunPosY = sin(dayNightCycle * toRadians) * orbitRadius;
        float sunPosZ = cos(dayNightCycle * toRadians) * orbitRadius;

        // Determina si es día o noche basado en la altura del "sol"
        isDaytime = sunPosY > 0.0f;

        // Dibujar skybox correspondiente
        if (isDaytime) {
            skyboxDay.DrawSkybox(view, projection);
        }
        else {
            skyboxNight.DrawSkybox(view, projection);
        }

        // Configurar iluminación según día o noche
        if (isDaytime) {
            // Sol: amarillo/blanco brillante durante el día
            pointLights[0] = PointLight(1.0f, 0.9f, 0.7f,       // Color amarillento
                0.8f, 1.0f,              // Intensidad ambiental y difusa
                0.0f, sunPosY, sunPosZ,   // Posición
                0.1f, 0.1f, 0.1f);        // Atenuación

            // Luz ambiental direccional más intensa durante el día
            mainLight = DirectionalLight(1.0f, 1.0f, 0.9f,      // Color  
                0.5f, 0.6f,             // Intensidad ambiental y difusa
                0.0f, -1.0f, 0.0f);     // Dirección
            spotLightCount = 0;
            pointLightCount = 0;
        }
        else {
            // Luna: azulada/blanca durante la noche (más tenue)
            pointLights[0] = PointLight(0.8f, 0.8f, 1.0f,       // Color azulado
                0.1f, 0.3f,              // Intensidad ambiental y difusa
                0.0f, -sunPosY, sunPosZ,   // Posición
                0.1f, 0.1f, 0.1f);        // Atenuación

            // Luz ambiental direccional más tenue durante la noche
            mainLight = DirectionalLight(0.1f, 0.1f, 0.3f,      // Color azulado tenue
                0.1f, 0.1f,             // Intensidad ambiental y difusa
                0.0f, -1.0f, 0.0f);     // Dirección
            spotLightCount = 4;
            pointLightCount = 9;

        }

        // Calculate a smooth transition factor between day and night
        float transitionFactor = (sin(dayNightCycle * toRadians) + 1.0f) * 0.5f; // 0 to 1

        // Blend directional light color and intensity based on time of day
        mainLight = DirectionalLight(
            0.1f + 0.9f * transitionFactor,   // Red (darker at night)
            0.1f + 0.9f * transitionFactor,   // Green (darker at night)
            0.3f + 0.6f * transitionFactor,   // Blue (slightly blue-ish at night)
            0.1f + 0.4f * transitionFactor,   // Ambient intensity
            0.1f + 0.5f * transitionFactor,   // Diffuse intensity
            0.0f, -1.0f, 0.0f                 // Direction
        );

        // Create two variants of materials - one for day, one for night
        Material Material_day = Material(2.0f, 256);   // More specular during day
        Material Material_night = Material(1.0f, 128); // Less specular at night

        // Configuración de luces dinámicas en el perímetro
        // Actualiza el ángulo de rotación de las luces
        static float lightRotationAngle = 0.0f;
        float lightRotationSpeed = 0.5f;
        lightRotationAngle += lightRotationSpeed * deltaTimeDos;
        if (lightRotationAngle > 2.0f * glm::pi<float>())
            lightRotationAngle -= 2.0f * glm::pi<float>();

        // Coordenadas para las esquinas
        float cornerX1 = 52.0f;   // Lado derecho X
        float cornerX2 = -39.0f;  // Lado izquierdo X
        float cornerZ1 = 56.0f;   // Lado frontal Z
        float cornerZ2 = -54.0f;  // Lado trasero Z

        // Calcula el ancho y el alto del rectángulo
        float width = cornerX1 - cornerX2;
        float height = cornerZ1 - cornerZ2;

        // Altura para todas las luces puntuales
        float lightHeight = 5.0f;

        // Colores base para las luces
        glm::vec3 colors[] = {
            glm::vec3(1.0f, 0.0f, 0.0f),     // Rojo
            glm::vec3(1.0f, 0.5f, 0.0f),     // Naranja
            glm::vec3(1.0f, 1.0f, 0.0f),     // Amarillo
            glm::vec3(0.0f, 1.0f, 0.0f),     // Verde
            glm::vec3(0.0f, 1.0f, 1.0f),     // Cian
            glm::vec3(0.0f, 0.0f, 1.0f),     // Azul
            glm::vec3(0.5f, 0.0f, 1.0f),     // Púrpura
            glm::vec3(1.0f, 0.0f, 1.0f)      // Magenta
        };

        // Configurar luces dinámicas
        pointLightCount = 9;
        for (int i = 1; i < pointLightCount; i++) {
            float normalizedPos = fmod((float)i / (float)pointLightCount * 4.0f + lightRotationAngle, 4.0f);
            float x, z;

            if (normalizedPos < 1.0f) { // Lado superior
                x = cornerX2 + normalizedPos * width;
                z = cornerZ1;
            }
            else if (normalizedPos < 2.0f) { // Lado derecho
                x = cornerX1;
                z = cornerZ1 - (normalizedPos - 1.0f) * height;
            }
            else if (normalizedPos < 3.0f) { // Lado inferior
                x = cornerX1 - (normalizedPos - 2.0f) * width;
                z = cornerZ2;
            }
            else { // Lado izquierdo
                x = cornerX2;
                z = cornerZ2 + (normalizedPos - 3.0f) * height;
            }

            glm::vec3 color = colors[i - 1];

            pointLights[i] = PointLight(
                color.r, color.g, color.b,    // Color
                0.0f, 1.0f,                  // Intensidad ambiental/difusa
                x, lightHeight, z,           // Posición
                0.3f, 0.2f, 0.1f             // Atenuación
            );
        }

        // Punto de luz para Shenron
        pointLights[pointLightCount] = PointLight(1.0f, 0.5f, 0.0f,  // Color naranja
            1.0f, 2.0f,  // Intensidades
            -85.0f, 3.0f, -35.0f,  // Posición de Shenron
            0.3f, 0.2f, 0.1f);
        pointLightCount++;

        // Configuración shader
        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();
        uniformEyePosition = shaderList[0].GetEyePositionLocation();
        uniformColor = shaderList[0].getColorLocation();
        uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
        uniformShininess = shaderList[0].GetShininessLocation();

        if (tipoCamara == 2) {
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(orthoProjection));
        }
        else {
            glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        }

        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
        glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

        // Usar el material según sea día o noche
        if (isDaytime) {
            Material_day.UseMaterial(uniformSpecularIntensity, uniformShininess);
        }
        else {
            Material_night.UseMaterial(uniformSpecularIntensity, uniformShininess);
        }

        // Configuración de luces en el shader
        shaderList[0].SetDirectionalLight(&mainLight);
        shaderList[0].SetPointLights(pointLights, pointLightCount);
        shaderList[0].SetSpotLights(spotLights, spotLightCount);

        // Inicialización de matrices de modelo y color
        glm::mat4 model(1.0);
        glm::mat4 modelaux(1.0);
        glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec2 toffset = glm::vec2(0.0f, 0.0f);
        glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

        //----------------------------------------
        // RENDERIZADO DE MODELOS
        //----------------------------------------

        // MODELOS DEL UNIVERSO SUPERMAN
        model = glm::mat4(1.0);
        modelaux = model;
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Mapa.RenderModel();

        modelaux = model;
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Fortress.RenderModel();

        /*-------BRAINIAC NAVE ANIMACION---------------*/
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f + verticalOffset, 0.0f));
        model = glm::rotate(model, glm::radians(rotationAmount), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        BrainiacShip.RenderModel();

        /*KRIPTONITA - MASIVA */
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(56.0f, 0.0f, -58.5f));
        model = glm::rotate(model, glm::radians(kryptoniteRotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Kryptonite.RenderModel();

        /*LOGO*/
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(25.0f, 30.0f, -30.5f));
        model = glm::rotate(model, glm::radians(logoRotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        BigLogo.RenderModel();

        /*Bancas*/
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(1.0f, 2.0f, -44.5f));
        model = glm::rotate(model, glm::radians(250.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Bench.RenderModel();

        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(45.0f, 2.0f, -8.0f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Bench.RenderModel();

        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(25.0f, 2.0f, -7.0f));
        model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Bench.RenderModel();

        //Estatua
        model = modelaux;
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        SupermanStatue.RenderModel();

        //Edifico Salón de la Justicia
        modelaux = model;
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Hall.RenderModel();

        // Carrito de comida
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(34.0f, 2.0f, -41.0f));
        model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Carts.RenderModel();

        // MODELOS DEL UNIVERSO DRAGON BALL
        // SHENRON
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-85.0f, 3.0f + shenronYOffset, -35.0f));
        model = glm::scale(model, glm::vec3(0.1f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        shenron.RenderModel();

        // GOKU
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-55.0f, 1.4f, -8.2f));
        model = glm::scale(model, glm::vec3(2.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        goku.RenderModel();

        // TICKETS
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-55.0f, 1.3f, -8.0f));
        model = glm::scale(model, glm::vec3(0.5f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        tickets.RenderModel();

        // PLANETA
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-25.0f, 40.0f, -100.0f));
        model = glm::rotate(model, glm::radians(planetaRotation), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        planeta.RenderModel();

        // NAVES
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-75.0f, 30.0f, -60.0f));
        model = glm::scale(model, glm::vec3(1.0f));
        model = glm::rotate(model, glm::radians(80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        nave.RenderModel();

        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-55.0f, 50.0f, -60.0f));
        model = glm::scale(model, glm::vec3(1.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        nave.RenderModel();

        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-45.0f, 60.0f, -30.0f));
        model = glm::scale(model, glm::vec3(1.0f));
        model = glm::rotate(model, glm::radians(100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        nave.RenderModel();

        // CASA GRANDE
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-25.0f, 1.2f, -64.0f));
        model = glm::scale(model, glm::vec3(0.05f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        casa_capsula.RenderModel();

        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-35.0f, 5.0f, -100.0f));
        model = glm::scale(model, glm::vec3(5.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        casa_kame.RenderModel();

        // ANDROIDE
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(startAndroideX + movXAndroide, 20.0f, startAndroideZ + movZAndroide));
        model = glm::rotate(model, glm::radians(androideRotation), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        androide.RenderModel();

        // COCHE
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-35.0f, 1.5f, -20.0f));
        model = glm::scale(model, glm::vec3(0.1f));
        model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        coche.RenderModel();

        // NAMEK
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-55.0f, -2.0f, -30.0f));
        model = glm::scale(model, glm::vec3(0.5f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        namek.RenderModel();

        // BROLY
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-61.0f, 12.2f, -20.0f));
        model = glm::scale(model, glm::vec3(1.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        broly.RenderModel();

        // CASA
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-55.0f, 0.0f, -55.0f));
        model = glm::scale(model, glm::vec3(0.5f));
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        casa.RenderModel();

        // RADAR (múltiples)
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-45.0f, 1.3f, -45.0f));
        model = glm::scale(model, glm::vec3(3.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        radar.RenderModel();

        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-25.0f, 1.3f, -45.0f));
        model = glm::scale(model, glm::vec3(3.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        radar.RenderModel();

        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-35.0f, 1.3f, -55.0f));
        model = glm::scale(model, glm::vec3(3.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
        radar.RenderModel();

        //CASA DE GOKU DONDE ESTÁ EL JUEGO DEL TOPO
        /*modelaux = model;
		model = glm::translate(model, glm::vec3(-30.0f, 1.3f, -45.0f));
		model = glm::scale(model, glm::vec3(0.4f));  // Puedes ajustar aquí
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		model = modelaux;
		casa_goku.RenderModel();*/


        //CUERPO DEL JUEGO
        model = modelaux;
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-30.0f, 2.0f, -42.5f));
        model = glm::scale(model, glm::vec3(0.15f));  // Puedes ajustar aquí
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        cuerpo_juego.RenderModel();

        //MARTILLO
        glm::vec3 topoPos = posicionesTopo[topoActual];
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(
            topoPos.x - 0.8f,
            topoPos.y + topoY + martilloHeight,
            topoPos.z - 1.0f));
        model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Ajuste de ángulo
        model = glm::rotate(model, glm::radians(martilloRotation), glm::vec3(0.0f, 0.0f, 1.0f)); // Animación de golpe

        model = glm::scale(model, glm::vec3(0.3f)); // Escala ajustable
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        martillo.RenderModel();


        //TOPO
        model = glm::mat4(1.0);
        glm::vec3 basePos2 = posicionesTopo[topoActual];
        model = glm::translate(model, glm::vec3(basePos2.x, basePos2.y + topoY, basePos2.z));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        topo.RenderModel();

        // TREN
        glm::mat4 modelTrain = glm::mat4(1.0f);
        modelTrain = glm::translate(modelTrain, glm::vec3(movXTrain, 0.5f, movZTrain));
        modelTrain = glm::rotate(modelTrain, glm::radians(trainRotation), glm::vec3(0.0f, 1.0f, 0.0f));
        modelTrain = glm::scale(modelTrain, glm::vec3(2.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelTrain));
        thomas.RenderModel();

        // MODELOS DEL UNIVERSO RESIDENT EVIL
        // Cuerpo de Leon Kennedy
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        model = glm::mat4(1.0);
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

        // Modelos de ambiente RE
        model = glm::mat4(1.0);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Mansion.RenderModel();

        model = glm::mat4(1.0);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        TiroHacha.RenderModel();

        model = glm::mat4(1.0);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Torre.RenderModel();

        model = glm::mat4(1.0);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Tren.RenderModel();

        model = glm::mat4(1.0);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Baño.RenderModel();

        model = glm::mat4(1.0);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Torre_Helicoptero.RenderModel();

        model = glm::mat4(1.0);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Torre_Helicoptero_Dos.RenderModel();

        model = glm::mat4(1.0);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Torre_Helicoptero_Tres.RenderModel();

        model = glm::mat4(1.0);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Carro_Abandonado.RenderModel();

        model = glm::mat4(1.0);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Cartel_Circo.RenderModel();

        // Parte 3: Base fija de la rueda de la fortuna
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.541f, 15.716f, 46.624f));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        RuedaFortuna_parteTres.RenderModel();

        // Parte 1: estructura metálica girando
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.541f, 15.716f, 46.624f));
        model = glm::rotate(model, glm::radians(anguloRueda), glm::vec3(0.0f, 0.0f, 1.0f));
        modelaux = model;
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        RuedaFortuna_parteUno.RenderModel();

        // Parte 2: canastas giran con la rueda
        model = modelaux;
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        RuedaFortuna_parteDos.RenderModel();

        // Renders de zombies
        // ZombieUno
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(28.062f, 2.393f, 14.145f + movDragon));
        model = glm::rotate(model, dragongiro * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelaux = model;
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Zombie_Dos_Cuerpo.RenderModel();

        // Renderizado de extremidades del zombie
        // Pierna izquierda
        model = modelaux;
        model = glm::translate(model, glm::vec3(-0.189f, -0.405f, -0.007f));
        model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie) * amplitudMovimientoZombie), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Zombie_Dos_PiernaIzquierda.RenderModel();

        // Pierna derecha
        model = modelaux;
        model = glm::translate(model, glm::vec3(0.103f, -0.448f, -0.022f));
        model = glm::rotate(model, glm::radians(-sin(animacionTiempoZombie) * amplitudMovimientoZombie), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Zombie_Dos_PiernaDerecha.RenderModel();

        // Brazo derecho
        model = modelaux;
        model = glm::translate(model, glm::vec3(0.375f, 0.772f, 0.458f));
        model = glm::rotate(model, glm::radians(-sin(animacionTiempoZombie) * amplitudMovimientoZombie), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Zombie_Dos_BrazoDerecho.RenderModel();

        // Brazo izquierdo
        model = modelaux;
        model = glm::translate(model, glm::vec3(-0.415f, 0.855f, 0.513f));
        model = glm::rotate(model, glm::radians(-sin(animacionTiempoZombie) * amplitudMovimientoZombie), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Zombie_Dos_BrazoIzquierdo.RenderModel();

        // Cabeza
        model = modelaux;
        model = glm::translate(model, glm::vec3(-0.032f, 1.241f, 0.03f));
        model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Zombie_Dos_Cabeza.RenderModel();

        // Tanque
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(18.347f, 3.148f, 55.705f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelaux = model;
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Tanque_Cuerpo.RenderModel();

        model = modelaux;
        model = glm::translate(model, glm::vec3(2.345f, -1.056f, -0.541f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Tanque_LlantasDerechas.RenderModel();

        model = modelaux;
        model = glm::translate(model, glm::vec3(-2.211f, -1.056f, 0.965f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Tanque_LlantasIzquierdas.RenderModel();

        model = modelaux;
        model = glm::translate(model, glm::vec3(-0.178f, 2.082f, -0.712f));
        model = glm::rotate(model, glm::radians(sin(animacionTiempoZombie * 0.5f) * 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Tanque_Capote.RenderModel();

        // Medicinas
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
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, pos + glm::vec3(0.0f, altura, 0.0f));
                    model = glm::rotate(model, tiempoMedicina, glm::vec3(0.0f, 1.0f, 0.0f));
                    glUniform3fv(uniformColor, 1, glm::value_ptr(color));
                    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
                    Medicina.RenderModel();
                }
            }
        }

        // ----------------------------------------------------------------------------------------------------------------------------------
        // ----------------------------------------- UNIVERSO PHINEAS & FERB - RENDERIZACIÓN-------------------------------------------------
        // ----------------------------------------------------------------------------------------------------------------------------------

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
        model = glm::scale(model, glm::vec3(0.75f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Ferb_M.RenderModel();

        // Ferb mano derecha 
        float angleSaludo = sin(ferbHandTime * 0.25f) * 20.0f; // Oscila entre -20 y +20 grados
        modelaux = model; // guarda el modelo base
        model = glm::translate(model, glm::vec3(-0.169f, 0.942f, 0.019f)); // punto de unión al hombro
        model = glm::rotate(model, glm::radians(angleSaludo), glm::vec3(0.0f, 0.0f, 1.0f)); // rotación de saludo
        model = glm::scale(model, glm::vec3(0.75f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Ferb_mano_M.RenderModel();




        // Phineas
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-47.0f, 1.2f, 5.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.75f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Phineas_M.RenderModel();
        // Phineas mano izquierda
        float anglePhineasSaludo = sin(phineasHandTime * 0.25f) * 25.0f;
        modelaux = model; // Guarda la transformación base
        model = glm::translate(model, glm::vec3(0.126f, 0.912f, 0.035f)); // Punto de unión del brazo
        model = glm::rotate(model, glm::radians(anglePhineasSaludo), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotación tipo saludo
        model = glm::scale(model, glm::vec3(0.75f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Phineas_mano_M.RenderModel();



        //Candace
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-35.0f, 1.2f, 20.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.75f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Candace_M.RenderModel();

        //Isabella
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-30.0f, 1.2f, 40.0f));
        model = glm::scale(model, glm::vec3(0.75f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Isabella_M.RenderModel();

        //Bufard
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-26.0f, 1.2f, 64.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.75f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Bufard_M.RenderModel();

        //Baljeet
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-20.0f, 1.2f, 40.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.75f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Baljeet_M.RenderModel();




        // --------------------------------------------JUEGO DE PERRY ---------------------------------------------------------------------

        //Maquina de perry
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-45.0f, 1.2f, 22.0f));
        model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.75f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        topo_machine_M.RenderModel();

        //Perry
        model = glm::mat4(1.0);
        glm::vec3 basePos = posicionesPerry[perryActual];
        model = glm::translate(model, glm::vec3(basePos.x, basePos.y + perryY, basePos.z));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Perry_M.RenderModel();

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

        //Doof
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-43.5f, 1.2f, 21.75f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.75f));
        modelaux = model; // Guarda la transformación base

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Doof_M.RenderModel();

        // BICEPS (rotación local en eje X)
        model = glm::translate(modelaux, glm::vec3(-0.497f, 2.205f, -0.066f)); // punto de unión
        model = glm::rotate(model, glm::radians(rotBicep), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Doof_bicep_M.RenderModel();

        // BRAZO (relativo al bicep)
        model = glm::translate(model, glm::vec3(-0.232f, -0.066f, 0.602f)); // unión
        model = glm::rotate(model, glm::radians(rotBrazo), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Doof_brazo_M.RenderModel();

        // MUÑECA (relativa al brazo)
        model = glm::translate(model, glm::vec3(-0.100f, 0.465f, 0.290f)); // unión
        model = glm::rotate(model, glm::radians(rotMuneca), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        Doof_muneca_M.RenderModel();

        // -----------------------------------------------------------------------------------------------------------------

        //---------------JUEGO DE LOS GLOBOS----------------
        // Carpa Perry
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-15.0f, 1.2f, 50.0f));
        model = glm::scale(model, glm::vec3(0.75f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        carpa_globo_M.RenderModel();

        // Base inicial después de la carpa
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, 3.2f));
        glm::mat4 modelBase = model;

        // Offsets para columnas (-1, 0, 1 en X), cada una con 3 globos apilados en Y
        float xOffsets[] = { -1.0f, 0.0f, 1.0f };

        for (int col = 0; col < 3; ++col) {
            glm::mat4 colBase = glm::translate(modelBase, glm::vec3(xOffsets[col], 0.0f, 0.0f));
            for (int row = 0; row < 3; ++row) {
                if (!globos[row][col]) continue;  // No dibujar globo si está desactivado

                glm::mat4 globoModel = glm::translate(colBase, glm::vec3(0.0f, row * 1.0f, 0.0f));
                glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(globoModel));
                globo_M.RenderModel();
            }
        }

        for (int col = 0; col < 3; ++col) {
            glm::mat4 colBase = glm::translate(modelBase, glm::vec3(xOffsets[col], 0.0f, 0.0f));
            for (int row = 0; row < 3; ++row) {
                if (globosPonchados[row][col]) {
                    glm::mat4 globoPonchadoModel = glm::translate(colBase, glm::vec3(0.0f, row * 1.0f, 0.0f));
                    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(globoPonchadoModel));
                    globo_ponchado_M.RenderModel();
                }
            }
        }



        //dardos
        // Aumenta la rotación durante el lanzamiento
        if (dardoEstado == 1) {
            rotacionDardo += velocidadRotacionDardo * deltaTime;
            if (rotacionDardo > 360.0f) rotacionDardo -= 360.0f;
        }
        else if (dardoEstado == 0) {
            rotacionDardo = 0.0f; // reinicia para cada nuevo lanzamiento
        }

        // Render dardo en movimiento
        model = glm::mat4(1.0);
        model = glm::translate(model, posDardoActual);
        model = glm::rotate(model, glm::radians(rotacionDardo), glm::vec3(0.0f, 0.0f, 1.0f)); // ROTACIÓN EN Z
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        dardo_M.RenderModel();


        for (const glm::vec3& posFinal : dardosFinales) {
            glm::mat4 modelDardoFinal = glm::mat4(1.0f);
            modelDardoFinal = glm::translate(modelDardoFinal, posFinal);
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelDardoFinal));
            dardo_M.RenderModel();
        }


        //linea roja
        model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(-15.0f, 1.3f, 48.0f));
        //model = glm::scale(model, glm::vec3(0.75f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        linea_roja_M.RenderModel();


        //---------------------------------------------------------


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

        animaciones_ferb(deltaTime);

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