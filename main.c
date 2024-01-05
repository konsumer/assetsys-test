#define STRPOOL_IMPLEMENTATION
#define ASSETSYS_IMPLEMENTATION
#include "assetsys.h"

#include <stdio.h>

void list_assets(assetsys_t* assetsys, char const* path, int indent) {
  // Print folder names and recursively list assets
  for (int i = 0; i < assetsys_subdir_count(assetsys, path); ++i) {
    char const* subdir_name = assetsys_subdir_name(assetsys, path, i);
    for (int j = 0; j < indent; ++j){
      printf("  ");
    }
    printf("%s/\n", subdir_name);

    char const* subdir_path = assetsys_subdir_path(assetsys, path, i);
    list_assets(assetsys, subdir_path, indent + 1);
  }

  // Print file names
  for (int i = 0; i < assetsys_file_count(assetsys, path); ++i) {
    char const* file_name = assetsys_file_name(assetsys, path, i);
    for (int j = 0; j < indent; ++j){
      printf("  ");
    }
    printf("%s\n", file_name);
  }
}

int main(int argc, char* argv[]) {
  assetsys_t* assetsys = assetsys_create(0);
  
  // test zip-mounting in root
  assetsys_mount(assetsys, "test.zip", "/");
  
  // test directory-mounting in subdir
  assetsys_mount(assetsys, "./build", "/build");

  // for soem reason I have to list both
  list_assets(assetsys, "/", 0);
  list_assets(assetsys, "/build", 0);

  assetsys_file_t file;
  assetsys_file(assetsys, "/readme.txt", &file);
  int size = assetsys_file_size(assetsys, file);
  char* content = (char*)malloc(size + 1);
  
  // assetsys_t* sys, assetsys_file_t file, int* size, void* buffer, int capacity
  int outSize = 0;
  assetsys_file_load(assetsys, file, &outSize, content, size + 1);
  if (outSize == 0) {
    printf("could not find readme.txt from test.zip.\n");
  } else {
    content[size] = '\0';
    printf("opened readme.txt with size of %d\n\n%s\n", outSize, content);
  }
  free(content);

  assetsys_destroy(assetsys);

  return 0;
}