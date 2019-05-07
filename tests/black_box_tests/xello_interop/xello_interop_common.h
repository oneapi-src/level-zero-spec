void matmat_host(int n, int m, int p, float *a, float *b, float* c);

int xeInit();
int xeInitProgram();
int xeUseCLProgram();
int xeInitBuffers();
int xeUseCLBuffers();
int xeUseCLCmdQueue();
int xeInitCmdQueue();
int xeCompute();
void xeCleanup();

int clInit();
int clInitProgram();
int clInitBuffers();
int clCompute();
void clCleanup();

void initArrays();
int validateArrays(float *c);
int validateResults(bool aubMode);

