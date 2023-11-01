/*================================================================================================================================
  These functions are for generating indexes which represent all ways of choosing k elements from an array of n elements.
  For example, for all ways to choose 3 elements from an array of 6 elements, use the indexes from print_all_indexes(6, 3).
  1 <= numberOfindexes, indexmax < 2^32
*/
uint32_t* initindexes(uint32_t numberOfindexes) {
  if (numberOfindexes == 0) return NULL;
  uint32_t* output = malloc(numberOfindexes*sizeof(uint32_t));  
  if (output == NULL) {
    fprintf(stderr, "Malloc Failed in initindexes(%u).\n", numberOfindexes);
  }
  uint32_t i;
  for(i=0; i < numberOfindexes; i++) {
    output[i] = i;
  }
  return output;
}

uint32_t* get_next_indexes(uint32_t numberOfindexes, uint32_t indexmax, uint32_t* indexes) {
  uint32_t i, arraypos = 0;
  if (numberOfindexes <= 0) return NULL;
  for (arraypos = 0; arraypos < numberOfindexes; arraypos++) {
    if (arraypos+1 < numberOfindexes) {
      if (indexes[arraypos] + 1 < indexes[arraypos+1]) {
        indexes[arraypos]++;
        for(i=0; i < arraypos; i++) {
          indexes[i] = i;
        }
        return indexes;
      }
    } else {
      if (indexes[arraypos] < indexmax) {
        indexes[arraypos]++;
        for(i=0; i < arraypos; i++) {
          indexes[i] = i;
        }
        return indexes;
      }
      free(indexes);
      return NULL;
    }
  }
  return NULL;
}

void print_indexes(uint32_t numberOfindexes, uint32_t*indexes) {
  uint32_t i;
  if (indexes == NULL) {
    printf("NULL\n");
    return;
  }
  for(i=numberOfindexes-1; ; i--) {
    printf("%u ", indexes[i]);
    if (i == 0) break;
  }
  printf("\n");
}

void print_all_indexes(uint32_t n, uint32_t k) {
  uint32_t*indexes = initindexes(k);
  uint64_t ixcount = 0;
  while (indexes != NULL) {
    print_indexes(k, indexes);
    ixcount++;
    indexes = get_next_indexes(k, n-1, indexes);
  }
  printf("There are %lu combinations for n=%u k=%u.\n", ixcount, n, k);
}

/*================================================================================================================================*/

