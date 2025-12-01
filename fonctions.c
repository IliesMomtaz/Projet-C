
int is free(int x, int y, int l, int h) { //implementation de is_free (à mettre où??)

    for (int i = 0; i<h; i ++) {//boucle hauteur h
        for (int j = 0; j < l; j++){ //boucle largeur l

            if (grid[y+i][x+j] != 0) return 0 //voir implementation tableau;
        }
    }

return 1;

}


char key = key_pressed(VEHICULE* v);

    key_pressed(VEHICULE* v) {
    if key = 'z' {
        v.direction = 'N';
    }

    if key = 'd' {
        v.direction = 'E';
    }
    if key = 'q' {
        v.direction = 'O';
    }
    if key = 's' {
        v.direction = 'S';
    }
}