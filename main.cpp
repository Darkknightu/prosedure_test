#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <iostream>
#include <ctime>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <x86intrin.h>

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

class BlockReader{
    int rowCount;
    int lengthOffset;
    int size;

public:
    BlockReader():lengthOffset(0){}

    BlockReader(istream is){
        is.read((char*)&rowCount, sizeof(rowCount));
        is.read((char*)&size, sizeof(size));
    }

    void writeTo(ostream os){
        os.write((char *)&rowCount, sizeof(rowCount));
        os.write((char *)size, sizeof(size));
    }

    void read(istream& is){
        is.read((char*)&this->rowCount, sizeof(this->rowCount));
        is.read((char*)&this->size, sizeof(this->size));
    }
};

class ColumnReader{
    string metaData;
    int blockCount;
    vector<BlockReader> blocks;

public:
    ColumnReader(){}

    ColumnReader(const ColumnReader &columnreader){
        metaData=columnreader.metaData;
        blockCount=columnreader.blockCount;
        blocks=columnreader.blocks;
    }
    ColumnReader(int count):blockCount(count){
        //metaData=meta;
    }

    void setBlocks(vector<BlockReader> _blocks){
        this->blocks.assign(_blocks.begin(),_blocks.begin()+_blocks.size());
    }

    int getblockCount(){
        return blockCount;
    }

    void pushBlock(BlockReader block){
        blocks.push_back(block);
    }
};

class HeadReader{
    int offset;
    int rowCount;
    int blockSize;
    int columnCount;
    string metaData;
    vector<ColumnReader> columns;

public:
    HeadReader(){}

    int getRowCount(){
        return rowCount;
    }

    int getColumnCount(){
        return columnCount;
    }
    string getMetaData(){
        return metaData;
    }

    void setColumns(vector<ColumnReader> _columns){
        this->columns.assign(_columns.begin(),_columns.begin()+_columns.size());
    }

    void readHeader(istream& is){
        is.read((char*)&this->offset, sizeof(this->offset));
        is.read((char*)&this->blockSize, sizeof(this->blockSize));
        is.read((char*)&this->rowCount, sizeof(this->rowCount));
        is.read((char*)&this->columnCount, sizeof(this->columnCount));
        getline(is,metaData);
        unique_ptr<vector<ColumnReader>> columns( new vector<ColumnReader>(columnCount));
        for (int i = 0; i <columnCount ; ++i) {
            int blockCount;
            is.read((char*)&blockCount, sizeof(blockCount));
            unique_ptr<vector<BlockReader>> blocks(new vector<BlockReader>(rowCount));
            for (int j = 0; j < blockCount; ++j) {
                unique_ptr<BlockReader> block(new BlockReader);
                block->read(is);
                blocks->push_back(*block);
            }
            unique_ptr<ColumnReader>column (new ColumnReader(blockCount));
            column->setBlocks(*blocks);
            columns->push_back(*column);
        }
        this->setColumns(*columns);
    }
};

void teststream(ostream os){
    ofstream file_out;
    file_out.open("./test.dat", ios_base::out|ios_base::binary);
    int blocksize=8*1024;
    int rowcount=1;
    int collumncount=3;
    string metaData="{\"type\":\"record\",\"name\":\"test\",\"fields\":[{\"name\":\"test_int\",\"type:\"int\"},{\"name\":\"test_int\",\"type:\"int\"},{\"name\":\"test_int\",\"type:\"int\"}]";
    file_out.write((char*)&blocksize, sizeof(blocksize));
    file_out.write((char*)&rowcount, sizeof(rowcount));
    file_out.write((char*)&collumncount, sizeof(collumncount));
    file_out<<metaData<<endl;
    for (int i = 0; i <collumncount ; ++i) {
        int blockcount=1;
        file_out.write((char*)&blockcount, sizeof(blockcount));
        for (int j = 0; j <blockcount ; ++j) {
            int rowcount=1;
            int size=1024*8;
            file_out.write((char*)&rowcount, sizeof(rowcount));
            file_out.write((char*)&size, sizeof(size));
        }

    }
    file_out.seekp((10*1024*1024,ios::beg));
    file_out.close();
    ifstream file_in;
    file_in.open("./test.dat", ios_base::in|ios_base::binary);
    unique_ptr<HeadReader> headreader(new HeadReader());
    headreader->readHeader(file_in);
    file_in.close();
    std::cout << "Hello, World!" << std::endl;
}

void testpoint(FILE* fp){

}


struct ColumnDescriptor{
    string name;
    string type;
    int size;
};

class RecordReader{
    char* record;
public:
    void setRecord(char* _record){
        record=_record;
    }

    char* getRecord(){
        return record;
    }
};

void testrecord(){

    unique_ptr<vector<ColumnDescriptor>> columns( new vector<ColumnDescriptor>());
    ColumnDescriptor long_column=
            {
                    "test_long",
                    "long",
                    sizeof(long long)
            };
    ColumnDescriptor float_column=
            {
                    "test_float",
                    "float",
                    sizeof(float)
            };
    ColumnDescriptor column;
    columns->push_back(long_column);
    columns->push_back(float_column);
    int length=0;
    for (int i = 0; i < columns->size(); ++i) {
        length+=(*columns)[i].size;
    }
    unique_ptr<char> tmp(new char[length]);
//    int offset=0;
//    *(long long *)tmp=0;
//    offset+= sizeof(long long);
//    *(float*)(tmp+offset)=1.28;
//    RecordReader* tmp_record=new RecordReader;
//    tmp_record->setRecord(tmp);
//    char* tmp_r;
//    tmp_r=tmp_record->getRecord();
//    long long tmp_l=*(long long*)tmp_r;
//    float tmp_f=*(float*)(tmp_r+ sizeof(long long));

//    delete(tmp);
}

void testmemory(){
    Tracer tracer;
    char* tmp;
    int t=8*1024*1024;
    int length=2;
    cout<<"times"<<t<<endl;
    for (int j = 0; j <12; ++j) {
        tracer.startTime();
        for (int i = 0; i < t; ++i) {
            tmp=new char[length];
            delete(tmp);
        }

        cout<<"test memory(direct delete)"<<" block size"<<length<<" "<<tracer.getRunTime()<<endl;
        length*=2;
    }
    length=2;
    char **tmptest=new char*[t];
    for (int j = 0; j <12; ++j) {
        tracer.startTime();
        for (int i = 0; i < t; ++i) {
            tmptest[i]=new char[length];
        }
        for (int i = 0; i < t; ++i) {
            delete []tmptest[i];
        }
        cout<<"test memory(together delete)"<<" block size"<<length<<" "<<tracer.getRunTime()<<endl;
        length*=2;

    }
    delete tmptest;
}

class test{
public:
    float trand(){
        return rand();
    }
};

void testptr(){
    float tmp;
    test* trand=new test();
    Tracer tracer;
    tracer.startTime();
    for (int i = 0; i < 1024; ++i) {
        tmp=trand->trand();
    }
    cout << "Ingestion: " << tracer.getRunTime() << endl;
    unique_ptr<test> tprand(new test());
    for (int i = 0; i < 1024; ++i) {
        tmp=tprand->trand();
    }
    cout << "Ingestion: " << tracer.getRunTime() << endl;
    delete(trand);
}



void testsimd(){
    int cntbuf=4096;
    float pbuf[cntbuf];
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

    __m256 yfsProduct=_mm256_set_ps(1,1,1,1);
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

    __m256 yfsProduct=_mm256_set_ps(1,1,1,1);
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

int main() {
    testsimd();
    return 0;
}