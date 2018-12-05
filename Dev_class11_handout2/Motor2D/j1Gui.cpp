#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Scene.h"
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
	int x, y;
	App->input->GetMousePosition(x, y);
	for (p2List_item<j1UIElement*>* item = elements.start; item != NULL; item = item->next)
	{
		j1UIElement* current_element = item->data;
		if (current_element->IsInside(x, y))
		{
			if (!current_element->hovered) 
			{
				if (current_element->interactable) ((j1UIInteractable*)current_element)->OnMouseHover();
				current_element->scene->OnMouseHover(item->data);
				current_element->hovered = true;
			}
			else if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT))
			{
				if (current_element->interactable) ((j1UIInteractable*)current_element)->OnMouseClick();
				current_element->scene->OnMouseClick(item->data);

			}
		}
		else if(current_element->hovered)
		{
			if (current_element->interactable) ((j1UIInteractable*)current_element)->OnMouseExit();
			current_element->scene->OnMouseExit(item->data);
			current_element->hovered = false;
		}
	}
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

j1UIImage * j1Gui::CreateImage(iPoint pos, SDL_Rect rect, j1Scene* scene)
{
	j1UIImage* image = new j1UIImage(pos, rect);
	image->scene = scene;
	elements.add(image);

	return image;
}

j1UILabel * j1Gui::CreateLabel(iPoint pos, p2SString path, int size, p2SString text, SDL_Color color, j1Scene* scene)
{
	_TTF_Font* font = App->font->Load(path.GetString(), size);
	j1UILabel* label = new j1UILabel(pos, font,text,color);
	label->scene = scene;
	elements.add(label);


	return label;
}

j1UIButton * j1Gui::CreateButton(iPoint pos, j1Scene * scene)
{
	j1UIButton* button = new j1UIButton(pos);
	button->scene = scene;
	elements.add(button);

	return button;
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

bool j1UIElement::IsInside(int x, int y)
{
	return((x < rect_box.x + rect_box.w)&&(rect_box.x<x) && (y < rect_box.y + rect_box.h)&&(rect_box.y < y));
}

j1UIImage::j1UIImage(iPoint pos, SDL_Rect rect)
{
	rect_box = { pos.x,pos.y,rect.w,rect.h };
	this->rect_sprite = rect;
}

j1UIImage::~j1UIImage()
{
}

bool j1UIImage::UIBlit()
{
	App->render->Blit(App->gui->GetAtlas(), rect_box.x, rect_box.y, &rect_sprite, 0.0F);
	return true;
}

j1UILabel::j1UILabel(iPoint pos, _TTF_Font* font, p2SString text, SDL_Color color)
{
	App->font->CalcSize(text.GetString(), rect_box.w, rect_box.h, font);
	rect_box.x = pos.x;
	rect_box.y = pos.y;
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
	App->render->Blit(texture, rect_box.x, rect_box.y, nullptr, 0.0F);
	SDL_DestroyTexture(texture);
	return true;
}

void j1UILabel::SetText(p2SString text)
{
	this->text = text;
}



j1UIButton::~j1UIButton()
{
}

bool j1UIButton::UIBlit()
{
	App->render->Blit(App->gui->GetAtlas(), rect_box.x, rect_box.y, &rect_sprite, 0.0F);
	return true;
}

void j1UIButton::OnMouseClick()
{
	rect_sprite = anim[2];
}

void j1UIButton::OnMouseHover()
{
	rect_sprite = anim[1];
}

void j1UIButton::OnMouseRelease()
{
	rect_sprite = anim[1];
}

void j1UIButton::OnMouseExit()
{
	rect_sprite = anim[0];
}

j1UIButton::j1UIButton(iPoint position)
{
	interactable = true;
	rect_box = { position.x, position.y, 229,69 };
	anim = new SDL_Rect[3];
	anim[0] = { 0,113,229,69 };
	anim[1] = { 411,169,229,69 };
	anim[2] = { 642,169,229,69 };
	rect_sprite = anim[0];
}
