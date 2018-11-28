#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"

#define CURSOR_WIDTH 2

class _TTF_Font;
// TODO 1: Create your structure of classes
class j1UIElement
{
public:
	iPoint position;
	SDL_Rect rect;
	j1UIElement();
	~j1UIElement();
	virtual bool UIBlit();
	virtual bool UICleanUp();
};
class j1UIImage : public j1UIElement
{
public:
	j1UIImage(iPoint pos,SDL_Rect rect);
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
	j1UIImage* CreateImage(iPoint pos, SDL_Rect rect);
	j1UILabel* CreateLabel(iPoint pos, p2SString path, int size, p2SString text, SDL_Color color);
	

	SDL_Texture* GetAtlas() const;

private:
	p2List<j1UIElement*> elements;
	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__