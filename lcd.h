
void lcdClear(void); // Clear lcd
void lcdIntialize(void); // Intialize lcd
void lcdData(char dat); // Send data's
void lcdString(char *str); // Send string
void lcdCommand(char com); //send commands
void delayMs(unsigned int x); // Delay in microseconds max@71MS
void lcdCursorPosition(unsigned int row, unsigned int pos); 
void lcdStart(void);
void serialInitialize(void);