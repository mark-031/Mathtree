#include<assert.h>
#include<stdio.h>

typedef float mtelem_t;
#define MTELEM_T "%.3f"

union mtnodedata_t
{
    mtelem_t     num;
    unsigned int op;
    char         var;

    mtnodedata_t()
    {
        op  = 0;
        num = 0;
        var = 0;
    }

    mtnodedata_t(unsigned int item)
    {
        op = item;
    }

    mtnodedata_t(mtelem_t item)
    {
        num = item;
    }

    mtnodedata_t(char item)
    {
        var = item;
    }
};


enum MathtreeDataTypes
{
    MathtreeDataTypeNumber   = 1,
    MathtreeDataTypeOp       = 2,
    MathtreeDataTypeVar      = 3,
};

#define MTDATATYPE(name) (char) MathtreeDataType##name

const char* opAdd = "+";
const char* opSub = "-";
const char* opMul = "*";
const char* opDiv = "/";

const char* opUnknown = "(+)";

enum MathtreeDataOperators
{
    MathtreeDataOperatorAdd = 1,
    MathtreeDataOperatorSub = 2,
    MathtreeDataOperatorMul = 3,
    MathtreeDataOperatorDiv = 4,
};

#define MTDATAOP(name) ((unsigned int) MathtreeDataOperator##name)

#define OPCHECKSTART() if(0)
#define OPCHECK(name) else if(MTDATAOP(name) == data.op) return op##name
#define OPCHECKEND() else return opUnknown

const char* opToStr(const mtnodedata_t& data)
{
    OPCHECKSTART();
    OPCHECK(Add);
    OPCHECK(Sub);
    OPCHECK(Mul);
    OPCHECK(Div);
    OPCHECKEND();
}

class Mathtree;
class MathtreeData;
class MathtreeNode;

class Mathtree
{
    private:
        MathtreeNode* root;

    public:
        Mathtree();

        ~Mathtree();

        int createRoot(const mtnodedata_t num_, const char type_);

        int setRoot(MathtreeNode* node_);
};

class MathtreeData
{
    private:
        mtnodedata_t data;
        char         type;

        friend class MathtreeNode;

    public:
        MathtreeData(const mtnodedata_t num_, const char type_);

        char getType();
};

class MathtreeNode
{
    private:
        MathtreeData* data;
        MathtreeNode* parent;
        MathtreeNode* right;
        MathtreeNode* left;

        void init_(const mtnodedata_t num_, const char type_);

        void dotWriteNodes_(FILE* dotfile_);

        void dotWriteEdges_(FILE* dotfile_);

    public:
        MathtreeNode(const mtnodedata_t num_, const char type_);

        MathtreeNode(const mtelem_t number_);

        MathtreeNode(const unsigned int op_);

        MathtreeNode(const char var_);

        ~MathtreeNode();

        int createRight(const mtnodedata_t num_, const char type_);
        
        int createLeft(const mtnodedata_t num_, const char type_);

        int setRight(MathtreeNode* node_);
        
        int setLeft(MathtreeNode* node_);

        mtelem_t calc();

        int dump(const char* path);

        MathtreeNode* operator+(MathtreeNode& node_);

        MathtreeNode* operator+(const mtelem_t& num_);

        MathtreeNode* operator-(MathtreeNode& node_);

        MathtreeNode* operator-(const mtelem_t& num_);

        MathtreeNode* operator*(MathtreeNode& node_);

        MathtreeNode* operator*(const mtelem_t& num_);

        MathtreeNode* operator/(MathtreeNode& node_);

        MathtreeNode* operator/(const mtelem_t& num_);

        friend MathtreeNode* operator+(const mtelem_t& num_, MathtreeNode& node_);

        friend MathtreeNode* operator-(const mtelem_t& num_, MathtreeNode& node_);

        friend MathtreeNode* operator*(const mtelem_t& num_, MathtreeNode& node_);

        friend MathtreeNode* operator/(const mtelem_t& num_, MathtreeNode& node_);
};