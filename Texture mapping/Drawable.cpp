#include "Drawable.h"
unsigned char* Drawable::ppmRead(char* filename, int* width, int* height) {
    
    FILE* fp=NULL;
    int i, w, h, d;
    unsigned char* image;
    char head[70];		// max line <= 70 in PPM (per spec).
#ifdef WIN32
    fopen_s(&fp, filename, "rb");
#else
    fp = fopen(filename, "rb");
#endif
    if (fp==NULL) {
        perror(filename);
        return NULL;
    }
    
    // Grab first two chars of the file and make sure that it has the
    // correct magic cookie for a raw PPM file.
    fgets(head, 70, fp);
    if (strncmp(head, "P6", 2)) {
        fprintf(stderr, "%s: Not a raw PPM file\n", filename);
        return NULL;
    }
    
    // Grab the three elements in the header (width, height, maxval).
    i = 0;
    while (i < 3) {
        fgets(head, 70, fp);
        if (head[0] == '#')		// skip comments.
            continue;
        if (i == 0){
#ifdef WIN32
            i += sscanf_s(head, "%d %d %d", &w, &h, &d);
#else
            i += sscanf(head, "%d %d %d", &w, &h, &d);
#endif
        }
        else if (i == 1){
#ifdef WIN32
            i += sscanf_s(head, "%d %d", &h, &d);
#else
            i += sscanf(head, "%d %d", &h, &d);
#endif
        }
        else if (i == 2){
#ifdef WIN32
            i += sscanf_s(head, "%d", &d);
#else
            i += sscanf(head, "%d", &d);
#endif
        }
    }
    
    // Grab all the image data in one fell swoop.
    image = (unsigned char*)malloc(sizeof(unsigned char) * w * h * 3);
    fread(image, sizeof(unsigned char), w * h * 3, fp);
    fclose(fp);
    
    *width = w;
    *height = h;
    return image;
    
}
