/*
peter keres
sep 21 2019


this will hold an example file that will get run by the exevpe systme call
this is a stand in for batch files, should work the same ether way

 could have other example files, maybe put a forloop in them so they take awahile to run

 NOTE: make sure you compile this file before you try to call it with the execv function
*/




int main (int argc, char *args[]){

  for (int i = 0; i < 1000; i++) {

    if ( (i % 50) == 0 ){
      printf("%d\n", i);
    }

  }

  return 0;
}
