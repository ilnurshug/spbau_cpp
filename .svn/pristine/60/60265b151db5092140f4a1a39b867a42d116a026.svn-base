#include "huffman_archive.h"

namespace huffman
{

void huffman_archive::serialize(const char* src, const char* dst, info& i) 
{
    vector<char> in, out;
    read_all_bytes(src, in);
    
    huffman::node* root;
    auto len = huffman::compress::cmprs(in, out, root);
    
    vector<lin_node> tree;
    size_t t_in = 0;
    linearize_tree(root, tree, t_in);
    
    delete root;
    
    i.input_len  = in.size();
    i.output_len = ceil((double)len / 8);    
    i.aux_len = tree.size() * size_of_lin_node;
    
    ofstream fout;
    fout.open(dst, ios::binary | ios::out);
    
    fout.write(reinterpret_cast<char*>(&i.aux_len), sizeof(long long));
    for (size_t i = 0; i < tree.size(); ++i)
    {
        fout.write(reinterpret_cast<char*>(&tree[i].sym), sizeof(char));
        fout.write(reinterpret_cast<char*>(&tree[i].l), sizeof(int));
        fout.write(reinterpret_cast<char*>(&tree[i].r), sizeof(int));
    }
    
    fout.write(reinterpret_cast<char*>(&len), sizeof(long long));
    
    for (size_t i = 0; i < out.size(); ++i)
        fout.write(reinterpret_cast<char*>(&out[i]), 1);
    
    fout.close();
}

void huffman_archive::deserialize(const char* src, const char* dst, info& i)
{
    ifstream ifs(src, ios::binary | ios::in);
    ifs.read(reinterpret_cast<char*>(&i.aux_len), sizeof(long long));
    
    vector<lin_node> tree;
    long long tree_len = i.aux_len / size_of_lin_node;
    for (long long k = 0; k < tree_len; ++k)
    {
        lin_node tmp;
        ifs.read(reinterpret_cast<char*>(&tmp.sym), sizeof(char));
        ifs.read(reinterpret_cast<char*>(&tmp.l), sizeof(int));
        ifs.read(reinterpret_cast<char*>(&tmp.r), sizeof(int));
        
        tree.push_back(tmp);
    }
    
    long long input_len, byte_len;
    ifs.read(reinterpret_cast<char*>(&input_len), sizeof(long long));

    byte_len = ceil((double)input_len / 8);
    vector<char> in;
    for (long long i = 0; i < byte_len; ++i)
    {
        char tmp;
        ifs.read(&tmp, sizeof(char));
        in.push_back(tmp);
    }
    ifs.close();
    
    huffman::node* root = delinearize_tree(tree);
    
    vector<char> out;
    huffman::decoder::decode(in, input_len, out, root); 
    
    i.input_len  = in.size(); 
    i.output_len = out.size();
    
    write_all_bytes(dst, out);
    
    delete root;
}

void huffman_archive::linearize_tree(huffman::node* t, vector<lin_node>& tree, size_t& t_in)
{
    if (!t) return;
    
    tree.push_back(lin_node());
    size_t i = tree.size() - 1;
    
    if (t->l && t->r) 
    {
        tree[i].l = ++t_in;
        linearize_tree(t->l, tree, t_in);
        tree[i].r = ++t_in;
        linearize_tree(t->r, tree, t_in);
    }
    else
    {
        tree[i].sym = t->sym;
        tree[i].l = tree[i].r = -1;
    }
}

huffman::node* huffman_archive::delinearize_tree(vector<lin_node>& tree, size_t i)
{
    if (!tree.size()) return NULL;
    
    huffman::node *t = new node();
    
    if (tree[i].l != -1 && tree[i].r != -1)
    {
        t->l = delinearize_tree(tree, tree[i].l);
        t->r = delinearize_tree(tree, tree[i].r);
        
        t->l->p = t;
        t->l->p = t;
    }
    else
    {
        t->sym = tree[i].sym;
    }
    
    return t;
}

void huffman_archive::read_all_bytes(const char* filename, vector<char>& bytes)
{
    ifstream ifs(filename, ios::binary | ios::ate);
    ifstream::pos_type pos = ifs.tellg();
    
    vector<char>  result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

    ifs.close();
    
    bytes = result;
}

void huffman_archive::write_all_bytes(const char* filename, vector<char>& bytes)
{
    ofstream fout;
    fout.open(filename, ios::binary | ios::out);

    for (size_t i = 0; i < bytes.size(); ++i)
        fout.write((char*) &bytes[i], 1);

    fout.close();
}
    
} // huffman
