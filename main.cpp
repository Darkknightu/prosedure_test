
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <iostream>
#include <ctime>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <intrin.h>
#include <any>
#include <boost/dynamic_bitset.hpp>

#define PMAXSIZE_EPS 1e-10

using namespace std;

class Tracer {
    timeval bt;

    timeval et;

    long dt;

public:
    void startTime() {
        gettimeofday(&bt, nullptr);
    }

    long getRunTime() {
        gettimeofday(&et, nullptr);
        dt = (et.tv_sec - bt.tv_sec) * 1000000 + et.tv_usec - bt.tv_usec;
        bt = et;
        return dt;
    }
};



using namespace std;


void testsimd(){
    int cntbuf=4096;
    float pbuf[4096];
    srand( (unsigned)time( NULL ) );
    for (int j = 0; j <cntbuf ; ++j) {
        pbuf[j] = (float)(rand() & 0x3f);
    }
    float s = 0;    // 求和变量.
    size_t i;
    size_t nBlockWidth = 8;    // 块宽. AVX寄存器能一次处理8个float.
    size_t cntBlock = cntbuf / nBlockWidth;    // 块数.
    size_t cntRem = cntbuf % nBlockWidth;    // 剩余数量.
    __m256 yfsLoad;    // 加载.
    const float* p = pbuf;    // AVX批量处理时所用的指针.
    const float* q;    // 将AVX变量上的多个数值合并时所用指针.


    cout<<"float test"<<endl;
    // AVX批量处理.
    Tracer tracer;
    __m256 yfsSum = _mm256_setzero_ps();    // 求和变量。[AVX] 赋初值0
    tracer.startTime();
    for(i=0; i<cntBlock; ++i)
    {
        yfsLoad = _mm256_load_ps(p);    // [AVX] 加载
        yfsSum = _mm256_add_ps(yfsSum, yfsLoad);    // [AVX] 单精浮点紧缩加法
        p += nBlockWidth;
    }
    // 合并.
    q = (const float*)&yfsSum;
    s = q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] + q[7];
    cout<<"time on float avx add"<<tracer.getRunTime() << endl;

    tracer.startTime();
    s=0;
    for(i=0; i<cntbuf; ++i)
    {
        s+=pbuf[i];
    }
    cout<<"time on float add"<<tracer.getRunTime() << endl;

    __m256 yfsProduct=_mm256_set_ps(1,1,1,1,1,1,1,1);
    tracer.startTime();
    for(i=0; i<cntBlock; ++i)
    {
        yfsLoad = _mm256_load_ps(p);    // [AVX] 加载
        yfsProduct = _mm256_mul_ps(yfsProduct, yfsLoad);    // [AVX] 单精浮点紧缩加法
        p += nBlockWidth;
    }
    // 合并.
    q = (const float*)&yfsProduct;
    s = q[0] * q[1] * q[2] * q[3] * q[4] * q[5] * q[6] * q[7];
    cout<<"time on float avx multiply"<<tracer.getRunTime() << endl;

    tracer.startTime();
    s=1;
    for(i=0; i<cntbuf; ++i)
    {
        s*=pbuf[i];
    }
    cout<<"time on float multiply"<<tracer.getRunTime() << endl;


    __m256 yfsSub = _mm256_setzero_ps();    // 求和变量。[AVX] 赋初值0
    tracer.startTime();
    for(i=0; i<cntBlock/2; ++i)
    {
        yfsLoad = _mm256_load_ps(p);    // [AVX] 加载
        yfsSub = _mm256_sub_ps(yfsSum, yfsLoad);
        p += 2*nBlockWidth;
    }
    // 合并.
    q = (const float*)&yfsSum;
    s = q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] + q[7];
    cout<<"time on float avx sub"<<tracer.getRunTime() << endl;

    tracer.startTime();
    s=0;
    for(i=0; i<cntbuf/2*nBlockWidth; ++i)
    {
        for (int j = 0; j <8 ; ++j) {
            s+=pbuf[j]-pbuf[j+8];
        }
    }
    cout<<"time on float sub"<<tracer.getRunTime() << endl;

    yfsProduct=_mm256_set_ps(1,1,1,1,1,1,1,1);
    tracer.startTime();
    for(i=0; i<cntBlock; ++i)
    {
        yfsLoad = _mm256_load_ps(p);    // [AVX] 加载
        yfsProduct = _mm256_div_ps(yfsProduct, yfsLoad);    // [AVX] 单精浮点紧缩加法
        p += nBlockWidth;
    }
    // 合并.
    q = (const float*)&yfsProduct;
    s = q[0] * q[1] * q[2] * q[3] * q[4] * q[5] * q[6] * q[7];
    cout<<"time on float avx div"<<tracer.getRunTime() << endl;

    tracer.startTime();
    s=1;
    for(i=0; i<cntbuf/2*nBlockWidth; ++i)
    {
        for (int j = 0; j <8 ; ++j) {
            s+=pbuf[j]/pbuf[j+8];
        }
    }
    cout<<"time on float div"<<tracer.getRunTime() << endl;

    // 处理剩下的.
}

void testfilewriter(FILE** fl){
    char* test="test";
    for (int i = 0; i < 1024; ++i) {
        fwrite(test, sizeof(char),strlen(test),fl[0]);
    }
}

void fileOutput(int num,char* name){
    fstream s(name,s.binary | s.trunc | s.in | s.out);
    for (int i = 0; i < num ; ++i) {
        s.write((char *)&i, sizeof(i)); ;
    }

}

void streamInputTest(int num,char* name){
    ifstream s(name,s.binary | s.in );
    int j;
    time_t strart=time(nullptr);
    for (int i = 0; i < num; ++i) {
        s.read((char *)&j, sizeof(j));;
    }
    time_t end=time(nullptr);
    cout<<end-strart<<"seconds for input as stream";
}

void fileInputTest(int num, char* s){
    FILE* file;
    file=fopen(s,"rb+");
    int j=1;
    int* pj=&j;
    time_t strart=time(nullptr);
    for (int i = 0; i < num; ++i) {
        fread(pj, sizeof(int),1,file);
    }
    time_t end=time(nullptr);
    cout<<end-strart<<"seconds for input as file";
}

void blockInputTest(int num, char* s){
    FILE* file;
    file=fopen(s,"rb+");
    int j=1;
    int* pj=&j;
    int* block=new int[1024];
    time_t start=time(nullptr);
    for (int i = 0; i < num/1024; ++i) {
        fread(block, sizeof(int),1024,file);
        for (int k = 0; k <1024 ; ++k) {
            j=block[k];
        }
    }
    time_t end=time(nullptr);
    cout<<end-start<<"seconds for input as file";
}


void anyInputTest(int num, char* s){
    FILE* file;
    file=fopen(s,"rb+");
    any j=1;
    int* block=new int[1024];
    time_t start=time(nullptr);
    for (int i = 0; i < num/1024; ++i) {
        fread(block, sizeof(int),1024,file);
        for (int k = 0; k <1024 ; ++k) {
            j=block[k];
        }
    }
    time_t end=time(nullptr);
    cout<<end-start<<"seconds for input as any";
}

class  anyTest{
public:
    any value;
    anyTest(int i):value(i){
    }
    any& getre(){
        return value;
    }
    any getva(){
        return value;
    }

};

void classInputTest(int num, char* s){
    FILE* file;
    file=fopen(s,"rb+");
    anyTest j(1);
    int* block=new int[1024];
    time_t start=time(nullptr);
    for (int i = 0; i < num/1024; ++i) {
        fread(block, sizeof(int),1024,file);
        for (int k = 0; k <1024 ; ++k) {
            j.getre()=block[k];
//            j.getva()=block[k];
        }
    }
    time_t end=time(nullptr);
    cout<<end-start<<"seconds for input as class";
}

class Test{
private:
    int test_i;

    char* test_c="test";
public:
    Test(int i):test_i(i){}

    int* getIntP(){
        return &test_i;
    }

    int getInt(){
        return test_i;
    }

};

void testReference(){
    Test t(1024);
    int* pi=t.getIntP();
    cout<<*pi<<endl;
    *pi=1048;
    cout<<*pi<<endl;
    cout<<t.getInt()<<endl;
}

int main() {
//    char* filename="./file0.dat";
//    FILE** fl=(FILE**)malloc(sizeof(FILE*));
//    fl[0]=fopen(filename,"wb+");
//    testfilewriter(fl);
//testReference();
    //fileOutput(1024,"./file.dat");
    blockInputTest(1024,"./file.dat");
return 0;
}