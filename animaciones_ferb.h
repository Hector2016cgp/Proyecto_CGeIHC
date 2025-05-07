// animaciones_ferb.h
#ifndef ANIMACIONES_FERB_H
#define ANIMACIONES_FERB_H

#include <glm.hpp>
#include <vector>

// Variables globales del universo Phineas & Ferb
extern float tiempoCarrusel;
extern float ballonyTime;
extern float ferbHandTime;
extern float phineasHandTime;

extern glm::vec3 posicionesPerry[8];
extern int perryActual;
extern float perryY;
extern bool subiendo;
extern float esperaActual;
extern bool esperando;

extern float doofGolpeTime;
extern float rotBicep;
extern float rotBrazo;
extern float rotMuneca;

extern float posX;
extern float posY;
extern float posZ;

extern glm::vec3 dardoInicio;
extern glm::vec3 dardoObjetivos[3];
extern int dardoEstado;
extern int tiradaActual;
extern float tiempoEspera_dardos;
extern float tLanzamiento;
extern float duracionLanzamiento;
extern glm::vec3 posDardoActual;
extern std::vector<glm::vec3> dardosFinales;
extern bool globos[3][3];
extern bool globosPonchados[3][3];
extern float rotacionDardo;
extern float velocidadRotacionDardo;

// Prototipo de función para actualizar animaciones
void animaciones_ferb(float deltaTime);

#endif // ANIMACIONES_FERB_H
