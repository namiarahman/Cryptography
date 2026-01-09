#include <iostream>
using namespace std;

void encode() {
    string in_mess;
    cout<<"Enter the message to encode: "<<endl;
    cin.ignore();
    getline(cin, in_mess);
    
    int mess_val[100];
    int count=0;
    
    for(char ch:in_mess) {
        if(ch==' ')
            mess_val[count++]=0;
        else
            mess_val[count++]=ch-'A'+1;
    }

    if(count%2!=0) {
        mess_val[count++]=0;
    }

    int cols=count/2;
    int mess_2d[2][50];  
    int index1=0;


    for (int i=0; i<cols; i++) {
        for (int j=0; j<2; j++) {
            mess_2d[j][i]=mess_val[index1++];
        }
    }
    
    int code[2][2];
    cout<<"Enter the 4 digit code: "<<endl;
    int code_input;
    cin>>code_input;
    code[0][0]=code_input/1000;
    code[0][1]=(code_input/100)%10;
    code[1][0]=(code_input/10)%10;
    code[1][1]=code_input%10;
    
    
    
    //for encoding
    int enc_2d[2][50]={0};
    
    //multiplying matrices
    for(int i=0; i<2; i++){
        for(int j=0; j<cols; j++){
            for(int k=0; k<2; k++){
                enc_2d[i][j]+=code[i][k]*mess_2d[k][j];
            }
        }
    }
    
    //making sure values are between 0-26
    for(int i=0; i<2; i++){
        for(int j=0; j<cols; j++){
            enc_2d[i][j] = ((enc_2d[i][j]%27)+27)%27;
        }
    }
    
    //turing 2d array into 1d
    int enc_val[count];
    int index2=0;
    for(int i=0; i<cols; i++){
        for(int j=0; j<2; j++){
            enc_val[index2++]=enc_2d[j][i];
        }
    }
    
    //turning array into message
    string enc_mess="";
    for(int i=0; i<count; i++){
        if (enc_val[i]==0){
            enc_mess+=' ';  
        }
        else{
            enc_mess+=(char)(enc_val[i]+'A'-1);  
        }
    }
    
    cout<<enc_mess<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
}

void decode() {
    //for decoding
    
    string in_mess;
    cout<<"Enter the message to decode: "<<endl;
    cin.ignore();
    getline(cin, in_mess);
    
    int mess_val[100];
    int count=0;
    
    for(char ch : in_mess) {
        if(ch==' ')
            mess_val[count++]=0;
        else
            mess_val[count++]=ch-'A'+1;
    }

    if(count%2!=0) {
        mess_val[count++]=0;
    }

    int cols=count/2;
    int mess_2d[2][50];  
    int index1=0;


    for (int i=0; i<cols; i++) {
        for (int j=0; j<2; j++) {
            mess_2d[j][i]=mess_val[index1++];
        }
    }
    
    int code[2][2];
    cout<<"Enter the 4 digit code: "<<endl;
    int code_input;
    cin>>code_input;
    code[0][0]=code_input/1000;
    code[0][1]=(code_input/100)%10;
    code[1][0]=(code_input/10)%10;
    code[1][1]=code_input%10;
    
    
    
    int det=(code[0][0]*code[1][1]-code[0][1]*code[1][0]) % 27;
    if(det<0){ 
        det+=27;
    }
    
    // modular inverse of determinant
    int det_inv=-1;
    for(int i=1; i<27; i++){
        if((det*i)%27==1){
            det_inv=i;
            break;
        }
    }
    if(det_inv==-1){
        cout<<"Matrix not invertible modulo 27!";
        return;
    }
    
    // integer inverse matrix mod 27
    int inv_code[2][2];
    inv_code[0][0]=(code[1][1]*det_inv)%27;
    inv_code[0][1]=(-code[0][1]*det_inv+27)%27;
    inv_code[1][0]=(-code[1][0]*det_inv+27)%27;
    inv_code[1][1]=(code[0][0]*det_inv)%27;

    
    int dec_2d[2][50] = {0};

    for(int i=0; i<2; i++){
        for(int j=0; j<cols; j++){
            dec_2d[i][j]=0;
            for(int k=0; k<2; k++){
                dec_2d[i][j]+=inv_code[i][k]*mess_2d[k][j];
                dec_2d[i][j]%=27; // keep in 0-26
            }
            if(dec_2d[i][j]<0) dec_2d[i][j]+=27;
        }
    }

    
    //turing 2d array into 1d
    int dec_val[count];
    int index2=0;
    for(int i=0; i<cols; i++){
        for(int j=0; j<2; j++){
            dec_val[index2++]=dec_2d[j][i];
        }
    }

    
    for(int i=0; i<count; i++){
            dec_val[i]=((dec_val[i]%27)+27)%27;
    }


    
    //turning array into message
    string dec_mess="";
    for(int i=0; i<count; i++){
        if (dec_val[i]==0){
            dec_mess+=' ';  
        }
        else{
            dec_mess+=(char)(dec_val[i]+'A'-1);  
        }
    }
    
    cout<<dec_mess;
}

int main() {
    int choice;
    cout<<"Enter 1 to encode or 2 to decode: "<<endl;
    cin>>choice;
    
    if(choice==1) {
        encode();
    } else if(choice==2) {
        decode();
    } else {
        cout<<"Invalid choice!"<<endl;
    }
    
    return 0;
}