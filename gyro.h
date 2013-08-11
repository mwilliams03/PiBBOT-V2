 int file;

void readBlock(uint8_t command, uint8_t size, uint8_t * data);
void selectDevice(int file, int addr);
void writeAccReg(uint8_t reg, uint8_t value);
void writeMagReg(uint8_t reg, uint8_t value);
void writeGyrReg(uint8_t reg, uint8_t value);
void readMAG(int * data);
void readACC(int * data);
void readGYR(int * data);


