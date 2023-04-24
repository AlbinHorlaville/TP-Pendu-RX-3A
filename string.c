
/**
 * @return la longueur de la chaine de caractères, c'est à dire le nombre
 * de caractères qu'elle contient. 
 * Exemple: "" -> length = 0
 *          "abc" -> length = 3
 */
int string_length(char *s) {
  int len;
  len = 0;
  for(int i = 0; *(s+i) != '\0'; i++){ // on s'arrete avant le carac de fin de chaine
    len = len + 1;
  } 
  return len;
}  


/**
 * Copie la second chaîne sur la première.
 * @param s1 est la première chaîne
 * @param s2 est la seconde chaîne
 */
void string_copy(char* s1, char* s2) {
   /* (*s1) = (*s2);
    (*s1)++;
    (*s2)++;
  }
  (*s1)='\0';*/
  while ((*s2))*s1++ = *s2++;
  *s1 = '\0';
  
}

/**
 * Concatène les deux chaînes de caractères, ajoutant la seconde à la fin 
 * de la première.
 * @param s1 est la première chaîne
 * @param s2 est la seconde chaîne
 * hello  word
 */
void string_concat(char* s1, char* s2) {
  //s1 = s1 + string_length(s1);
  int i = 0;
  while (s2[i] != '\0') {
    s1[string_length(s1)] = s2 [i];
    i = i + 1;
  }
  s1[string_length(s1) + string_length(s2)] = '\0';
}

/**
 * Compare les deux chaînes de caractères
 * @param s1
 * @param s2
 * @return 0 si les deux chaînes sont identiques.
 *         -1 si la chaîne s1 est lexicographiquement inférieur à la chaîne s2
 *         1 si  la chaîne s1 est lexicographiquement supérieur à la chaîne s2
 */
int string_cmp(char *s1, char* s2) {
  int len_s1 = string_length(s1);
  int len_s2 = string_length(s2);
  int i = 0;

  // on boucle tant que les carac sont les memes
  while (s1[i]!='\0' || s2[i]!='\0'){
    if (s1[i] < s2[i])
      return -1;
    if (s1[i]> s2[i])
      return 1;
    i = i + 1;
  }
  // si on arrive ici c'est que les lettres etaient les memes mais qu'on arrive a une fin de chaine

  if (len_s1<len_s2){
    return -1;
  }
  else if (len_s2<len_s1){
    return 1;
  }

  return 0;
}


/**
 * Cherche le caractère donné en argument, dans la chaîne donné en argument,
 * à partir de la position donné (offset).
 */
int string_index_of(char *dst, int offset, char ch) {
  int i = 0;
  while (dst[offset+i]!=ch && dst[offset+i]!='\0'){
    i++;
  }
  if (dst[offset+i] == ch){
    return i+offset;
  }
  else {
    return -1;
  }
}

/**
 * Copie une sous-chaîne de la chaîne source dans la chaîne destination.
 * La sous-chaîne est défini par l'index du premier caractères (offset) 
 * et sa longueur (length). 
 * Cette sous-chaîne sera copiée dans la chaîne destination à l'index
 * donné par l'argument "doff".
 * @param dst: la chaîne destination
 * @param doff: l'offset dnas la chaîne destination
 * @param src: la chaîne source
 * @param offset: l'offset de la sous-chaîne à copier.
 * @param length: la loongueur de la sous-chaîne à copier.
 */
void string_substring(char* dst, int doff, char *src, int offset, int length) {
  for(int i = 0; i < length; i++){
    dst[i + doff] = src[i + offset];
  }
}
