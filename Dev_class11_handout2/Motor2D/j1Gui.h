#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"

#define CURSOR_WIDTH 2

class _TTF_Font;
// TODO 1: Create your structure of classes
class j1UIElement
{
public:
	SDL_Rect rect_box;
	SDL_Rect rect_sprite;
	bool hovered = false;
	bool interactable = false;
	j1Scene* scene;
	j1UIElement();
	~j1UIElement();
	virtual bool UIBlit();
	virtual bool UICleanUp();
	virtual bool IsInside(int x, int y);
};

class j1UIInteractable : public j1UIElement
{
public:
	SDL_Rect* anim;

	virtual void OnMouseClick() {};
	virtual void OnMouseHover() {};
	virtual void OnMouseRelease() {};
	virtual void OnMouseExit() {};
};

class j1UIImage : public j1UIElement
{
public:

	j1UIImage(iPoint pos, SDL_Rect rect);
	~j1UIImage();
	bool UIBlit();
};
class j1UILabel : public j1UIElement
{
public:
	_TTF_Font* font;
	p2SString text;
	SDL_Color color;
	j1UILabel(iPoint pos, _TTF_Font* font, p2SString text, SDL_Color color);
	~j1UILabel();
	bool UIBlit();
	void SetText(p2SString text);
};
class j1UIButton : public j1UIInteractable
{
public:
	//j1UILabel label;
	j1UIButton(iPoint pos);
	~j1UIButton();

	bool UIBlit();
	void OnMouseClick();
	void OnMouseHover();
	void OnMouseRelease();
	void OnMouseExit();
};
// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	j1UIImage* CreateImage(iPoint pos, SDL_Rect rect, j1Scene* scene);
	j1UILabel* CreateLabel(iPoint pos, p2SString path, int size, p2SString text, SDL_Color color, j1Scene* scene);
	j1UIButton* CreateButton(iPoint pos, j1Scene* scene);
	

	SDL_Texture* GetAtlas() const;

private:
	p2List<j1UIElement*> elements;
	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__