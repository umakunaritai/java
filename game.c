#include <stdio.h>
//FF8の戦闘システムを再現

struct OBJECT{

        char name[20];
        int hp;
        int time;
};
typedef struct OBJECT object;

int main (void){

        //初期情報
        object person[3] = {

                {"リノア",8478,6},
                {"スコール",9999,6},
                {"ゼル",7998,6}
        };

        object enemy = {"アルテマウェポン",99999,10};

        //printf("%d\n",enemy.hp);
        int turn=3;
        int i=0;
        int target=0;
        int s=0;
        int living_count=3;
        int length=0;
        int j=0;
        int space=0;
        while(enemy.hp > 0 && living_count >0){

                //誰が行動するか決定 turnに記録
                turn = -1;
                if(enemy.time >= 10){
                        turn = 3;
                        enemy.time = 0;
                }else{
                        for(i=0;i<3;i++){
                                if(person[i].time >= 10){
                                        if(person[i].hp > 0){
                                                turn = i;
                                                person[i].time = 0;
                                                break;// for i
                                        }else{
                                                //pass
                                        }
                                }else{
                                        //pass
                                }
                        }//for i
                }

                //timeの増加
                for(i=0;i<3;i++){
                        person[i].time += 1;
                }
                enemy.time += 1;

                if(turn==-1){
                        continue;
                }else{
                        //pass
                }

                //攻撃する
                if(turn==3){
                        //敵の攻撃
                        //対象者の決定
                        //ターンが繰るごとに順番に攻撃していく
                        target = s;
                        s++;
                        person[target].hp -= 1000;//とりあえずここは定数
                        if(person[target].hp<=0){
                                living_count--;
                        }else{
                                //pass
                        }

                }else{
                        //味方の攻撃
                        enemy.hp -= 10000;//とりあえずここも定数
                }

                //画面出力
                //敵情報の出力
                puts("-------------------");
                printf("%s  ",enemy.name);
                printf("%5d",enemy.hp);

                //ここまでの文字数をカウントする
                space = strlen(enemy.name) + 2 + 5;

                //味方情報の出力
                for(i=0;i<3;i++){

                        if(i==0){

                                for(j=0;j<space;j++){

                                        printf(" ");
                                }

                        }else{
                                for(j=0;j<space*2;j++){

                                        printf(" ");
                                }

                        }
                        printf("%s ",person[i].name);
                        printf("%d ",person[i].hp);
                        length = person[i].time;
                        if(length>=10){
                                length = 10;
                                for(j=0;j<length;j++){

                                        printf("*");
                                }
                                printf("!");
                        }else{
                                for(j=0;j<length;j++){

                                        printf("*");
                                }
                        }
                        puts("");
                }

                /*
                //デバッグ用
                printf("turn:%d\n",turn);
                printf("enemy.time:%d\n",enemy.time);
                for(i=0;i<3;i++){

                        printf("person[i].time:%d\n",person[i].time);
                }
                if(turn==0){
                        puts("attacker:リノア");

                }else if(turn==1){
                        puts("attacker:スコール");

                }else if(turn==2){
                        puts("attacker:ゼル");

                }else{
                        puts("attacker:アルテマウェポン");

                }
                */
                
                

        }//while

        return 0;


}
