//ip�A�h���X�ƃT�u�l�b�g�܂��̓v���t�B�b�N�X����͂�����
//�l�b�g���[�N�A�h���X�A�z�X�g�̍ŏ��A�Ō�A�u���[�h�L���X�g
//�z�X�g�̌��Ȃǂ��낢��ȏ����o���Ă���鑕�u

//���񂻂�
//���N�U��ɃR�[�h�������܂����B�o�͂̎d������낤���Ƃ��납��悭�����グ���Ȃ��Ďv���܂��B�֐���������Ƃ��͍ŏ����̋@�\�ɗ��߂�Ƃ����Ə����₷�������Ȃ��Ďv���܂��B�ȒP�Ȃ悤�Ŗl�ɂƂ��Ă͕��G�ł������K�ɂȂ����ȂƎv���܂��B�����s�ɂȂ�Ɗ֐������ƂĂ��厖���ȂƎv���܂����B�r�����񂩂�����߂����ɂȂ�܂������A�����ł��Ă悩�����ł��B�ǐ��̍����R�[�h��ڎw���Ă��������ł�
//2020/06/23 18:38

/*
 * �G���[�����i�C�ɂ��Ȃ��ł��������j

   �G���[ �ۑ�SQ2
   10.101.99.228 255.255.128.0
   insert�Ŗ������[�v���Ă�H
   ���炵��.��߂����̂ŉ����H

   Q5
   128.107.0.55 255.255.255.0
   �u���[�h�L���X�g�\���o�O \0�������ĂȂ���
   ��������


   */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//-1.�e[16]����J�b�g����child_10[4](char10�i��,4bit)�𐶐�����
int cutter(int octet,char *parent,char *child_10,int *start_memo,int *end_memo);

//0.sum����text_2(char2�i�� 8bit)���쐬
int create_text_2(int sum,char *text_2);

//0.5 binary_ip �� binary_sub��AND���Z
int math_and(char *binary_ip,char *binary_sub,char *text_2);

//1.char��i��(8bit)text_2��10�i��(int)�ɒ��� return sum;��sum����󂯎��
int bin(char *text_2);

//2.int10�i��(sum)��char10�i���ɂ���
int texting(int num_10,char *child_10);//char *child_10�Ɏ��e ������return�ŕԂ�

//3.char10�i���𖄂ߍ��� return start;
//�������������Ă��܂��\��������̂Ŏg�p�͌���I
int bury(int length,char *child_10,char *sub,int start);

//3.network_address�̍쐬
//bury�֐�����ʓI�Ȏg�p���ł���悤�ɕύX
void insert(int octet,char *parent,char *child,int *start_memo,int *end_memo);
        
//4.search_sub() host_bit�����߂�Breturn��host_bit
int search_sub(char *binary_sub ,int octet);

//main�֐�
int main (void){

        //����

        //���b�Z�[�W
        //puts("ip�A�h���X�ƃv���t�B�b�N�X�܂��̓T�u�l�b�g�}�X�N�𔼊p�X�y�[�X�ŋ�؂��ē��͂��Ă�������:");
        
        puts("Enter the ip address and prefix or subnet mask with spacekey,and will show you network address ,broadcast address and so on.");
        //puts("��:");
        puts("example:");
        puts("172.16.77.120 /16");
        puts("172.16.77.120 255.255.0.0");
        puts("");

        //���͗p����m��
        char ip[16];//max 15 +1
        char sub[16];//max 15 +1
        scanf("%s %s",ip,sub);

        //�����̎擾
        int ip_length = strlen(ip);
        int sub_length = strlen(sub);
        //printf("ip_length:%d sub_length:%d\n",ip_length,sub_length);

        //sub���v���t�B�b�N�X�^�C�v���T�u�l�b�g�}�X�N������
        //sub��1�����ڂ�����
        //�v���t�B�b�N�X�Ȃ�pre = 1

        int pre=0;
        int i=0;
        int value=0;
        int tmp=0;
        int syou=0;
        int amari=0;
        int t=0;
        int num_10;
        char text_2[9];
        char child_10[4];
        int length=0;
        if(sub[0]=='/'){
                pre = 1;

                //sub�ɃT�u�l�b�g�}�X�N�Ƃ��ď㏑������

                //�㏑���̑O�ɒl��ۑ�
                //value�ɕۑ� 
                for(i=0;i<sub_length-1;i++){

                        tmp = sub[sub_length-i-1] - '0';
                        value += tmp *pow(10,i);
                        //printf("value:%d\n",value);
                }
                //printf("value:%d\n",value);

                //sub�ɏ㏑��
                syou = value / 8;
                amari = value % 8;

                //syou�̕�����255���㏑��
                for(i=0;i<syou;i++){

                        sub[t] = '2';
                        t++;

                        sub[t] = '5';
                        t++;

                        sub[t] = '5';
                        t++;

                        sub[t] = '.';
                        t++;

                }//for i
                //printf("sub:%s\n",sub);

                //amari�̕����㏑��
                if(amari==0){
                        //pass

                }else{
                        //�]�蕪�𖄂߂�

                        //2�i����10�i���ɒ���
                        //1�̐�:amari 0�̐�:8-amari
                        for(i=0;i<8;i++){

                                if(i<amari){
                                        text_2[i] = '1';

                                }else{
                                        text_2[i] = '0';

                                }
                        }
                        num_10 = bin(text_2);//�������n���Ă���̂��s��
                        //printf("num_10(sum):%d\n",num_10);

                        //sub�ɖ��߂�
                        //�������珑��
                        length = texting(num_10,child_10);//char *child_10�Ɏ��e

                        //printf("child_10:%s\n",child_10);

                        t = bury(length,child_10,sub,t);


                        //���߂���syou+1
                        syou += 1;


                }//if amari

                while(syou != 4){

                        sub[t] ='0';
                        t++;

                        sub[t] = '.';
                        t++;

                        syou += 1;

                }

                //�Ō�̃h�b�g�ɏ㏑���@�s��
                sub[t-1] = '\0';




        }else{
                //pass

        }//if sub[0]=='/'

        /*
        //�\��(�\������G���A�Ɍ�ł܂Ƃ߂�)
        puts("--------------------------");
        printf("IP�A�h���X      :%s\n",ip);
        printf("�T�u�l�b�g�}�X�N:%s\n",sub);
        */


        //�v���t�B�b�N�X�������ꍇ�T�u�l�b�g�}�X�N�ɒ����܂ŏI��
        //�������瓯������

        //ip�ƃT�u�l�b�g��2�i���ɒ�����AND���Z

        //2�i���ɒ����I�N�e�b�g�̌���
        //�T�u�l�b�g��255�ł͂Ȃ��Ȃ����Ƃ�
        //�T�u�l�b�g��sub(char)�Ɏ��e

        int octet=0;
        int octet_value=0;
        int count=0;
        for(octet=0;octet<4;octet++){

                count = 0;
                t = octet * 4; 

                //255�`�F�b�N

                //2�`�F�b�N
                if(sub[t]=='2'){
                        count++;

                }else{

                }
                t++;

                //5�`�F�b�N
                if(sub[t]=='5'){
                        count++;

                }else{

                }
                t++;

                //5�`�F�b�N
                if(sub[t]=='5'){
                        count++;

                }else{

                }
                t++;

                if(count==3){
                        //pass
                }else{
                        break;
                }
        }

        octet_value = octet+1;
        //printf("octet:%d\n",octet_value);

        //�\��
        puts("------------------");
        //printf("AND���Z�I�N�e�b�g�ӏ�:%d\n",octet_value);
        printf("calculating in octet %d...\n",octet_value);
        puts("");

        //�ϐ�octet�̃I�N�e�b�g��2�i���ɂȂ�����AND���Z

        char child_ip_10[4];
        char binary_ip[9];
        char child_sub_10[4];
        char binary_sub[9];

        int decimal_ip=0;
        int keta;
        int tmpt=0;
        int sum=0;
        int start_memo=0;
        int end_memo=0;
        //binary_ip�̍쐬
        sum = cutter(octet,ip,child_ip_10,&start_memo,&end_memo);
        //printf("sum%d\n",sum);
        tmpt = create_text_2(sum,binary_ip);

        //�\��
        printf("decimal_ip(10) :%s\n",child_ip_10);
        printf("binary_ip(2)   :%s\n",binary_ip);

        //binary_sub�̍쐬
        sum = cutter(octet,sub,child_sub_10,&start_memo,&end_memo);
        tmpt = create_text_2(sum,binary_sub);

        //�\��
        puts("");
        printf("decimal_sub(10):%s\n",child_sub_10);
        printf("binary_sub(2)  :%s\n",binary_sub);

        //binary_ip��binary_sub��AND���Z
        tmpt = math_and(binary_ip,binary_sub,text_2);

        puts("");
        puts("after AND");
        printf("binary(2)      :%s\n",text_2);

        //10�i���ɖ߂�
        sum = bin(text_2);
        printf("decimal(10)    :%d\n",sum);

        int sum_AND = sum;//����sum�g�����Ⴄ

        //�l�b�g���[�N�A�h���X�Ƃ��ĕ\��
        //2.int10�i��(sum)��char10�i���ɂ���
        char AND_10[4];
        length = texting(sum_AND,AND_10);//char *child_10�Ɏ��e ������return�ŕԂ�


        //start�̈ʒu�ɍ���
        //cutter��start,end�̈ʒu���킩��

        //**start_memo���L�^
        sum = cutter(octet,ip,child_10,&start_memo,&end_memo);

        //�}��
        char network_address[16];
        strcpy(network_address,ip);//�����Ă邩�s��
        insert(octet,network_address,AND_10,&start_memo,&end_memo);

        //�\��
        //printf("network address:%s\n",network_address);


        //binary_ip(2),binary_sub(2)�ɂ���s�����Ă����Ă��A���S���Y�����l�b�N�ȋC������

        //�z�X�g���̕\��
        int host_bit=0;
        host_bit = search_sub(binary_sub,octet);
        //printf("�z�X�g��:%d(2^%d -2 )\n",(int)pow(2,host_bit)-2,host_bit);
        /*
        printf("2^%d = %d\n",host_bit,(int)pow(2,host_bit));
        printf("�z�X�g��:%d(2^%d - 2)\n",(int)pow(2,host_bit)-2,host_bit);
        */

        //�u���[�h�L���X�g�A�h���X

        int host_bit_tmp = host_bit;
        int broad_octet = 3;//�Y����
        while(host_bit_tmp >=9){

                host_bit_tmp %= 8;
                broad_octet--;

        }
        /*
        puts("---non accurate---");
        printf("broad_octet:%d\n",broad_octet);
        printf("host_bit_tmp:%d\n",host_bit_tmp);
        */

        //��broad_octet�I�N�e�b�g�̐���host_bit_tmp�����₹�΂���
        char broad_cast[16];
        strcpy(broad_cast,network_address);//�ł��Ă邩�ȁH �ł��Ă�

        //printf("broad_cast:%s\n",broad_cast);
        
        //cutter�Ăяo���čŏ��Ō�𒲂ׂ�
        //������network_address���Q��
        //char AND_10[4];����g�����ق�������
        sum = cutter(broad_octet,network_address,child_10,&start_memo,&end_memo);
        //�����󔒂Ƃ����v�Z���Ă��܂��Ă���̂�AND_10���g��
        sum = atoi(AND_10);
        //printf("cutter�Ŏ��o����sum:%d\n",sum);

        //start_memo ~ end_memo�̂Ƃ����host_bit_tmp���ӂ₷
        //�����������򂵂Ȃ��Ă���
        /*
        if(broad_octet==3){
                //�z�X�g����256�ȉ��̂Ƃ�
                //��4�I�N�e�b�g���C������̂ł��̑��̏C���͂���Ȃ�
                sum = sum + pow(2,host_bit_tmp)-1;

        }else{
                //��1~3�I�N�e�b�g���C���A���̂��Ƃ�255�ɂ���K�v������
                //sum = sum + host_bit_tmp - 1;
                sum = sum + pow(2,host_bit_tmp)-1;
                puts("broad cast�A�h���X�Ɍ�肪����\��������܂�");

        }
        */
        sum = sum + pow(2,host_bit_tmp)-1;

        //printf("����������sum:%d\n",sum);
        //2.int10�i��(sum)��char10�i���ɂ���
        length = texting(sum,child_10);//char *child_10�Ɏ��e ������return�ŕԂ�
        //bury�֐�����ʓI�Ȏg�p���ł���悤�ɕύX
        insert(broad_octet,broad_cast,child_10,&start_memo,&end_memo);

        //�C���������̃I�N�e�b�g����255�Ŗ��߂�
        int broad_octet_now = broad_octet;
        if(broad_octet==3){
                //pass
                //�����k�����������Ă�̂��ȁH �����悤�ɂ���
                //printf("after inserted)end_memo:%d\n",end_memo);
        }else{

                while(broad_octet_now < 3){

                        //puts("loop?");

                        broad_octet_now++;

                        //start end�𒲂ׂ�
                        sum = cutter(broad_octet_now,broad_cast,child_10,&start_memo,&end_memo);
                        child_10[0] = '2';
                        child_10[1] = '5';
                        child_10[2] = '5';
                        //���̃k�����������߂ȋC������
                        //child_10[3] = '\0';
                        
                        insert(broad_octet_now,broad_cast,child_10,&start_memo,&end_memo);

                        //�m�F
                        //printf("broad cast(unfinished):%s\n",broad_cast);

                }

                //�k�������͂����Ɏ����Ă���΂����̂ł�
                //main�֐�����end_memo������̂Ń|�C���^���g���K�v���Ȃ��A�܂����Ƃ��Ɏg���K�v���o�Ă���
                //broad_cast[*end_memo+0] = '\0';

                //broad_cast[end_memo] = '\0';
        }
        //��S�I�N�e�b�g���C�������Ƃ��ɂ��k������������邽�߂������낤
        broad_cast[end_memo] = '\0';

        //puts("finished repairing broad cast.");

        //�\���ݒ�G���A�i�����ɂ܂Ƃ߂�j
        puts("");
        puts("");
        puts("RESULT");
        printf("ip_address         :%s\n",ip);
        printf("subnet_mask        :%s\n",sub);
        printf("network_address    :%s\n",network_address);
        printf("broadcast_address  :%s\n",broad_cast);
        //printf("host_bit          :%d(2^%d = %d)\n",host_bit,host_bit,(int)pow(2,host_bit));
        printf("host_amount        :%d(2^%d - 2)\n",(int)pow(2,host_bit)-2,host_bit);

        //return
        return 0;
}//main

//-1.�e[16]����J�b�g����child_10[4]�𐶐�����
int cutter(int octet,char *parent,char *child_10,int *start_memo,int *end_memo){
        
        //ex 255.89.252.0
        //3�I�N�e�b�g���w�肳�ꂽ��252��؂��肽��
        int i=0;
        int t=0;
        int octet_value = octet+1;
        int count=0;
        int count_value=1;
        int keta=0;
        int fin=0;

        int start=0;
        int end=0;

        //�S����3*4 + 1*3 = 15 �k��������16����0~15
        //�����������������@�͈͂Ǝ�н
        //0~15 15�̓k������
        for(i=0;i<=15;i++){

                //����������������
                //��4�I�N�e�b�g���ނƃo�O��
                //sub�Ƃ������ƈ���Ȃ���������
                //��ԍŏ��Ɏg���̂Ŋ֌W�Ȃ�
                //��4�I�N�e�b�g�̎��������I���ł��Ă��Ȃ�
                //parent[i] == '\0'
                if(parent[i]=='.' || parent[i]== '\0' ){

                        if(fin==1){
                                //�k�����������
                                end = i-1;
                                child_10[t] = '\0';
                                break;
                        }else{
                                //pass
                        }

                        count++;
                        count_value++;

                }else{
                        //�ړI�I�N�e�b�g�������ꍇ�A���̎擾
                        //�l�̃R�s�[
                        if(octet_value == count_value){

                                //�����ǉ����Ă݂��s��
                                //�����ċ󔒂��ł����Ƃ����J�E���g���Ă��܂��Ă�̂ł͂Ȃ����낤��
                                if(fin==0){
                                        start = i;

                                }else{

                                }

                                keta++;
                                child_10[t] = parent[i];
                                //printf("child_10:%c parent:%c\n",child_10[t],parent[i]);
                                t++;

                                fin=1;



                        }else{

                                //pass
                        }

                }//if

        }//for i

        *start_memo = start;
        *end_memo = end;
        //printf("start_memo:%d end_memo:%d\n",*start_memo,*end_memo);

        //start,end,keta���킩�����̂ŁAsum�����߂�
        //child_10[4]
        int value;
        int cnt=0;
        int sum=0;

        //printf("keta:%d\n",keta);

        //�������������@�����H
        //sum�������Ⴄ��������
        for(i=0;i<keta;i++){

                sum += (child_10[keta-i-1] - '0') * pow(10,i);
                //printf("sum:%d\n",sum);

        }

        //sum���߂��ĂȂ�
        //start end���L�^����

        //�m�F�o��
        /*
        puts("in cutter");
        printf("child_10:%s\n",child_10);
        printf("keta:%d\n",keta);
        printf("parent:%s\n",parent);
        printf("sum:%d\n",sum);
        puts("END in cutter");
        */
        return sum;
}

//0.sum����text_2(char2�i�� 8bit)���쐬
int create_text_2(int sum,char *text_2){

        int value = sum;
        int pow_2;
        int cnt;
        int i;
        int syou;
        
        for(i=0;i<8;i++){

                syou = value / pow(2,8-i-1);
                //printf("value:%d syou;%d\n",value,syou);

                text_2[i] = syou + '0';

                value -= syou * pow(2,8-i-1);

        }
        text_2[i] = '\0';

        return 0;

}
//0.5 binary_ip �� binary_sub��AND���Z
int math_and(char *binary_ip,char *binary_sub,char *text_2){

        int i=0;
        int count=0;
        for(i=0;i<8;i++){

                if(binary_ip[i] == '1' && binary_sub[i] == '1'){

                        text_2[i] = '1';

                }else{
                        text_2[i] = '0';
                        count++;

                }

        }

        //���̃J�E���g�͎g��Ȃ��悤�ɁBhost_bit�ŃI�N�e�b�g�����������z�X�g�r�b�g�����J�E���g����Ă���
        return count;

}

//1.char��i��(8bit)text_2��10�i��(int)�ɒ��� return sum;��sum����󂯎��
int bin(char *text_2){

        /*
        printf("test_2:%s\n",text_2);
        printf("amari;%d\n",amari);
        */

        int i=0;
        int sum=0;
        int value=0;
        for(i=0;i<8;i++){

                value = text_2[8-i-1] - '0';
                
                sum += value * pow(2,i);

                //printf("sum:%d\n",sum);
        }
        //printf("sum:%d\n",sum);

        return sum;

}

//2.int10�i��(sum)��char10�i���ɂ���
int texting(int num_10,char *child_10){

        //char *child_10�Ɏ��e

        int i=0;
        int length=0;
        int syou=-1;
        int value = num_10;

        //���������߂�
        //10�Ŋ��邱�Ƃ��J��Ԃ���syou��0�ɂȂ�����I��
        //�A���S���Y�������Ă邩�s��
        while(syou!=0){

                syou = value / 10;
                value /= 10;
                length++;

        }
        value = num_10;

        //printf("length(keta):%d\n",length);

        //char *child_10�Ɏ��e
        int keta=-1;
        int pow_10=-1;
        for(i=0;i<length;i++){

                pow_10 = pow(10,length-i-1);
                keta = value / pow_10;
                value -= keta * pow_10;

                child_10[i] = keta + '0';

        }
        child_10[i] = '\0';

        return length;
}

//3.char10�i���𖄂ߍ��� return start;
int bury(int length,char *child_10,char *sub,int start){

        //printf("bury(child_10):%s\n",child_10);

        //sub[start]~sub[start+length-1]�܂�child_10��}��
        int i=0;
        for(i=0;i<length;i++){

                sub[start] = child_10[i];
                start++;

        }

        sub[start] = '.';
        start++;


        return start;

}

//3.network_address�̍쐬
//bury�֐�����ʓI�Ȏg�p���ł���悤�ɕύX
void insert(int octet,char *parent,char *child,int *start_memo,int *end_memo){

        //strlen�̓k�������͊܂܂Ȃ�
        int i;
        int delete_letter = *end_memo - *start_memo+1;
        int insert_letter = strlen(child);
        //printf("delete_letter:%d insert_letter:%d\n",delete_letter,insert_letter);
        //printf("start_memo:%d end_memo:%d\n",*start_memo,*end_memo);

        //insert�̂ق����傫����΂��炷
        if(delete_letter < insert_letter){
                //���炷
                //*start_memo����'\0'�܂ł�1������ɂ��炷
                //���炳�Ȃ���.��������ꍇ������o�O��
                //puts("���炷���������ĂȂ��̂ŁA�l�b�g���[�N�A�h���X�̕\�����o�O���Ă��܂�");
                //puts("���炷���������܂���");

                //�k�������̈ʒu��T��
                int posi=0;
                for(i=*start_memo;i<15;i++){

                        if(parent[i] == '\0'){
                                posi = i;

                        }else{

                        }

                }

                // �C�R�[���̏ꍇ�͊܂܂�Ă��Ȃ��̂Ńo�b�t�@�̂��ӂ�͋N����Ȃ�
                for(i=posi;i>=*start_memo;i--){

                        //�ړ�
                        parent[i+1] = parent[i];
                        parent[i] = parent[i-1];

                        //�k���������v���ȁA�A

                }

                /*
                int length_test = strlen(parent);
                printf("�������e�X�g:%d",length_test);
                */
        }else{
                //pass

        }


        //puts("deleteing letter");
        //�O�̕�������
        for(i= *start_memo+0;i<= *end_memo+0;i++){

                parent[i] = ' ';

        }

        //�}��
        //puts("inserting letter");
        for(i=0;i<insert_letter;i++){

                parent[*start_memo+i] = child[i];
        }
        *end_memo = *start_memo + i;
        //�����ǉ�
        //parent[*start_memo+i] = '\0';
        //������ƃl�b�g���[�N�A�h���X�~�X��

        int after_inserted_soon_t = *start_memo + i;

        //��l�I�N�e�b�g�܂�0�ɂȂ�
        //����͕ʊ֐��ł�����ق�������
        //�l�b�g���[�N�A�h���X�̎���0�ɂ��������A�u���[�h�L���X�g�̂Ƃ���255�ɂ�����
        
        //�m�F
        //printf("(unfinished):%s\n",parent);

        return;
}

//4.search_sub() host_bit�����߂�Breturn��host_bit
int search_sub(char *binary_sub,int octet){

        int i=0;
        int count=0;
        for(i=0;i<8;i++){

                if(binary_sub[8-i-1]=='0'){
                        count++;

                }else{
                        break;

                }

        }

        //���̃I�N�e�b�g�̓��[�J���̂͂���������v�A�A
        while(octet < 3){

                count += 8;
                octet++;

        }

        return count;

}

