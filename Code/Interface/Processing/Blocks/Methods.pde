/*
 create Cube Class
 */
float xmag, ymag = 0;
float newXmag, newYmag = 0; 

void createCube(float scaleX, float scaleY, float scaleZ) {

  noStroke();

  scale(scaleX, scaleY, scaleZ);
  beginShape(QUADS);

  //stroke(255);
  fill(0, 255, 255); 
  vertex(0, 1, 1);
  fill(255, 255, 255); 
  vertex( 1, 1, 1);
  fill(255, 0, 255); 
  vertex( 1, 0, 1);
  fill(0, 0, 255); 
  vertex(0, 0, 1);

  fill(255, 255, 255); 
  vertex( 1, 1, 1);
  fill(255, 255, 0); 
  vertex( 1, 1, 0);
  fill(255, 0, 0); 
  vertex( 1, 0, 0);
  fill(255, 0, 255); 
  vertex( 1, 0, 1);

  fill(255, 255, 0); 
  vertex( 1, 1, 0);
  fill(0, 255, 0); 
  vertex(0, 1, 0);
  fill(0, 0, 0); 
  vertex(0, 0, 0);
  fill(255, 0, 0); 
  vertex( 1, 0, 0);

  fill(0, 255, 0); 
  vertex(0, 1, 0);
  fill(0, 255, 255); 
  vertex(0, 1, 1);
  fill(0, 0, 255); 
  vertex(0, 0, 1);
  fill(0, 0, 0); 
  vertex(0, 0, 0);

  fill(0, 255, 0); 
  vertex(0, 1, 0);
  fill(255, 255, 0); 
  vertex( 1, 1, 0);
  fill(255, 255, 255); 
  vertex( 1, 1, 1);
  fill(0, 255, 255); 
  vertex(0, 1, 1);

  fill(0, 0, 0);  
  vertex(0, 0, 0);
  fill(255, 0, 0);  
  vertex( 1, 0, 0);
  fill(255, 0, 255);  
  vertex( 1, 0, 1);
  fill(0, 0, 255);  
  vertex(0, 0, 1);

  endShape();

  //popMatrix();
}
