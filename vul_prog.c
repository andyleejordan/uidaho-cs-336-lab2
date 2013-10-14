/* vul_prog.c */ 

/* This code was provided by the lab's author Wenliang Du, of Syracuse
   University */

#define SECRET1 0x44
#define SECRET2 0x55

int main(int argc, char *argv[])
{
  char user_input[100];
  int *secret;
  int int_input;
  int a, b, c, d; /* other variables, not used here.*/

/* Second malloc statement needed to remedy initial address containing
 * x0C the form feed character. 16 was an arbitrary number, I guessed
 * until the address was free of terminating hex values.
 */
  a = (int *) malloc(16*sizeof(int));

  /* The secret value is stored on the heap */
  secret = (int *) malloc(2*sizeof(int));

  /* getting the secret */
  secret[0] = SECRET1; secret[1] = SECRET2;

  printf("The variable secret's address is 0x%8x (on stack)\n", &secret);
  printf("The variable secret's value is 0x%8x (on heap)\n", secret);
  printf("secret[0]'s address is 0x%8x (on heap)\n", &secret[0]);
  printf("secret[1]'s address is 0x%8x (on heap)\n", &secret[1]);

  /* Note that these scanf's also introduce a buffer overflow
     vulnerability. If a user inputs a string longer than 100 chars,
     user_input will overflow. We will 'fix' that by setting a maximum
     width one less than the size of user_input (to account for the
     trailing null character). Fix is in quotes because a better
     solution would be to replace these functions with fgets; however,
     we feel that is outside the scope of this particular lab. */
  printf("Please enter a decimal integer\n");
  scanf("%d", &int_input);  /* getting an input from user */
  printf("Please enter a string\n");
  scanf("%99s", user_input); /* getting a string from user */

  /* Previous vulnerable place. This is a simple fix: instead of
     allowing a user-alterable format-string, we supply a hard-coded
     format-string consisting of a single %s paramter, and pass our
     user_input string as an argument to printf with which it fills
     the %s */
  printf("%s", user_input);  
  printf("\n");

  /* Verify whether your attack is successful */
  printf("The original secrets: 0x%x -- 0x%x\n", SECRET1, SECRET2);
  printf("The new secrets:      0x%x -- 0x%x\n", secret[0], secret[1]);
  return 0;
}
