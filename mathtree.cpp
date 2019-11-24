#include"mathtree.hpp"

// Tree methods

Mathtree::Mathtree()
{
    this->root = nullptr;
}

int Mathtree::createRoot(const mtnodedata_t num_, const char type_)
{
    if(this->root != nullptr)
        return 1;
    
    this->root = new MathtreeNode(num_, type_);

    return 0;
}

int Mathtree::setRoot(MathtreeNode* node_)
{
    if(this->root != nullptr)
        return 1;
    
    this->root = node_;

    return 0;
}

// Data methods

MathtreeData::MathtreeData(const mtnodedata_t num_, const char type_)
{
    this->data = num_;
    this->type = type_;
}

char MathtreeData::getType()
{
    return this->type;
}

// Node methods

void MathtreeNode::dotWriteNodes_(FILE* dotfile_)
{
    fprintf(dotfile_, "    node_%p [label=\"", this);

    if(this->data->type == MTDATATYPE(Number))
        fprintf(dotfile_, MTELEM_T, this->data->data.num);

    else if(this->data->type == MTDATATYPE(Op))
        fprintf(dotfile_, opToStr(this->data->data));

    else
        fprintf(dotfile_, "Unknown type");
    
    fprintf(dotfile_, "\"];\n");

    if(this->right != nullptr)
        this->right->dotWriteNodes_(dotfile_);

    if(this->left != nullptr)
        this->left->dotWriteNodes_(dotfile_);
};

void MathtreeNode::dotWriteEdges_(FILE* dotfile_)
{
    if(this->right != nullptr)
    {
        fprintf(dotfile_, "    node_%p -- node_%p;\n", this, this->right);
        this->right->dotWriteEdges_(dotfile_);
    }

    if(this->left != nullptr)
    {
        fprintf(dotfile_, "    node_%p -- node_%p;\n", this, this->left);
        this->left->dotWriteEdges_(dotfile_);
    }
};

MathtreeNode::MathtreeNode(const mtnodedata_t num_, const char type_)
{
    this->data   = new MathtreeData(num_, type_);
    this->parent = nullptr;
    this->right  = nullptr;
    this->left   = nullptr;
}

int MathtreeNode::createRight(const mtnodedata_t num_, const char type_)
{
    if(this->right != nullptr)
        return 1;
    
    this->right = new MathtreeNode(num_, type_);

    return 0;
}

int MathtreeNode::createLeft(const mtnodedata_t num_, const char type_)
{
    if(this->left != nullptr)
        return 1;
    
    this->left = new MathtreeNode(num_, type_);

    return 0;
}

int MathtreeNode::setRight(MathtreeNode* node_)
{
    if(this->right != nullptr)
        return 1;

    this->right = node_;

    return 0;
}

int MathtreeNode::setLeft(MathtreeNode* node_)
{
    if(this->left != nullptr)
        return 1;

    this->left = node_;

    return 0;
}

int MathtreeNode::dump(const char* path)
{
    FILE* dotfile_ = fopen(path, "w");

    fprintf(dotfile_, "graph Mathtree {\n");

    this->dotWriteNodes_(dotfile_);

    fprintf(dotfile_, "\n");

    this->dotWriteEdges_(dotfile_);

    fprintf(dotfile_, "}");

    fclose(dotfile_);

    return 0;
}