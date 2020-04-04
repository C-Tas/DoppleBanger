#include "HUD.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

HUD::~HUD()
{
	for (auto it = elementsHUD_.begin(); it != elementsHUD_.end(); ++it) {
		delete(*it);
	}
	elementsHUD_.clear();
}

const void HUD::draw()
{
	for (auto it = elementsHUD_.begin(); it != elementsHUD_.end(); ++it) {
		(*it)->draw();
	}

	glm::dmat4 aMat = mViewMat * mModelMat;  // glm matrix multiplication
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(glm::value_ptr(aMat));
	glColor3d(mColor.r, mColor.g, mColor.b);
	glLineWidth(20);

	if (vVertices.size() > 0) {  // transfer data
	// transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
		if (vColors.size() > 0) { // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
		}

		glDrawArrays(mPrimitive, 0, mNumVertices);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	glLineWidth(1);
	glColor3d(1, 1, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer
	glutSwapBuffers();	// swaps the front and back buffer
}

bool HUD::update()
{
	return false;
}

void HUD::initObject()
{
	//Creacion del fondo del HUD
	SDL_Rect destRect;

	//Timon
	destRect.w = W_WHEEL; destRect.h = H_WHEEL;
	destRect.x = (app_->getWindowWidth() / 10) - W_WHEEL / 2;
	destRect.y = app_->getWindowHeight() * 5 / 7;
	wheel_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::WheelHUD), destRect);
	elementsHUD_.push_back(wheel_);

	//Cuerda
	destRect.w = W_ROPE; destRect.h = H_ROPE;
	destRect.x = app_->getWindowWidth() / 10;
	destRect.y = app_->getWindowHeight() * 3 / 4;
	rope_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::RopeHUD), destRect);
	elementsHUD_.push_back(rope_);

	//Skills y objetos
	destRect.w = W_SKILLS; destRect.h = H_SKILLS;
	destRect.x = (app_->getWindowWidth() / 2) - W_SKILLS / 2;
	destRect.y = app_->getWindowHeight() * 6 / 7;
	skills_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::SkillsHUD), destRect);
	elementsHUD_.push_back(skills_);

	//Para el líquido que representa la vida
	mViewMat = lookAt(mEye, mLook, mUp);
	mPrimitive = GL_LINE_LOOP;
	mNumVertices = 360;
	vVertices.reserve(mNumVertices);
	float a = 90 + 100;

	for (int i = 0; i < mNumVertices; i++) {
		vVertices.emplace_back(100 * cos(glm::radians(a)), 100 * sin(glm::radians(a)), 0.0);
		if (i < mNumVertices - 200) a += 360.0 / 360;
	}

	mColor = (glm::dvec4(1.0, 0.0, 1.0, 1.0));
}