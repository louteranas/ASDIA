#include "swOut.h"
#include "mem.h"


/*Smith-Waterman*/
void printAlis(struct matrix *mat, char *s1, char *s2){
  char c1[mat->w+mat->h+1];
  char c2[mat->w+mat->h+1];
  char * chaine1 = c1 + mat->w+mat->h;
  char * chaine2 = c2 + mat->w+mat->h;
  *chaine1 = '\0';
  *chaine2 = '\0';
  unsigned int index[2];
  maxIndex(mat, index);
  struct cell current_cell = mat->cells[index[0]*mat->w+index[1]];
  while(current_cell.score != 0){
    if((current_cell.prevs & 1) == 1){
      if(s1[index[1] - 1] == s2[index[0] - 1]){
        *(--chaine1) = s1[index[1] - 1];
        *(--chaine2) = s2[index[0] - 1];
      }
      else{
        *(--chaine1) = tolower(s1[index[1] - 1]);
        *(--chaine2) = tolower(s2[index[0] - 1]);
      }
      index[0]--;
      index[1]--;
      current_cell = mat->cells[index[0]*mat->w+index[1]];
    }
    else if((current_cell.prevs & 2) == 2){
        *(--chaine1) = tolower(s1[index[1] - 1]);
        *(--chaine2) = '-';
      index[1]--;
      current_cell = mat->cells[index[0]*mat->w+index[1]];
    }
    else{
      *(--chaine1) = '-';
      *(--chaine2) = tolower(s2[index[0] - 1]);
      index[0]--;
      current_cell = mat->cells[index[0]*mat->w+index[1]];
    }

  }
  printf("chaine 1 : %s\nchaine 2 : %s\n\n", chaine1, chaine2);
}


/*Altschul & Erickson*/
void printAlisAlt(struct matrix *mat_d, struct matrix *mat_v, struct matrix *mat_h, char *s1, char *s2){
  uint8_t current_mat = 1;
  char c1[mat_d->w+mat_d->h+1];
  char c2[mat_d->w+mat_d->h+1];
  char * chaine1 = c1 + mat_d->w+mat_d->h;
  char * chaine2 = c2 + mat_d->w+mat_d->h;
  *chaine1 = '\0';
  *chaine2 = '\0';
  unsigned int index[2];
  maxIndex(mat_d, index);
  struct cell current_cell = mat_d->cells[index[0]*mat_d->w+index[1]];
  while(current_cell.score != 0){
    if(s1[index[1] - 1] == s2[index[0] - 1]){
      *(--chaine1) = s1[index[1] - 1];
      *(--chaine2) = s2[index[0] - 1];
    } else {
      *(--chaine1) = tolower(s1[index[1] - 1]);
      *(--chaine2) = tolower(s2[index[0] - 1]);
    }

    if ((current_mat & 1) == 1) {
      index[0]--;
      index[1]--;
    } else if ((current_mat & 2) == 2) {
        index[0]--;
    } else if ((current_mat & 4) == 4){
          index[1]--;
    } else {
      fprintf(stderr, "mauvaise matrice");
    }

    if((current_cell.prevs & 1) == 1){
      current_mat = 1;
    } else if((current_cell.prevs & 2) == 2){
      current_mat = 2;
    } else if((current_cell.prevs & 4) == 4){
      current_mat = 4;
    }

    if ((current_mat & 1) ==1){
      current_cell = mat_d->cells[index[0]*mat_d->w+index[1]];
    } else if ((current_mat & 2) == 2){
        current_cell = mat_v->cells[index[0]*mat_d->w+index[1]];
    } else if ((current_mat & 4) == 4) {
        current_cell = mat_h->cells[index[0]*mat_d->w+index[1]];
    } else {
      fprintf(stderr, "mauvaise matrice");
    }


  }
  printf("chaine 1 : %s\nchaine 2 : %s\n\n", chaine1, chaine2);
}


void maxIndex(struct matrix *mat, unsigned int* index){
  // finding coordinates of the highest score in the given matrix
  int max = 0;
  for (unsigned int i=0; i<mat->h; i++){
    for (unsigned int j=0; j<mat->w; j++){
      if(mat->cells[i*mat->w+j].score > max){
        max = mat->cells[i*mat->w+j].score;
        index[0] = i;
        index[1] = j;
      }
    }
  }
  printf("le max num %d est: (%d,%d)\n", max, index[0],index[1]);
}


// La portion de code suivante était supposée permettre d'obtenit plusieurs chemins optimaux.
// Elle n'a pas été aboutie faute de temps

// unsigned int **maxIndex(struct matrix *mat){
//   int max = 0;
//   unsigned int maxNumber = 0;
//   for(unsigned int i = 0; i < mat->h; i++){
//     for(unsigned int j = 0; j < mat->w; j++){
//       if(mat->cells[i*mat->w+j].score > max){
//         maxNumber = 1;
//         max = mat->cells[i*mat->w+j].score;
//       }
//       else if(mat->cells[i*mat->w+j].score == max){
//         maxNumber++;
//       }
//     }
//   }
//   unsigned int maxIndex = 0;
//   unsigned int **index = malloc((maxNumber+1)*sizeof(unsigned int *));
//   for(unsigned int i = 0; i <(maxNumber+1); i++){
//     index[i] = malloc(2*sizeof(unsigned int));
//   }
//   for(unsigned int i = 0; i < mat->h; i++){
//     for(unsigned int j = 0; j < mat->w; j++){
//       if(mat->cells[i*mat->w+j].score == max){
//         index[maxIndex][0] = i;
//         index[maxIndex][1] = j;
//         //printf("le max num %d est: (%d,%d)\n", maxIndex, i,j);
//         maxIndex++;
//       }
//     }
//   }
//   index[maxNumber] = NULL;
//   return index;
// }
