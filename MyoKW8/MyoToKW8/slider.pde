class Slider{

int x0Bg, y0Bg, x1Bg, y1Bg; // coordinate bg background
int x0slider, y0slider, x1slider, y1slider; // coordinate bg background
int widthBg, heightBg; 
int heightSlider, bar; // bar

Slider(int posX, int posY, int Width, int Height){
 
  x0Bg = posX;
  y0Bg = posY;
  widthBg = Width;
  heightBg = Height;
  
  x1Bg = widthBg; // bottom corner backgroung 100
  y1Bg = heightBg; // bottom corner backgroung 100
 
}


void display(){
  noStroke();
  fill(#245993); // colour background
  rect(x0Bg, y0Bg, x1Bg, y1Bg); // background
  fill(100); // colour slider
  rect(x0slider, y0slider, x1slider, y1slider); // slider
  }


void run(){
  update();
  display();
  }

void update(){
  x0slider = x0Bg;
  y0slider = y0Bg;
  x1slider = x1Bg;
  y1slider = y1Bg-bar;
  }

}
