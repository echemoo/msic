class RTNode;
class Entry;

int existsInList(int n, vector<int> &List);
void eraseElement(int n, vector<int> &List);
void mergeSets(map<int, int>&, map<int, int>&);

void error(string errmsg, bool _terminate);
float area(int dimension, float* mbr);
float margin(int dimension, float* mbr);
float overlap(int dimension, float* r1, float* r2);
float* overlapRect(int dimension, float *r1, float *r2);
float* overlapRect_dynamic(int dimension, float* r1, float* r2, bool* func);    // by Greg
float objectDIST(float* p1, float* p2);
float MINMAXDIST(float* Point, float* bounces);
float MINDIST(float* Point, float* bounces);
float MAXDIST(float* p, float* bounces, int dim);
float MbrMINDIST(float* _m1, float* _m2, int _dim);
float MbrMAXDIST(float* _m1, float* _m2, int _dim);
float mindist(float* p, float* bounces, int dimension, float* bound);   // by Greg
float mindist_dynamic(float* p, float* bounces, int dimension, float* bound, bool* func);   // by Greg

