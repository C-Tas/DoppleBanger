#pragma once
#include "Draw.h"
#include <list>
#include <GL/freeglut.h>
#include <glm.hpp>

class HUD : public Draw
{
public:
	HUD(Application* app) : Draw(app, { 0,0 }, { 0,0 }) { initObject(); };
	~HUD();

	const virtual void draw();
	virtual bool update();

private:
	list<Draw*> elementsHUD_; //Lista de los elementos del HUD
	Draw* wheel_ = nullptr; //Timon
	Draw* rope_ = nullptr; //Cuerda
	Draw* skills_ = nullptr; //Skills y objetos

	GLuint mPrimitive = GL_TRIANGLES;
	GLuint mNumVertices = 0;
	vector<glm::dvec3> vVertices;
	vector<glm::dvec4> vColors;
	glm::dmat4 mModelMat;
	glm::dmat4 mViewMat = glm::dmat4(1.0);
	glm::dvec4 mColor;

	glm::dvec3 mEye = { 0.0, 0.0, 500.0 };
	glm::dvec3 mLook = { 0.0, 0.0, 0.0 };
	glm::dvec3 mUp = { 0.0, 1.0, 0.0 };

#pragma region Constantes
	//Timon
	const uint W_WHEEL = app_->getWindowWidth() * 3 / 19;
	const uint H_WHEEL = W_WHEEL;

	//Cuerda
	const uint W_ROPE = app_->getWindowWidth() * 7 / 8;
	const uint H_ROPE = app_->getWindowHeight() * 2 / 9;

	//Skills
	const uint W_SKILLS = app_->getWindowWidth() * 5 / 13;
	const uint H_SKILLS = app_->getWindowHeight() / 10;
#pragma endregion

	//Inicializa el objeto
	virtual void initObject();
};

