float xmag, ymag = 0;
float newXmag, newYmag = 0; 

void createCube(float scaleX, float scaleY, float scaleZ) {

  pushMatrix(); 
  noStroke();
  
  translate(100, height - 200, -30); 
  
  newXmag = mouseX/float(width) * TWO_PI;
  newYmag = mouseY/float(height) * TWO_PI;
  
  float diff = xmag-newXmag;
  if (abs(diff) >  0.01) { 
    xmag -= diff/4.0; 
  }
  
  diff = ymag-newYmag;
  if (abs(diff) >  0.01) { 
    ymag -= diff/4.0; 
  }

  //rotateX(-ymag); 
  //rotateY(-xmag); 

  scale(scaleX, scaleY, scaleZ);
  beginShape(QUADS);
  
  
  //stroke(255);
  fill(0, 255, 255); vertex(-1, 1, 1);
  fill(255, 255, 255); vertex( 1, 1, 1);
  fill(255, 0, 255); vertex( 1, -1, 1);
  fill(0, 0, 255); vertex(-1, -1, 1);

  fill(255, 255, 255); vertex( 1, 1, 1);
  fill(255, 255, 0); vertex( 1, 1, -1);
  fill(255, 0, 0); vertex( 1, -1, -1);
  fill(255, 0, 255); vertex( 1, -1, 1);

  fill(255, 255, 0); vertex( 1, 1, -1);
  fill(0, 255, 0); vertex(-1, 1, -1);
  fill(0, 0, 0); vertex(-1, -1, -1);
  fill(255, 0, 0); vertex( 1, -1, -1);

  fill(0, 255, 0); vertex(-1, 1, -1);
  fill(0, 255, 255); vertex(-1, 1, 1);
  fill(0, 0, 255); vertex(-1, -1, 1);
  fill(0, 0, 0); vertex(-1, -1, -1);

  fill(0, 255, 0); vertex(-1, 1, -1);
  fill(255, 255, 0); vertex( 1, 1, -1);
  fill(255, 255, 255); vertex( 1, 1, 1);
  fill(0, 255, 255); vertex(-1, 1, 1);

  fill(0, 0, 0);  vertex(-1, -1, -1);
  fill(255, 0, 0);  vertex( 1, -1, -1);
  fill(255, 0, 255);  vertex( 1, -1, 1);
  fill(0, 0, 255);  vertex(-1, -1, 1);

  endShape();

  popMatrix();
}
