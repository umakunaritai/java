//ipアドレスとサブネットまたはプレフィックスを入力したら
//ネットワークアドレス、ホストの最初、最後、ブロードキャスト
//ホストの個数などいろいろな情報を出してくれる装置

//かんそう
//半年振りにコードを書きました。出力の仕方すら危ういところからよく書き上げたなって思います。関数化をするときは最小限の機能に留めるともっと書きやすかったなって思います。簡単なようで僕にとっては複雑でいい練習になったなと思います。長い行になると関数化がとても大事だなと思いました。途中何回かあきらめそうになりましたが、完走できてよかったです。可読性の高いコードを目指していきたいです
//2020/06/23 18:38

/*
 * エラーメモ（気にしないでください）

   エラー 課題４Q2
   10.101.99.228 255.255.128.0
   insertで無限ループしてる？
   ずらして.を戻したので解決？

   Q5
   128.107.0.55 255.255.255.0
   ブロードキャスト表示バグ \0が入ってないか
   多分解決


   */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//-1.親[16]からカットしたchild_10[4](char10進数,4bit)を生成する
int cutter(int octet,char *parent,char *child_10,int *start_memo,int *end_memo);

//0.sumからtext_2(char2進数 8bit)を作成
int create_text_2(int sum,char *text_2);

//0.5 binary_ip と binary_subをAND演算
int math_and(char *binary_ip,char *binary_sub,char *text_2);

//1.char二進数(8bit)text_2を10進数(int)に直す return sum;でsumから受け取る
int bin(char *text_2);

//2.int10進数(sum)をchar10進数にする
int texting(int num_10,char *child_10);//char *child_10に収容 長さはreturnで返す

//3.char10進数を埋め込む return start;
//後ろを書き換えてしまう可能性があるので使用は限定的
int bury(int length,char *child_10,char *sub,int start);

//3.network_addressの作成
//bury関数を一般的な使用ができるように変更
void insert(int octet,char *parent,char *child,int *start_memo,int *end_memo);
        
//4.search_sub() host_bitを求める。returnはhost_bit
int search_sub(char *binary_sub ,int octet);

//main関数
int main (void){

        //入力

        //メッセージ
        //puts("ipアドレスとプレフィックスまたはサブネットマスクを半角スペースで区切って入力してください:");
        
        puts("Enter the ip address and prefix or subnet mask with spacekey,and will show you network address ,broadcast address and so on.");
        //puts("例:");
        puts("example:");
        puts("172.16.77.120 /16");
        puts("172.16.77.120 255.255.0.0");
        puts("");

        //入力用域を確保
        char ip[16];//max 15 +1
        char sub[16];//max 15 +1
        scanf("%s %s",ip,sub);

        //長さの取得
        int ip_length = strlen(ip);
        int sub_length = strlen(sub);
        //printf("ip_length:%d sub_length:%d\n",ip_length,sub_length);

        //subがプレフィックスタイプかサブネットマスクか判定
        //subの1文字目を見る
        //プレフィックスならpre = 1

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

                //subにサブネットマスクとして上書きする

                //上書きの前に値を保存
                //valueに保存 
                for(i=0;i<sub_length-1;i++){

                        tmp = sub[sub_length-i-1] - '0';
                        value += tmp *pow(10,i);
                        //printf("value:%d\n",value);
                }
                //printf("value:%d\n",value);

                //subに上書き
                syou = value / 8;
                amari = value % 8;

                //syouの分だけ255を上書き
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

                //amariの分を上書き
                if(amari==0){
                        //pass

                }else{
                        //余り分を埋める

                        //2進数を10進数に直す
                        //1の数:amari 0の数:8-amari
                        for(i=0;i<8;i++){

                                if(i<amari){
                                        text_2[i] = '1';

                                }else{
                                        text_2[i] = '0';

                                }
                        }
                        num_10 = bin(text_2);//正しく渡せているのか不安
                        //printf("num_10(sum):%d\n",num_10);

                        //subに埋める
                        //ここから書く
                        length = texting(num_10,child_10);//char *child_10に収容

                        //printf("child_10:%s\n",child_10);

                        t = bury(length,child_10,sub,t);


                        //埋めたらsyou+1
                        syou += 1;


                }//if amari

                while(syou != 4){

                        sub[t] ='0';
                        t++;

                        sub[t] = '.';
                        t++;

                        syou += 1;

                }

                //最後のドットに上書き　不安
                sub[t-1] = '\0';




        }else{
                //pass

        }//if sub[0]=='/'

        /*
        //表示(表示するエリアに後でまとめる)
        puts("--------------------------");
        printf("IPアドレス      :%s\n",ip);
        printf("サブネットマスク:%s\n",sub);
        */


        //プレフィックスだった場合サブネットマスクに直すまで終了
        //ここから同じもの

        //ipとサブネットを2進数に直してAND演算

        //2進数に直すオクテットの決定
        //サブネットが255ではなくなったとき
        //サブネットはsub(char)に収容

        int octet=0;
        int octet_value=0;
        int count=0;
        for(octet=0;octet<4;octet++){

                count = 0;
                t = octet * 4; 

                //255チェック

                //2チェック
                if(sub[t]=='2'){
                        count++;

                }else{

                }
                t++;

                //5チェック
                if(sub[t]=='5'){
                        count++;

                }else{

                }
                t++;

                //5チェック
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

        //表示
        puts("------------------");
        //printf("AND演算オクテット箇所:%d\n",octet_value);
        printf("calculating in octet %d...\n",octet_value);
        puts("");

        //変数octetのオクテットを2進数になおしてAND演算

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
        //binary_ipの作成
        sum = cutter(octet,ip,child_ip_10,&start_memo,&end_memo);
        //printf("sum%d\n",sum);
        tmpt = create_text_2(sum,binary_ip);

        //表示
        printf("decimal_ip(10) :%s\n",child_ip_10);
        printf("binary_ip(2)   :%s\n",binary_ip);

        //binary_subの作成
        sum = cutter(octet,sub,child_sub_10,&start_memo,&end_memo);
        tmpt = create_text_2(sum,binary_sub);

        //表示
        puts("");
        printf("decimal_sub(10):%s\n",child_sub_10);
        printf("binary_sub(2)  :%s\n",binary_sub);

        //binary_ipとbinary_subのAND演算
        tmpt = math_and(binary_ip,binary_sub,text_2);

        puts("");
        puts("after AND");
        printf("binary(2)      :%s\n",text_2);

        //10進数に戻す
        sum = bin(text_2);
        printf("decimal(10)    :%d\n",sum);

        int sum_AND = sum;//次でsum使っちゃう

        //ネットワークアドレスとして表示
        //2.int10進数(sum)をchar10進数にする
        char AND_10[4];
        length = texting(sum_AND,AND_10);//char *child_10に収容 長さはreturnで返す


        //startの位置に困る
        //cutterはstart,endの位置がわかる

        //**start_memoを記録
        sum = cutter(octet,ip,child_10,&start_memo,&end_memo);

        //挿入
        char network_address[16];
        strcpy(network_address,ip);//合ってるか不安
        insert(octet,network_address,AND_10,&start_memo,&end_memo);

        //表示
        //printf("network address:%s\n",network_address);


        //binary_ip(2),binary_sub(2)にする不安っていってたアルゴリズムがネックな気がする

        //ホスト数の表示
        int host_bit=0;
        host_bit = search_sub(binary_sub,octet);
        //printf("ホスト数:%d(2^%d -2 )\n",(int)pow(2,host_bit)-2,host_bit);
        /*
        printf("2^%d = %d\n",host_bit,(int)pow(2,host_bit));
        printf("ホスト数:%d(2^%d - 2)\n",(int)pow(2,host_bit)-2,host_bit);
        */

        //ブロードキャストアドレス

        int host_bit_tmp = host_bit;
        int broad_octet = 3;//添え字
        while(host_bit_tmp >=9){

                host_bit_tmp %= 8;
                broad_octet--;

        }
        /*
        puts("---non accurate---");
        printf("broad_octet:%d\n",broad_octet);
        printf("host_bit_tmp:%d\n",host_bit_tmp);
        */

        //第broad_octetオクテットの数をhost_bit_tmp分増やせばおｋ
        char broad_cast[16];
        strcpy(broad_cast,network_address);//できてるかな？ できてる

        //printf("broad_cast:%s\n",broad_cast);
        
        //cutter呼び出して最初最後を調べる
        //ここはnetwork_addressを参照
        //char AND_10[4];これ使ったほうが早い
        sum = cutter(broad_octet,network_address,child_10,&start_memo,&end_memo);
        //多分空白とかを計算してしまっているのでAND_10を使う
        sum = atoi(AND_10);
        //printf("cutterで取り出したsum:%d\n",sum);

        //start_memo ~ end_memoのところをhost_bit_tmp分ふやす
        //ここ多分分岐しなくていい
        /*
        if(broad_octet==3){
                //ホスト数が256以下のとき
                //第4オクテットを修正するのでその他の修正はいらない
                sum = sum + pow(2,host_bit_tmp)-1;

        }else{
                //第1~3オクテットを修正、そのあとは255にする必要がある
                //sum = sum + host_bit_tmp - 1;
                sum = sum + pow(2,host_bit_tmp)-1;
                puts("broad castアドレスに誤りがある可能性があります");

        }
        */
        sum = sum + pow(2,host_bit_tmp)-1;

        //printf("調整加えたsum:%d\n",sum);
        //2.int10進数(sum)をchar10進数にする
        length = texting(sum,child_10);//char *child_10に収容 長さはreturnで返す
        //bury関数を一般的な使用ができるように変更
        insert(broad_octet,broad_cast,child_10,&start_memo,&end_memo);

        //修正した次のオクテットから255で埋める
        int broad_octet_now = broad_octet;
        if(broad_octet==3){
                //pass
                //ここヌル文字入ってるのかな？ 入れるようにした
                //printf("after inserted)end_memo:%d\n",end_memo);
        }else{

                while(broad_octet_now < 3){

                        //puts("loop?");

                        broad_octet_now++;

                        //start endを調べる
                        sum = cutter(broad_octet_now,broad_cast,child_10,&start_memo,&end_memo);
                        child_10[0] = '2';
                        child_10[1] = '5';
                        child_10[2] = '5';
                        //このヌル文字がだめな気がする
                        //child_10[3] = '\0';
                        
                        insert(broad_octet_now,broad_cast,child_10,&start_memo,&end_memo);

                        //確認
                        //printf("broad cast(unfinished):%s\n",broad_cast);

                }

                //ヌル文字はここに持ってくればいいのでは
                //main関数内にend_memoがあるのでポインタを使う必要がない、またぐときに使う必要が出てくる
                //broad_cast[*end_memo+0] = '\0';

                //broad_cast[end_memo] = '\0';
        }
        //第４オクテットを修正したときにもヌル文字をいれるためここだろう
        broad_cast[end_memo] = '\0';

        //puts("finished repairing broad cast.");

        //表示設定エリア（ここにまとめる）
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

//-1.親[16]からカットしたchild_10[4]を生成する
int cutter(int octet,char *parent,char *child_10,int *start_memo,int *end_memo){
        
        //ex 255.89.252.0
        //3オクテットを指定されたら252を切り取りたい
        int i=0;
        int t=0;
        int octet_value = octet+1;
        int count=0;
        int count_value=1;
        int keta=0;
        int fin=0;

        int start=0;
        int end=0;

        //全部で3*4 + 1*3 = 15 ヌル文字で16文字0~15
        //ここも原因だった　範囲と式ﾐｽ
        //0~15 15はヌル文字
        for(i=0;i<=15;i++){

                //ここが原因だった
                //第4オクテット絡むとバグる
                //subとかちゃんと扱わなかったから
                //一番最初に使うので関係ない
                //第4オクテットの時正しく終了できていない
                //parent[i] == '\0'
                if(parent[i]=='.' || parent[i]== '\0' ){

                        if(fin==1){
                                //ヌル文字いれる
                                end = i-1;
                                child_10[t] = '\0';
                                break;
                        }else{
                                //pass
                        }

                        count++;
                        count_value++;

                }else{
                        //目的オクテットだった場合、桁の取得
                        //値のコピー
                        if(octet_value == count_value){

                                //ここ追加してみた不安
                                //消して空白ができたとこもカウントしてしまってるのではないだろうか
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

        //start,end,ketaがわかったので、sumを求める
        //child_10[4]
        int value;
        int cnt=0;
        int sum=0;

        //printf("keta:%d\n",keta);

        //ここも怪しい　原因？
        //sumも桁も違う時がある
        for(i=0;i<keta;i++){

                sum += (child_10[keta-i-1] - '0') * pow(10,i);
                //printf("sum:%d\n",sum);

        }

        //sum求められてない
        //start endを記録する

        //確認出力
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

//0.sumからtext_2(char2進数 8bit)を作成
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
//0.5 binary_ip と binary_subをAND演算
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

        //このカウントは使わないように。host_bitでオクテットも加味したホストビット数がカウントされている
        return count;

}

//1.char二進数(8bit)text_2を10進数(int)に直す return sum;でsumから受け取る
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

//2.int10進数(sum)をchar10進数にする
int texting(int num_10,char *child_10){

        //char *child_10に収容

        int i=0;
        int length=0;
        int syou=-1;
        int value = num_10;

        //桁数を求める
        //10で割ることを繰り返してsyouが0になったら終了
        //アルゴリズムあってるか不安
        while(syou!=0){

                syou = value / 10;
                value /= 10;
                length++;

        }
        value = num_10;

        //printf("length(keta):%d\n",length);

        //char *child_10に収容
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

//3.char10進数を埋め込む return start;
int bury(int length,char *child_10,char *sub,int start){

        //printf("bury(child_10):%s\n",child_10);

        //sub[start]~sub[start+length-1]までchild_10を挿入
        int i=0;
        for(i=0;i<length;i++){

                sub[start] = child_10[i];
                start++;

        }

        sub[start] = '.';
        start++;


        return start;

}

//3.network_addressの作成
//bury関数を一般的な使用ができるように変更
void insert(int octet,char *parent,char *child,int *start_memo,int *end_memo){

        //strlenはヌル文字は含まない
        int i;
        int delete_letter = *end_memo - *start_memo+1;
        int insert_letter = strlen(child);
        //printf("delete_letter:%d insert_letter:%d\n",delete_letter,insert_letter);
        //printf("start_memo:%d end_memo:%d\n",*start_memo,*end_memo);

        //insertのほうが大きければずらす
        if(delete_letter < insert_letter){
                //ずらす
                //*start_memoから'\0'までを1個うしろにずらす
                //ずらさないと.が消える場合がありバグる
                //puts("ずらす処理をしてないので、ネットワークアドレスの表示がバグっています");
                //puts("ずらす処理をしました");

                //ヌル文字の位置を探す
                int posi=0;
                for(i=*start_memo;i<15;i++){

                        if(parent[i] == '\0'){
                                posi = i;

                        }else{

                        }

                }

                // イコールの場合は含まれていないのでバッファのあふれは起こらない
                for(i=posi;i>=*start_memo;i--){

                        //移動
                        parent[i+1] = parent[i];
                        parent[i] = parent[i-1];

                        //ヌル文字大丈夫かな、、

                }

                /*
                int length_test = strlen(parent);
                printf("文字数テスト:%d",length_test);
                */
        }else{
                //pass

        }


        //puts("deleteing letter");
        //前の文字消す
        for(i= *start_memo+0;i<= *end_memo+0;i++){

                parent[i] = ' ';

        }

        //挿入
        //puts("inserting letter");
        for(i=0;i<insert_letter;i++){

                parent[*start_memo+i] = child[i];
        }
        *end_memo = *start_memo + i;
        //ここ追加
        //parent[*start_memo+i] = '\0';
        //これやるとネットワークアドレスミスる

        int after_inserted_soon_t = *start_memo + i;

        //第四オクテットまで0になる
        //これは別関数でやったほうがいい
        //ネットワークアドレスの時は0にしたいし、ブロードキャストのときは255にしたい
        
        //確認
        //printf("(unfinished):%s\n",parent);

        return;
}

//4.search_sub() host_bitを求める。returnはhost_bit
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

        //このオクテットはローカルのはずだから大丈夫、、
        while(octet < 3){

                count += 8;
                octet++;

        }

        return count;

}

