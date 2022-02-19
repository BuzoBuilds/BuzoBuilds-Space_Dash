//BuzoBuilds Space_Dash for the Arduino Mega 
//depends on teh LED_Matrix_Lib library and the LED_Matrix_Game_Lib library 
#include "LED_Matrix_Lib.h" 
#include "LED_Matrix_Game_Lib.h" 

DataMatrix dm; 
FrameRateController fc; 
Controller controller; 

//class for the player
class Player : public GameObject{ 
public:
  void initPlayer(float x, float y){
    this->x = x; 
    this->y = y; 
    this->head = NULL;
  
    //make and attach colider for player
    Colider * c = (Colider *)malloc(sizeof(Colider)); 
    c->x = this->x- 1; 
    c->y = this->y -2; 
    c->l = 5; 
    c->w = 2;  
    c->next = NULL; 

    this->addColider(c);  
  }   

  //code to draw player on the DataMatrix, which will eventually draw its self on the LED Matrix
  void draw(int state){
    if(state == 0){   

      dm.addPixel(this->x-1,this->y+1,7);
      dm.addPixel(this->x-1,this->y,7);
      dm.addPixel(this->x-1,this->y-1,7);

      dm.addPixel(this->x,this->y-2,7); 
      dm.addPixel(this->x,this->y-1,7); 
      dm.addPixel(this->x,this->y,7); 
      dm.addPixel(this->x,this->y+1,7); 
      dm.addPixel(this->x,this->y+2,7); 

      dm.addPixel(this->x+1,this->y,7);  

      dm.addPixel(this->x+2,this->y,7); 

      dm.addPixel(this->x+3,this->y,7);
    }
  } 

};  

//class for the player's fire
class PlayerFire : public GameObject{ 
  char length;
  char width;


  public: 
    void initPlayerFire(float x, float y){
      this->x = x; 
      this->y = y; 
      this->head = NULL; 

      this->length = 1; 
      this->width = 4;

      Colider *c = (Colider *)malloc(sizeof(Colider)); 
      c->x = this->x; 
      c->y = this->y; 
      c->l = this->length; 
      c->w = this->width;  
      c->next = NULL;

      this->addColider(c); 
    } 

    void draw (int state){
      dm.addRect(this->x,this->y, this->width, this->length, 2); 
    } 

  
}; 

//class for the Alien enemies
class Alien : public GameObject{
  char length; 
  char width; 
  char color;
  

  public: 
    int state;  
    void initAlien(float x, float y, char color){
      this->x =x; 
      this->y = y; 
      this->head = NULL; 

      this->length = 5; 
      this->width = 6;  
      this->color = color; 
      this->state = 0;  

      Colider *c = (Colider *)malloc(sizeof(Colider)); 
      c->x = this->x; 
      c->y = this->y-2;
      c->l = this->length; 
      c->w = this->width; 
      c->next = NULL; 

      this->addColider(c);
    } 

    //The different states are used to create animation
    void draw(int state){
      if(state == 0){

        dm.addPixel(this->x, this->y+1, this->color); 
        dm.addPixel(this->x+1, this->y+1, this->color);

        dm.addPixel(this->x-1,this->y,this->color); 
        dm.addPixel(this->x, this->y, this->color); 
        dm.addPixel(this->x+1,this->y,this->color); 
        dm.addPixel(this->x+2, this->y, this->color); 

        dm.addPixel(this->x, this->y-1, this->color); 
        dm.addPixel(this->x+1, this->y-1, this->color);  

        dm.addPixel(this->x-1,this->y-2, this->color); 
        dm.addPixel(this->x+2, this->y-2, this->color); 

      }  
      else if(state == 1){
        dm.addPixel(this->x,this->y,7);
      }  
       else if(state == 2){
        dm.addPixel(this->x,this->y,7);
      } 
      else if(state == 3){  
        dm.addPixel(this->x,this->y + 2,this->color); 

        dm.addPixel(this->x -2,this->y ,this->color);
        dm.addPixel(this->x,this->y,7); 
        dm.addPixel(this->x + 2,this->y ,this->color); 

        dm.addPixel(this->x,this->y - 2,this->color);

      } 
      else if (state ==4){ 

        dm.addPixel(this->x,this->y + 3,this->color);  

        dm.addPixel(this->x-2, this->y+2, this->color);
        dm.addPixel(this->x,this->y + 2,this->color);  
        dm.addPixel(this->x+2, this->y+2, this->color);

        dm.addPixel(this->x -3,this->y ,this->color);
        dm.addPixel(this->x -2,this->y ,this->color);
        dm.addPixel(this->x,this->y,7); 
        dm.addPixel(this->x + 2,this->y ,this->color); 
        dm.addPixel(this->x + 3,this->y ,this->color); 

        dm.addPixel(this->x-2, this->y-2, this->color);
        dm.addPixel(this->x,this->y - 2,this->color); 
        dm.addPixel(this->x+2, this->y-2, this->color);
  

        dm.addPixel(this->x,this->y - 3,this->color); 

      } 
      else{ 
        dm.addPixel(this->x,this->y+4, this->color); 

        dm.addPixel(this->x-3,this->y+3,this->color);
        dm.addPixel(this->x,this->y + 3,this->color);  
        dm.addPixel(this->x+3,this->y + 3,this->color);   

        dm.addPixel(this->x-2, this->y+2, this->color);
        dm.addPixel(this->x,this->y + 2,this->color);  
        dm.addPixel(this->x+2, this->y+2, this->color);

        dm.addPixel(this->x-4,this->y,this->color);
        dm.addPixel(this->x -3,this->y ,this->color);
        dm.addPixel(this->x -2,this->y ,this->color);
        dm.addPixel(this->x,this->y,7); 
        dm.addPixel(this->x + 2,this->y ,this->color); 
        dm.addPixel(this->x + 3,this->y ,this->color); 
        dm.addPixel(this->x+4,this->y,this->color);

        dm.addPixel(this->x-2, this->y-2, this->color);
        dm.addPixel(this->x,this->y - 2,this->color); 
        dm.addPixel(this->x+2, this->y-2, this->color);
  

        dm.addPixel(this->x-3,this->y-3,this->color);
        dm.addPixel(this->x,this->y - 3,this->color);  
        dm.addPixel(this->x+3,this->y - 3,this->color); 

        dm.addPixel(this->x,this->y+4,this->color);   


      }

    } 

    /*void shoot(){

    }*/ 
}; 

// class for stars
class Star: public GameObject{ 
  public: 
  void initStar(float x, float y){
    this->x = x; 
    this->y = y; 
    this->head = NULL;
  }
  void draw(int state){
    dm.addPixel(this->x,this->y,7);
  }
}; 

//static function that is invoked when controller interrupt is triggered
static void invokeControllerHandeler(){
  controller.controllerInterruptHandeler(); 
} 

Player p; 
const int maxPlayerFire = 5;  
PlayerFire * playerFires[maxPlayerFire]; 

const int maxAliens = 10;
Alien * aliens[maxAliens]; 

const int maxStars = 20; 
Star * stars[maxStars ];

void setup() {
  //init game 
  Serial.begin(9600); 

  //init game
  fc.initFrameRateController(60); 
  dm.clearDataMatrix(); 
  setMatrixAddyToZero(); 
  init_LED_Matrix(35,34,36,22,23,24,26,27,28,30,31,32,33,29); 
  controller.initController(2,3,4,5,6,10,8); 
  attachInterrupt(digitalPinToInterrupt(2), invokeControllerHandeler, CHANGE); 

  //init GameObjects 
  p.initPlayer(6,16);  

  for(char i = 0; i < maxPlayerFire; i++){
    playerFires[i] = NULL;
  } 

  for(char i = 0; i < maxAliens; i++){
    aliens[i] = NULL;
  } 

  for(char i = 0; i < maxStars; i++){
    stars[i] = (Star *)malloc(sizeof(Star)); 
    stars[i]->initStar(random(0,64),random(0,32));
  }

}

void loop() {
  // put your main code here, to run repeatedly:  
  //start frame 
  fc.setFrameStartTime(); 

  //draw stars 
  for(char i = 0; i < maxStars; i++){ 
   stars[i]->draw(0); 
  }  

  //draw gameobjects 
  p.draw(0);   

  //draw player gunfire 
  for(char i = 0; i < maxPlayerFire; i++){ 
    if(playerFires[i] != NULL){
      playerFires[i]->draw(0);
    }
  }  

  //draw aliens 
   for(char i = 0; i < maxAliens; i++){ 
    if(aliens[i] != NULL){
      aliens[i]->draw(aliens[i]->state);
    }
  }   

  
  //draw onto led matrix 
  drawLEDMatrix(&dm); 


  //game logic 

  //handle input 
  if(controller.input != 0){ 

    bool bits[8]; 
    charToBinArray(controller.input,bits);  

    bool collidingWalls[8]; 
    charToBinArray(p.didItColideWithWall(), collidingWalls);

    if(bits[6] == true){ // go up unless collision with upper wall
      if(!collidingWalls[6]){
        p.translate(0,1); 
      }
    } 

    if(bits[4] == true){ // go down unless collision with lower wall
      if(!collidingWalls[4]){
        p.translate(0,-1);
      }
    }  

    if(bits[3] == true){ //shoot button
      for(char i = 0; i < maxPlayerFire; i++){ 
        if(playerFires[i] == NULL){ 
          playerFires[i] = (PlayerFire *)malloc(sizeof(PlayerFire));
          playerFires[i]->initPlayerFire(p.x + 5,p.y); 
          break;
        }
      }
    }

    controller.inputProcessed();
  } 

  //rest of game logic  

  //fire to alien collison 
  for(char f = 0; f < maxPlayerFire; f++){
    if(playerFires[f] != NULL){
      for(char a = 0; a < maxAliens; a++){
        if(aliens[a]!=NULL){
          if(aliens[a]->didItColideWithGO(playerFires[f])){
            playerFires[f]->destroyGameObject(); 
            playerFires[f] = NULL; 
            aliens[a]->state =1; 
          }
        }
      }
    }
  } 

  //spawn an alien randomly 
  char ranAlienNumber = (char)random(0,10);  
  if(ranAlienNumber > 8 ){
     for(char i = 0; i < maxAliens; i++){ 
        if(aliens[i] == NULL){ 
          aliens[i] = (Alien *)malloc(sizeof(Alien)); 
          float  rany = (float)random(0,32);
          aliens[i]->initAlien(70, rany, (char) random(1,8)); 
          break;
        }
      }
  } 



//translate or destroy player fire
  for(char i = 0; i < maxPlayerFire; i++){
    if(playerFires[i] != NULL){ 
      if(playerFires[i]->x > 70){
        playerFires[i]->destroyGameObject(); 
        playerFires[i] = NULL;
      }
      else{
        playerFires[i]->translate(5,0); 
      }

    }  
  }

//translate or destory alien and update state if needed
    for(char i = 0; i < maxAliens; i++){
    if(aliens[i] != NULL){ 
      if(aliens[i]->state > 5 || aliens[i]->x < -10){
        aliens[i]->destroyGameObject(); 
        aliens[i] = NULL;
      }
      else{
        aliens[i]->translate(-3,0); 
        if(aliens[i]->state > 0){
          aliens[i]->state++; 
        } 
      }

    }
  }  

  //move stars 
  for(char i = 0; i < maxStars; i++){
    stars[i]->translate(-1,0); 
    if(stars[i]-> x < -10){
      stars[i]->x = 68; 
      stars[i]->y = random(0,32);
    }
  }








  fc.waitTillNextFrame(); 
  //clear sreen for next frame 
  dm.clearDataMatrix(); 
  clearScreen(); 

}
