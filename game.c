#include <stdio.h>
//FF8�̐퓬�V�X�e�����Č�

struct OBJECT{

        char name[20];
        int hp;
        int time;
};
typedef struct OBJECT object;

int main (void){

        //�������
        object person[3] = {

                {"���m�A",8478,6},
                {"�X�R�[��",9999,6},
                {"�[��",7998,6}
        };

        object enemy = {"�A���e�}�E�F�|��",99999,10};

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

                //�N���s�����邩���� turn�ɋL�^
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

                //time�̑���
                for(i=0;i<3;i++){
                        person[i].time += 1;
                }
                enemy.time += 1;

                if(turn==-1){
                        continue;
                }else{
                        //pass
                }

                //�U������
                if(turn==3){
                        //�G�̍U��
                        //�Ώێ҂̌���
                        //�^�[�����J�邲�Ƃɏ��ԂɍU�����Ă���
                        target = s;
                        s++;
                        person[target].hp -= 1000;//�Ƃ肠���������͒萔
                        if(person[target].hp<=0){
                                living_count--;
                        }else{
                                //pass
                        }

                }else{
                        //�����̍U��
                        enemy.hp -= 10000;//�Ƃ肠�����������萔
                }

                //��ʏo��
                //�G���̏o��
                puts("-------------------");
                printf("%s  ",enemy.name);
                printf("%5d",enemy.hp);

                //�����܂ł̕��������J�E���g����
                space = strlen(enemy.name) + 2 + 5;

                //�������̏o��
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
                //�f�o�b�O�p
                printf("turn:%d\n",turn);
                printf("enemy.time:%d\n",enemy.time);
                for(i=0;i<3;i++){

                        printf("person[i].time:%d\n",person[i].time);
                }
                if(turn==0){
                        puts("attacker:���m�A");

                }else if(turn==1){
                        puts("attacker:�X�R�[��");

                }else if(turn==2){
                        puts("attacker:�[��");

                }else{
                        puts("attacker:�A���e�}�E�F�|��");

                }
                */
                
                

        }//while

        return 0;


}
