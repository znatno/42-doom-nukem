#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "doom_nukem.h"
#include "math.h"
#include <unistd.h>


//void	apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend)
//{
//    SDL_Rect pos;
//
//    pos.x = x;
//    pos.y = y;
//    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
//    SDL_RenderCopy(rend, tex, NULL, &pos);
//}

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define POINTS_COUNT 2

//static SDL_Point points[POINTS_COUNT] = {
//        {100, 100},
//        {100, 300},
////        {140, 240},
////        {120, 200}
//};

/* Define window size */
#define W 608
#define H 480
/* Define various vision related constants */
#define EyeHeight  6    // Camera height from floor when standing
#define DuckHeight 2.5  // And when crouching
#define HeadMargin 1    // How much room there is above camera before the head hits the ceiling
#define KneeHeight 2    // How tall obstacles the player can simply walk over without jumping
#define hfov (0.73f*H)  // Affects the horizontal field of vision
#define vfov (.2f*H)    // Affects the vertical field of vision


/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */
static struct sector
{
    float floor, ceil;
    struct xy { float x,y; } *vertex; // Each vertex has an x and y coordinate
    signed char *neighbors;           // Each edge may have a corresponding neighboring sector
    unsigned npoints;                 // How many vertexes there are
} *sectors = NULL;

static unsigned NumSectors = 0;

static struct player
{
    struct xyz { float x,y,z; } where,      // Current position
            velocity;   // Current motion vector
    float angle, anglesin, anglecos, yaw;
    // Looking towards (and sin() and cos() thereof)
    // A yaw is a counterclockwise rotation of
    // $ \alpha$ about the $ z$-axis.
    unsigned sector;                        // Which sector the player is currently in
} player;



void print_player(void) {
    printf("---------player--------------------------\n");
    printf("x = %f, y = %f, z = %f\n", player.where.x,player.where.y,player.where.z);
    printf("sector = %u\n", player.sector);
    printf("-----------------------------------------\n");
}

void print_sector(void) {
    int i = NumSectors;
    while (i-- > 0) {
        printf("---------sector # %d-----------------------------\n",i);
        printf("floor = %f, ceil = %f\n", sectors[i].floor, sectors[i].ceil);
        printf("vertex.x = %f vertex.y = %f\n",sectors[i].vertex[0].x, sectors[i].vertex->y);
        printf("neighbors = %s\n", sectors[i].neighbors);
        printf("-------------------------------------------------\n");
    }
}

static void LoadData()
{
    FILE* fp = fopen("../res/map-clear.txt", "rt");
    if(!fp) { perror("../res/map-clear.txt"); exit(1); }
    char Buf[256], word[256], *ptr;
    struct xy *vert = NULL, v;
    int n, m, NumVertices = 0; n, m,
    while(fgets(Buf, sizeof Buf, fp))
        switch(sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
        {
            case 'v': // vertex
                for(sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1; )
                { vert = realloc(vert, ++NumVertices * sizeof(*vert)); vert[NumVertices-1] = v; }
                break;
            case 's': // sector
                sectors = realloc(sectors, ++NumSectors * sizeof(*sectors));
                struct sector* sect = &sectors[NumSectors-1];
                int* num = NULL;
                sscanf(ptr += n, "%f%f%n", &sect->floor,&sect->ceil, &n);
                for(m=0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; )
                { num = realloc(num, ++m * sizeof(*num)); num[m-1] = word[0]=='x' ? -1 : atoi(word); }
                sect->npoints   = m /= 2;
                sect->neighbors = malloc( (m  ) * sizeof(*sect->neighbors) );
                sect->vertex    = malloc( (m+1) * sizeof(*sect->vertex)    );
                for(n=0; n<m; ++n) sect->neighbors[n] = num[m + n];
                for(n=0; n<m; ++n) sect->vertex[n+1]  = vert[num[n]]; // TODO: Range checking
                sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
                free(num);
                break;
            case 'p':; // player
                float angle;
                sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle,&n);
                player = (struct player) { {v.x, v.y, 0}, {0,0,0}, angle,0,0,0, n }; // TODO: Range checking
                player.where.z = sectors[player.sector].floor + EyeHeight;
        }
    fclose(fp);
    free(vert);
}

/*Free sectors and other stuff*/


//static void UnloadData()
//{
//    for(unsigned a=0; a<NumSectors; ++a) free(sectors[a].vertex);
//    for(unsigned a=0; a<NumSectors; ++a) free(sectors[a].neighbors);
//    free(sectors);
//    sectors    = NULL;
//    NumSectors = 0;
//}


int main(void)
{
    LoadData();

//    printf("vertex.x = %f vertex.y = %f\n",sectors[0].vertex->x, sectors[0].vertex->y);
//    print_player();
//    print_sector();
    return (0);
}
