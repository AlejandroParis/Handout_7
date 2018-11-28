#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	for (p2List_item<j1UIElement*>* item = elements.start; item != NULL; item = item->next)
	{
		item->data->UIBlit();
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

j1UIImage * j1Gui::CreateImage(iPoint pos, SDL_Rect rect)
{
	j1UIImage* image = new j1UIImage(pos, rect);
	elements.add(image);

	return image;
}

j1UILabel * j1Gui::CreateLabel(iPoint pos, p2SString path, int size, p2SString text, SDL_Color color)
{
	_TTF_Font* font = App->font->Load(path.GetString(), size);
	j1UILabel* label = new j1UILabel(pos, font,text,color);
	elements.add(label);


	return label;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

j1UIElement::j1UIElement()
{
}

j1UIElement::~j1UIElement()
{
}

bool j1UIElement::UIBlit()
{
	return true;
}

bool j1UIElement::UICleanUp()
{
	return true;
}

j1UIImage::j1UIImage(iPoint pos, SDL_Rect rect)
{
	position = pos;
	this->rect = rect;
}

j1UIImage::~j1UIImage()
{
}

bool j1UIImage::UIBlit()
{
	App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &rect, 0.0F);
	return true;
}

j1UILabel::j1UILabel(iPoint pos, _TTF_Font* font, p2SString text, SDL_Color color)
{
	position = pos;
	this->font = font;
	this->text = text;
	this->color = color;
}
j1UILabel::~j1UILabel()
{
}

bool j1UILabel::UIBlit()
{
	SDL_Texture* texture = App->font->Print(text.GetString(), color, font);
	App->render->Blit(texture, position.x, position.y, nullptr, 0.0F);
	SDL_DestroyTexture(texture);
	return true;
}
