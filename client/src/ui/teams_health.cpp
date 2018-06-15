#include "teams_health.h"

#define PADDING_PERCENT 5
#define WHITE_TICKNESS_PERCENT 10
#define SIZE_TEXT_PERCENT 25
#define BARS_PERCENT 75
#define WORMS_PER_TEAM 3

View::TeamsHealth::TeamsHealth(SDL_Renderer * r, int width, int height, int teamsAmount, int wormsHealth) : 
  text(height / (100 / SIZE_TEXT_PERCENT), 2, gPath.PATH_FONT_ARIAL_BOLD) {
  this->width = width;
  this->height = height;
  this->teamsAmount = teamsAmount;
  this->wormsHealth = wormsHealth;
  this->padding = this->height / (100 / PADDING_PERCENT);
  this->heightHealthRect = (height / (100 / BARS_PERCENT) / teamsAmount) - (this->padding * 2);
  this->whiteTickness = this->heightHealthRect / (100 / WHITE_TICKNESS_PERCENT);
  this->maxTeamHealth = WORMS_PER_TEAM * this->wormsHealth;
  this->hide = false;

  SDL_Color black = {0,0,0,0};
  this->text.setBackgroundColor(black);

  SDL_Color white = {255, 255, 255, 255};
  this->text.setTextColor(white);

  this->text.setText(r, "Teams health");
  
  for (int i = 0 ; i < this->teamsAmount ; i++) {
    this->teamsHealth[i+1] = this->maxTeamHealth;
  }
}

View::TeamsHealth::~TeamsHealth() {

}

int View::TeamsHealth::getWidth(void) const {
	return this->width;
}

int View::TeamsHealth::getHeight(void) const {
	return this->height;
}

int View::TeamsHealth::getX(void) const {
	return this->x;
}

int View::TeamsHealth::getY(void) const {
	return this->y;
}

void View::TeamsHealth::setX(int x) {
	this->x = x - this->width / 2;
  this->text.setX(x);
}

void View::TeamsHealth::setY(int y) {
	this->y = y - this->height / 2;
  this->text.setY(y - this->height / 2 + this->text.getHeight() / 2);
}

void View::TeamsHealth::render(SDL_Renderer * r, int camX, int camY) {
  if (this->hide) {
    return;
  }
  
  const SDL_Color colors[] = {
    {0, 0, 0, 0},
    {255, 0, 0, 0},
    {0, 255, 0, 0},
    {0, 0, 255, 0}
  };
  
  // Render text
  this->text.render(r, camX, camY);

  for (int i = 0 ; i < this->teamsAmount ; i++) {
    // White rects
    SDL_Rect whiteRect = {
      this->x + this->padding,
      this->y + i * (this->padding + this->heightHealthRect) + this->text.getHeight(),
      this->width - this->padding * 2,
      this->heightHealthRect
    };

    SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);        
    SDL_RenderFillRect(r, &whiteRect);

    // Black rects
    SDL_Rect blackRect = {
      this->x + this->padding + this->whiteTickness,
      this->y + i * (this->padding + this->heightHealthRect) + this->whiteTickness + this->text.getHeight(),
      this->width - this->padding * 2 - this->whiteTickness * 2,
      this->heightHealthRect - this->whiteTickness * 2
    };

    SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF);        
    SDL_RenderFillRect(r, &blackRect);

    int currentHealth = this->teamsHealth[i + 1];
    int maxRectHealthWidth = this->width - this->padding * 2 - this->whiteTickness * 2;
    int rectHealthWidth = (currentHealth * maxRectHealthWidth) / this->maxTeamHealth;

    // Team health rect
    SDL_Rect teamRect = {
      this->x + this->padding + this->whiteTickness,
      this->y + i * (this->padding + this->heightHealthRect) + this->whiteTickness + this->text.getHeight(),
      rectHealthWidth,
      this->heightHealthRect - this->whiteTickness * 2
    };

    SDL_SetRenderDrawColor(r, colors[i+1].r, colors[i+1].g, colors[i+1].b, colors[i+1].a);        
    SDL_RenderFillRect(r, &teamRect);    
  }
}

void View::TeamsHealth::update(const YAML::Node & teamsHealthNode) {
  YAML::const_iterator it = teamsHealthNode.begin();

  for (; it != teamsHealthNode.end() ; it++) {
    int teamId = it->first.as<int>();
    this->teamsHealth[teamId] = it->second.as<int>();
  }
}

void View::TeamsHealth::toggleHide(void) {
  this->hide = !this->hide;
}