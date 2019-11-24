float[] coords;
String[] data;
int i = 0;
int w =700;
int h =700;
void setup() {
  fullScreen();
  //size(7000, 7000);
  data = loadStrings("data.csv");
  //noLoop();
}

void draw() {
  if (i > data.length-1)
    i =0;
  background(255);
  fill(0);
  translate(350,350);
  coords = float(split(data[i], ','));
  ellipse(coords[0], coords[1], 3, 3);
  ellipse(coords[2],coords[3],3,3);
  i++;
}
