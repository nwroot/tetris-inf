#include "tetris.h"

struct tetris_piece standard_pieces[7] = {
{
    .piece_def = {
        { 0, 0, 0, 0 },
        { 1, 1, 1, 1 },
        { 0, 0, 0, 0,},
        { 0, 0, 0, 0,}
    },
    .use_custom_rot = false
},
{
    .piece_def = {
        { 1, 0, 0 ,0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    .use_custom_rot = true,
    .rot_center_x = 1,
    .rot_center_y = 1
},
{
    .piece_def = {
        { 0, 0, 1 ,0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    .use_custom_rot = true,
    .rot_center_x = 1,
    .rot_center_y = 1
},

{
    .piece_def = {
        { 1, 1, 0 ,0 },
        { 1, 1, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    .use_custom_rot = true,
    .rot_center_x = NO_ROT,
    .rot_center_y = NO_ROT
},
{
    .piece_def = {
        { 0, 1, 1 ,0 },
        { 1, 1, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    .use_custom_rot = true,
    .rot_center_x = 1,
    .rot_center_y = 1
},
{
    .piece_def = {
        { 0, 1, 0 ,0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    .use_custom_rot = true,
    .rot_center_x = 1,
    .rot_center_y = 1
},
{
    .piece_def = {
        { 1, 1, 0 ,0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    .use_custom_rot = true,
    .rot_center_x = 1,
    .rot_center_y = 1
}
};

void rotar(int *mat, int n){ 
 int helper[n][n]; 
 for(int i = 0; i<n; ++i){ 
  for(int j = 0; j<n; ++j){ 
   helper[i][j] = mat[i * n + j]; 
  } 
 } 
 for(int i = 0; i<n; ++i){ 
  for(int j = n-1; j>=0; --j){ 
   mat[i * n + j] = helper[n-1-j][i]; 
  } 
 } 
} 
 
 
void do_rot_matrix(struct tetris_piece *piece) {
    if(piece->use_custom_rot) {
        if(piece->rot_center_x == 1 && piece->rot_center_y == 1) {
            int mat[3][3];
            
            for(int i = 0; i < 3; i++) memcpy(mat[i], piece->piece_def[i], sizeof(uint32_t) * 3);
            rotar((int *)mat, 3);
            
            for(int i = 0; i < 3; i++) memcpy(piece->piece_def[i], mat[i], sizeof(uint32_t) * 3);
        }
    }
    /*
    
    if(!piece->use_custom_rot) {
        printf("Unsupported rotation");
    } else {
        mat[piece->rot_center_y][piece->rot_center_x] = piece->piece_def[piece->rot_center_y][piece->rot_center_x];
        
        if(piece->rot_center_x == 1 && piece->rot_center_y == 1) {
            mat[0][0] = piece->piece_def[0][1];
            mat[0][1] = piece->piece_def[0][2];
            mat[0][2] = piece->piece_def[1][2];
            mat[1][2] = piece->piece_def[2][2];
            mat[2][2] = piece->piece_def[2][1];
            mat[2][1] = piece->piece_def[2][0];
            mat[2][0] = piece->piece_def[1][0];
            mat[1][0] = piece->piece_def[0][0];
            
            memcpy(piece->piece_def, mat, sizeof(int) * 4 * 4);
        } else {
            
        }
    }
    */
}
        
        
