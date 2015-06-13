PImage integralogo;
PImage cons;

void logoSetup(){
   integralogo = loadImage("blue-integra.png"); //
  cons = loadImage("cons.png"); //

  cons.resize(int(cons.width/5.5),int(cons.height/5.5));
  integralogo.resize(int(integralogo.width/3.5),int(integralogo.height/3.5));


  for (int i = 0;i<cons.width;i++) {// pour image d'origine allant de 0 à la fin de la fenetre ( abscisse)
    for (int j = 0; j<cons.height;j++) {//......................................................(ordonnée)
      //int r =(int) red(cons.get(i, j)); //definit les sous pixels rouges des pixels sur la longueur de l'image d'origine
      int r =(int)blue(cons.get(i, j)); //.......................bleu...................................................
      int b =(int)blue(cons.get(i, j)); //.......................bleu...................................................
      int g =(int)green(cons.get(i, j)); //......................vert..................................................
      cons.set(i, j, color(110-r, 110-g, 160-g));
    }
  }
  
}

void logoRun(){
  
   image(integralogo, width/2+width/110, height-integralogo.height); // display integra logo
   image(cons, width-cons.width, height-integralogo.height); // display integra logo

}
