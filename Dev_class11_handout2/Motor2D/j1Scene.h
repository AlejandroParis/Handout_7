#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class j1UIImage;
class j1UILabel;
class j1UIElement;
class j1UIButton;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnMouseClick(j1UIElement* element);
	bool OnMouseHover(j1UIElement* element);
	bool OnMouseRelease(j1UIElement* element);
	bool OnMouseExit(j1UIElement* element);

private:
	SDL_Texture* debug_tex;
	j1UIImage* banner;
	j1UILabel* text;
	j1UILabel* window_title;
	j1UIButton* button;
};

#endif // __j1SCENE_H__