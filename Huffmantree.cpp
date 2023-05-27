#include <iostream>
#include<vector>
#include<string>
using namespace std;


struct output{
    char name;
    string value;

    output(){
        name = ' ';
        value = "";
    }
};



struct huffmannode{
    int freq;
    char name;
    huffmannode * left;
    huffmannode * right;

    huffmannode(){
        name = ' ';
        freq = 10;
        left = nullptr; 
        right  = nullptr;
    }

    huffmannode(int data){
        name = ' ';
        freq = data;
        left = nullptr; 
        right  = nullptr;
    }
};
void printvec(huffmannode * vec, int size){
    for (int i = 0; i<size; i++){
        cout<<vec[i].freq<<";";
    }
    cout<<endl;
    
}

void swap(huffmannode* vec, int pos, int pos2){
    huffmannode temp = vec[pos];
    vec[pos] = vec[pos2];
    vec[pos2] = temp;
}

void heapify(huffmannode* vec, int index, int size){
    int max = index;
    int left  = (index*2)+1;
    int right = (index*2)+2;
    if(left<size && vec[left].freq < vec[max].freq){
        max = left;
    }
    if(right<size && vec[right].freq < vec[max].freq){
        max = right;
    }
    if(max!= index){
        swap(vec, max, index);
        heapify(vec, max, size);
    }

}

huffmannode* minheapify(huffmannode* vec, int size){

    for(int i = size/2-1; i>=0; i--){//heapify every thing so it is a maxheap. i start at size/2 -1
        heapify(vec, i , size);//anything under that is leaf nodes
    }


    return vec;
}
void heapinsert(huffmannode* vec,huffmannode key, int i){
    vec[i]= key;
    while(vec[i/2].freq > vec[i].freq){
        swap(vec, i/2, i);
        i = i/2;
    }
}

huffmannode* heapextract(huffmannode* vec,int i){
    
    huffmannode* data = new huffmannode[1];
    data->freq = vec[0].freq;
    data->right = vec[0].right;
    data->left = vec[0].left;
    data->name = vec[0].name;

    swap(vec, i, 0);
    heapify(vec, 0, i);
    return data;
}


huffmannode huffmancode(huffmannode* vec,int size){
    
    for(int i = 1; i<size; i++){
        //we have to use malloc becuase if we have local variable, 
        // in the next itration the node might be overwriten 
        //then the pointer are no longer pointeing at the right thing
        huffmannode *z, *x, *y;
     
        x = heapextract(vec, size-i);
        y = heapextract(vec, size-i-1);
        z = new huffmannode[1];
        z->freq = x->freq+y->freq;
        z->left= x;
        z->right = y;
        

        heapinsert(vec, *z, size-i-1);

    }
    return vec[0];

}
void generate_output(huffmannode* node, vector<output>& outvec, char* code, int len) {
    if (node->left == nullptr && node->right == nullptr) {
        // leaf node, print or store the code
        output a;
        a.name = node->name;
        for (int i = 0; i < len; i++) {
            a.value += code[i];
        }
        outvec.push_back(a);
    } else {
        // non-leaf node, recursively traverse its children
        code[len] = '0';
        generate_output(node->left, outvec, code, len + 1);
        code[len] = '1';
        generate_output(node->right, outvec, code, len + 1);
    }
}

void sort_output(vector<output>& outvec) {
    // Sort using bubble sort algorithm
    int n = outvec.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (outvec[j].name > outvec[j + 1].name) {
                output temp = outvec[j];
                outvec[j] = outvec[j + 1];
                outvec[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char** argv) {
    // getting the input
    int size = 6;
    huffmannode* freq = new huffmannode[6];
    char names[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    for (int i = 0; i < size; i++) {
        huffmannode data;
        cin >> data.freq;
        data.name = names[i];
        freq[i] = data;
    }
    freq = minheapify(freq, size);

    huffmannode tree = huffmancode(freq, size);

    char* code = new char[size];
    vector<output> outvec;

    generate_output(&tree, outvec, code, 0);

    sort_output(outvec);

    for (int i = 0; i < 6; i++) {
        output k = outvec[i];
        cout << k.name << ":" << k.value << endl;
    }

    return 0;
}
