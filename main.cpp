#include "source/headers.h"
bool init(SDL_Renderer*& renderer, SDL_Window*& window); // TODO: Write methods for initializing individual renderers, windows, ect
void close(SDL_Window* window);
void clearScreen(SDL_Renderer* renderer);
void renderChanges(SDL_Renderer* renderer, SDL_Window* window);
SDL_Renderer* DrawGroup::renderer = NULL;

int main(int argc, char *argv[]) {
	SDL_Window* gWindow = NULL; // TODO: Rename these to something not dumb and arbitrary
	SDL_Renderer* gRenderer = NULL;
	if(!init(gRenderer, gWindow)) {
		printf("Failed to initialize!\n");
		return 0;
	}
	Line tempLine;
	tempLine.setColorChannels(0x00, 0xFF, 0xFF);
	Point newPoint;
	
	Dot dot = Dot(Point(300, 150));
	dot.setColorChannels(0xFF);
	
	Configuration config;
	
	DrawGroup::SET_RENDERER(gRenderer);
	
	CollideBaseGroup* boxes = new CollideBaseGroup; // TODO: Try and get rid of raw pointers where possible
	std::vector<BackElement*>* ground = new std::vector<BackElement*>;
	/* TODO: Add method for initializing everything on screen to clean up main() and help smooth the transition to using 'Screen' as the base class for the project */
	 
	/* TODO: Create a file structure for containing level data so its not hardcoded */
	/* Initializes the pointer to the single texture shared by all Box objects, then creates the boxes and assigns the pointer to them */
	SuperTexture* mTexture = Box::createBoxTexture(gRenderer);
	boxes->push_back(new Box(Point(50, 50)));
	boxes->push_back(new Box(Point(200, 200)));
	boxes->push_back(new Box(Point(350, 200)));
	boxes->push_back(new Box(Point(500, 200)));
	boxes->setTexture(mTexture);
	
	BackgroundGroup groundGroup;
	for (int x = 0; x <= Screen::MAX_WIDTH; x += 100) {
		for (int y = 0; y <= Screen::MAX_HEIGHT; y += 100) {
			groundGroup.add(Point(x, y), Ground::GRASS);
		}
	}
	
	
	BadTest small(Point(300, 350), boxes);
	small.set(gRenderer);
	
	Font gFont = Font();
	BoundedPoint screenPos = BoundedPoint(Screen::MAX_WIDTH - Screen::SCREEN_WIDTH, Screen::MAX_HEIGHT - Screen::SCREEN_HEIGHT);
	
	PointDelta px;
	std::string foo = "mani is pretty smart sometimes, but kotlin is a dumb language cause it has no semi-colons iirc";
	AppearingText ap(foo, 10, 0, 20, "resources/Font.ttf", COLORS::RED, Point(0, 0), 300);
	
	PointDelta* popo = new PointDelta(0, 0, 4);
	Controller contra(config);
	contra.addListener("Ray", 120);
	contra.addPlayerKeys(popo);
	FpsText text(new Font(), Point(100, 10), COLORS::RED);
	while(!contra.quit) {
		clearScreen(gRenderer); /* Clear the screen */
		/* Event Handling */
		popo->zero(); // Find a cleaner way
		contra.handleEvents();
		
		/* Collision Detection */
		if (popo->getNonZero()) {
			dot.collideTest((*popo) * text.getRatio(), boxes, screenPos);
		}
		
		/* Drawing things onto the screen */
		groundGroup.drawGroup(screenPos);
		boxes->drawGroup(screenPos);
		small.render(gRenderer, screenPos);
		ap.update(gRenderer); // TODO: Seperate the upating and the drawing of entities
		dot.draw(gRenderer, screenPos.negate()); // Player must always be drawn onto the top layer for best visibility
		
		
		/* Raycasting */
		if (contra.checkListener(config["Ray"]).getHeld()) {
			newPoint = collideTestVectorToRay(boxes, dot.getRay());
			if (!newPoint.isNull()) {
				tempLine = Line(dot.getCenter(), newPoint.copy());
				tempLine.drawLine(gRenderer, screenPos);
			}
		}
		
		text.draw(gRenderer); // Draw FPS on screen
		renderChanges(gRenderer, gWindow); /* Render all changes onto the window */
	}
	close(gWindow);
	delete popo;
	delete mTexture;
	delete ground;
	delete boxes;
	return 0;
}


bool init(SDL_Renderer*& renderer, SDL_Window*& gWindow) {
	//Initialization flag
	bool success = true;
	
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	} else {
		SDL_Init(SDL_INIT_VIDEO);
		//Create window
		gWindow = SDL_CreateWindow(Screen::WINDOW_TITLE.c_str(), Screen::DEFAULT_POS, Screen::DEFAULT_POS, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		} else {
			/* Initialize true-type font */
			TTF_Init();
			/* Create renderer */
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		}
	}
	return success;
}

void close(SDL_Window* window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void clearScreen(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}

void renderChanges(SDL_Renderer* renderer, SDL_Window* window) {
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}
