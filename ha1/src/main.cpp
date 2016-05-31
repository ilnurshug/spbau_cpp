#include "huffman_archive.h"
using namespace std;

void test() 
{
    huffman::huffman_archive::info i;
    
    huffman::huffman_archive::serialize("input", "out.bin", i);
    cout << i.input_len << endl << i.output_len << endl << i.aux_len << endl;
    
    huffman::huffman_archive::deserialize("out.bin", "res", i);
    cout << i.input_len << endl << i.output_len << endl << i.aux_len << endl;
}

char* get(const char *flag, int argc, char* argv[])
{
    char *a = 0;
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], flag) == 0) 
        {
            a = argv[i + 1];
            break;
        }
    }
    return a;
}

int main(int argc, char* argv[]) 
{
    //test();
    //return 0;
    
    char *in  = get("-f", argc, argv);
    char *out = get("-o", argc, argv); 
    
    if (!in)  in  = get("--file", argc, argv);
    if (!out) out = get("--output", argc, argv);
    
    if (!in || !out)
    {
        cout << "arg error\n";
        return 0;
    }
    
    huffman::huffman_archive::info i;
    
    if (strcmp(argv[1], "-c") == 0)
    {
        huffman::huffman_archive::serialize(in, out, i);
    }
    else if (strcmp(argv[1], "-u") == 0)
    {
        huffman::huffman_archive::deserialize(in, out, i);
    }
    
    cout << i.input_len << endl << i.output_len << endl << i.aux_len << endl;
    
    /*ofstream fout;
    fout.open("input", ios::binary | ios::out);
    for (size_t i = 1; i < 3500 * 2000; i++)
    {
        //for (size_t k = 0; k <= i; k++)
        //{
        //    char tmp = (char)('a' + (i % 28));
        //    fout.write(&tmp, 1);
        //}
        char tmp = (char)('a' + rand() % 28);
        fout.write(&tmp, 1);
    }
    fout.close();*/
    
    
    
    return 0;
}